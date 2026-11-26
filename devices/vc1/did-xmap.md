# VC1: display IDs, the mode table and the colour-map bank

How the Entry board decides, for each pixel, which of the colour map's four banks the 8-bit pixel value is looked up in. This is the
IRIX 5.3 X server's use of the VC1; the kernel's own start-up uses a simpler form of the same tables. Chip-level addressing is on the
[VC1 page](README.md); the palette side is on [Colour-map banks](../bt479/banks.md).

Grades follow [AGENTS.md](../../AGENTS.md). Tags: **[binary]** read in a shipped object, with function and address; **[hdr]** a name
or value in the shipped header `sys/lg1hw.h` or `sys/lg1.h` (names and numbers only, no text taken); **[inferred]** says what the
reading rests on. Sources: IRIX 5.3 (install disc image, SHA-256 `a194caea63d280109c37d50be929c34a0f80a23c3e951c3cfa2af1315a0d8cad`),
`usr/cpu/sysgen/IP20boot/lg1.a` and `usr/lib/X11/dyDDX/lg1mc.so` (checksums in [irix-files.md](../../references/irix-files.md)); X
server addresses are `lg1mc.so` virtual addresses. No VC1 data sheet is held (searched the Library by name and by part number
`L1A6654`); nothing here is a statement about the chip's internals beyond what software does to it and reads back.

## Summary

- **Established (what software writes).** The X server gives every window a small display ID (DID, 5 bits) and writes two tables
  into the VC1: a per-scanline list of "from this x onward DID n" spans in the external SRAM, and, through window 1 of the VC1 (the
  "display-mode" or XMAP table), a 16-bit mode word per DID, whose bits 3:2 are the number of the bank the X server loaded that
  window's colour map into. The kernel only initialises both to "every row is DID 0, every mode word is 0".
- **Inferred (what the chip does).** The four colour-map banks are chosen per window, not per board, by the VC1 reading these tables
  while it scans out. Nothing shipped reads the result back, so this rests on what the tables hold and on the X server needing it.
- **Inferred.** The VC1 hands the mode word's bank bits and index-offset bits to the colour map beside the pixel value, so one
  1024-entry palette serves up to seven installed X colour maps at once. A model that displays bank 0 only shows every window whose colour
  map the server put in banks 1, 2 or 3 through bank 0's entries, which matches grey windows coming out blue/cyan.
- **Unknown.** Everything inside the chip: the exact wire between mode word and colour map, what the mode word's other bits do, the
  odd half of the mode table, and the horizontal divider registers' arithmetic.

## What each program writes

### Registers (window 0, address counter set through `CONFIGSEL` 5 and 4)

| Register | Name [hdr] | Kernel `initVC1` (`light_init.o` +0x594) | X server `vc1Init` (0x5e2d2d90) |
|---|---|---|---|
| 0x40, 0x41 | `DID_EP` | 0x40, 0x00 (frame table at SRAM 0x4000) | 0x09, 0x00 (frame table at SRAM 0x0900) |
| 0x42, 0x43 | `DID_END_EP` | 0x46, 0x00 (end at 0x4600) | 0x0f, 0x00 (end at 0x0f00) |
| 0x44, 0x45 | `DID_HOR_DIV`, `DID_HOR_MOD` | 0xcc, 0x04 | 0xcd, 0x00 |
| 0x60, 0x61 | `BLKOUT_EVEN`, `BLKOUT_ODD` | 0x01, 0x01 | 0x01, 0x01 |
| 0x62, 0x63 | `AUXVIDEO_MAP` and the byte after it | not written | 0x31, 0x00 |

**Established** (every store of `vc1Init` between its two table loads and the cursor registers was traced; the kernel row is the
earlier reading on the [VC1 page](README.md)). Reading of the divider pair, **inferred** from arithmetic only: 5 x 204 + 4 = 1024 and
5 x 205 = 1025, so both programs describe a 1024-pixel line cut into five parts, the server rounding up. What the VC1 does with it:
unknown. `AUXVIDEO_MAP` is named for the optional video-input board; 0x31 has the same shape as a mode-word low byte (see below) but
nothing reads it back except `light_read_auxmapindex` (+0x1814), which returns it to user space.

### SRAM

| Address | Kernel | X server |
|---|---|---|
| frame table (pointed to by `DID_EP`) | 0x4000, 0x600 bytes: 768 pairs 0x48 0x00; last pair 0x48 0x40 | 0x0900, 0x600 bytes: 768 pairs 0x20 0x00; last pair 0x20 0x04 (initial load in `vc1Init`; rebuilt by `vc1LoadDIDTable` 0x5e318954, which stores the table in the same 0x0900 area through `vc1LoadSRAM` with length 0x600) |
| line table | 0x4800, 0x8a bytes (`did_linetable`) | 0x2000, 16 bytes at first load; `vc1LoadDIDTable` later writes the real table at 0x2000 or 0x5000, alternating on each reload |

**Established** for the addresses, lengths and initial bytes (the 16 bytes the server loads first are `00 01 00 00  00 05 00 00  00 00 00 00  00 00 00 00`,
read from the module's data at 0x5e3c0ea0). The alternation between 0x2000 and 0x5000 is **established** as a store sequence in
`vc1LoadDIDTable` (a flag toggled in the board record, 0x2000 or 0x5000 added to every pointer); that it is double buffering so the
chip never scans a half-written table is **inferred**.

The kernel's frame table is not uniform: 767 pairs are 0x48 0x00 (record 0, DID 0) and the last is 0x48 0x40, which is record 16 (records
are four bytes) and so DID 16, not DID 0. The 0x8a bytes the kernel loads are 32 four-byte records and a 10-byte tail (count 4,
four zero entries) at 0x4880 that no frame entry points at (`light_init.o` data at `did_linetable`, `initVC1` +0x594). The server's last
frame entry is 0x2004, the second record of its 16-byte first load, which has count 5 and five zero entries (all **established**
from the stores and the data). In the kernel DID 16 and DID 0 both have mode word 0 and in the server the
last row's entries are all DID 0, so the display is the same; whether the odd last row means anything to the chip is **unknown**.

## The two tables

### Frame table: one pointer per scanline

Entry n (16 bits, big-endian, at the address in `DID_EP` + 2n) is the SRAM address of the line table record used for screen row n; rows
0 to 767. **Established** from `light_read_scan` (`light.o` +0x1924), which reads exactly 768 entries, and from both programs' stores.
In the same routine an entry with bit 15 set is read as a repeat count: the previous pointer is used for that many rows and the
read address then jumps to the slot of the first row after the run. No program writes one (the X server's table is a full
0x600 bytes of explicit pointers), so a run-length entry is **inferred** to be a chip feature that the readback decodes and nothing uses.
A model may ignore it.

### Line table record: spans of display ID along one row

At the pointer: one 16-bit count n, then n 16-bit entries. **Established** from `light_read_scan` (the count then the entries, per
distinct pointer) and from the kernel's `did_linetable` (32 records of "count 1, entry i" for i = 0 to 31, so record i means "the whole row
is DID i").

The X server's entries are `(x << 5) | did`: `vc1LoadDIDTable` ORs a window's DID (5 bits) with its left edge shifted up five bits
(0x5e318f94 to 0x5e318fa8, where each rectangle of a window's clip list becomes one entry), emits the rectangles of a row from left to
right, and writes the count first. **Established** for the packing (the emit loop was read); **inferred** for the direction of use:
pixel x of the row takes the DID of the last entry whose x is at or below it, and the first entry of every row starts at x = 0 (the
default records do, and the server's clip lists cover the screen). When a flag byte in the board record (byte +10) is
zero the routine appends one more entry to each row's record, a copy of the last entry with x one higher (+32 in the packed form,
0x5e319010 to 0x5e31901c), and counts it (the count store at 0x5e318f44); **established** for the sequence. The flag is the
kernel's board-info byte 0x2a, which `rexGetRevs` copies into the board record (0x5e2d2034 to 0x5e2d2040) and which `lightInitInfo`
(`light_init.o` +0x184 to +0x194) sets to the VC1's register 5 read-back masked with 7, minus one: so the extra entry is emitted when
the VC1 reads back 1 in those bits (**inferred** that this is a chip revision; the data-sheet meaning is **unknown**). What the extra
entry is for is **unknown**.

## The mode table (window 1)

32 entries in the even half (byte address 2n) and 32 in the odd half (0x40 + 2n); [hdr] names them `MODE_REG_0_E` to `MODE_REG_1F_E` and
`MODE_REG_0_O` to `MODE_REG_1F_O` ("even" and "odd" are the header's names; why there are two copies, whether the chip uses
the half chosen by pixel parity, scan line parity or something else is **unknown**; the header also heads the two tables "Even XMAP" and "Odd XMAP" and has `BLKOUT_EVEN` and `BLKOUT_ODD` registers, which points at a split of the display by parity, **inferred** from the names only). `light_read_displaymodes` (`light.o` +0x1864) reads
all 64 and `lightSetDisplayMode` (+0x1540) writes only the even half (address 2n, high byte then low byte, GO alias only); the
retrace handler touches only entries below 32. The X server writes both halves for the entries it initialises (below). At run time every mode word goes through request 1017 and `lightSetDisplayMode`, so the odd half is written once, by `vc1Init`, for DIDs 4 to 8 (byte addresses 0x48 to 0x50, which is the second copy a model's write log shows); no shipped path refreshes it, and none writes the odd half of any other DID, so what they hold is the chip's power-up state, which is **unknown** (**established** that no shipped code writes them). Since a changed DID's even word would then disagree with its odd word, whichever condition selects the odd half is not met in an ordinary desktop (**inferred**): reading the even half only matches every software path.

### Mode word layout

16 bits, high byte first. **Established** from `rexChangeDIDCmap` (0x5e312a68, read in full): for an installed colour map it
clears everything except bits 14:12 and 1:0 of the window's saved word (mask 0x7003), then ORs in 0x0300 and
`((hw & 0x0f) << 2) | (hw & 0xf0)`, where `hw` is the byte the server keeps per hardware colour map (table below). So:

| Bits | Meaning | Grade |
|---|---|---|
| 1 | which of the two image buffers a double-buffered window shows (the retrace handler sets or clears it) | inferred ([VC1 page](README.md#display-mode-xmap-table)); established that `rexChangeDIDCmap` (0x5e312bd0 to 0x5e312c00) follows bit 2 of the window's flags word (+0x20) when its bit 1 is set, and leaves the saved bit alone otherwise |
| 0 | set in the three pop-up and overlay entries the server initialises (DID 6 to 8); otherwise preserved by the server; the emulated trace shows it set on a double-buffered window's ID, and no shipped code tests it | role unknown; **inferred** to mark a narrow (four-bit) pixel whose nibble bit 1 picks, from that fit alone ([GL context state](../rex1/gl-context-state.md#which-nibble)) |
| 3:2 | colour-map bank (0 to 3) | established as the server's field; that the chip passes it to the colour map is inferred |
| 7:4 | high nibble of a colour-index offset (0x00, 0x30 or 0x40 in the shipped table) | established as the field; addition to the pixel is inferred (see [banks](../bt479/banks.md#where-each-bank-is-used)) |
| 9:8 | always 11 once the server has written the entry; the kernel leaves 00 | role unknown |
| 14:12 | preserved by the server, never set by anything read | role unknown |
| 11:10, 15 | never set | unknown |

The server writes the word to the kernel with private request 1017 (`rexChangeDIDCmap` +0x1f0 to +0x1fc); the kernel side is
**inferred** to end in `lightSetDisplayMode`, the only routine in `lg1.a` that writes this table.

### Initial entries

The X server's `vc1Init` first writes 0x0300 to all 32 even entries (a loop of eight passes of four entries, 0x5e2d2f9c to 0x5e2d301c),
then overwrites entries 4 to 8 in both halves (even entry at 2n, odd copy at 0x40 + 2n) before any window exists. The kernel's `initVC1` zeroes only the even half (64 bytes from address 0, `light_init.o` 0x10000764 to 0x100007b4), so the odd half is
otherwise never written. **Established** for the words (store sequence traced in `vc1Init`, 0x5e2d3024 to 0x5e2d33f4):

| Entry (DID) | Word | Reading (**inferred** from the field layout above) |
|---|---|---|
| 0 to 3, 9 to 31 | 0x0300 | bank 0, even half only |
| 4 | 0x0304 | bank 1 |
| 5 | 0x0308 | bank 2 |
| 6 | 0x030d | bank 3, index offset 0x00, bit 0 set |
| 7 | 0x033d | bank 3, index offset 0x30, bit 0 set |
| 8 | 0x034d | bank 3, index offset 0x40, bit 0 set |

The server's per-hardware-colour-map byte `hw` (word at +0x14 of each 24-byte record of `rexHWCmaps`, data at 0x5e3c0138; seven
records, `rexNumHWCmaps` = 7 at 0x5e3c01e0) is, for maps 0 to 6: 0x00, 0x01, 0x02, 0x00, 0x03, 0x33, 0x43. **Established** (read from
the data section). The low nibble is the bank and the high nibble the index offset; maps 4, 5 and 6 reproduce the mode words of DIDs 6, 7
and 8 exactly (bank 3 with offsets 0x00, 0x30, 0x40), which supports "DID is the index the server assigns to a hardware colour map" for
those three. The word at +0x10 of the same seven records reads 0, 4, 5, 0x20, 6, 7, 8: it is the display ID of the map, because `cmapDID`
(0x5e315b8c) returns it for a window whose colour map is installed, and 0x20 (32, one past the mode table) is the pop-up map's.
The allocator functions (`FindFreeID`, `SetDIDMode`, `UpdateDIDMode`) were read for the install page: map 3 is the pop-up map
and is not tied to bank 0 as this page first said ([how DIDs and mode words are chosen](../../platforms/lg1/colormap-install.md#3-choosing-a-windows-display-id-and-mode-word),
**established** for the DID field, **inferred** for the pop-up reading).

## When a window moves (IRIX 6.2 X server, read 2026-11-25)

Question: after a rendering (GL) window is dragged, does the guest rewrite the display-ID tables for the area it left, and when? Answer: yes, during the window-tree validation of the move itself, before the pixels are copied and before the vacated area is painted. Nothing read rewrites them later in the same move. Tags as above; addresses are 6.2 `lg1mc.so` (hash in [irix-files.md](../../references/irix-files.md)). The slot numbers are byte offsets in the screen record `rexScreenRec` (data 0x5e5724d0); each slot's function was read from the data.

**The slots (established).** 188 `nfbPositionWindow`; 204 `nfbLayerValidateTreeSL` (wrapped by `rrmValidateTree`, 0x5e4a15d8); 208 `nfbPostValidateTree`; 212 `miWindowExposures`; 216 `nfbPaintWindowBackground`; 224 `rexCopyWindow`; 468 `nfbMarkOverlappedWindows`; 480 `nfbMoveWindow`; 492 `miHandleValidateExposures`. The board's own per-screen table `rexScrnPriv` (data 0x5e5723c4) holds `rexValidateVisual` (0x5e489fc0) at offset 108.

**Order for a mapped window moved with the move validation kind (`nfbMoveWindow`, 0x5e4a5224, established).**

1. Snapshot the old clip regions; call slot 188, `MoveWindowInStack`, `ResizeChildrenWinSize` and slot 468.
2. Slot 204. `rrmValidateTree` first walks the subtree and, for rendering-node windows with pending state, calls `rrmInvalidate` (0x5e4bd784), which sends kernel request 1010 and may rewrite a window's mode word through `rexValidateMode` (request 1017: bank, offset and the shown-buffer bit, no table). Then `nfbLayerValidateTreeSL` builds, for each display ID, the region that gained area (the window's newly exposed area to its own ID, the parent's exposed area, which is the vacated rectangle, to the parent's ID, **inferred** from the region arithmetic) and at 0x5e490f38 calls slot 108, `rexValidateVisual`, when the parent's window flag 0x8 is set. That flag is set on a window's ancestors when a descendant's display ID differs from its parent's (`nfbSetDidFlags`, 0x5e489288; **inferred** for the condition), so it is set while any rendering window exists below the root. `rexValidateVisual` takes the per-ID regions, removes the gains from the other IDs and, if any ID gained area, calls `vc1LoadDIDTable` (0x5e4a5c1c).
3. Slot 224, `rexCopyWindow`: block copies only; no VC1 access found.
4. Slot 492, `miHandleValidateExposures`: for each window slot 212 with the exposed region (the vacated rectangle) and slot 216 paints the background through the REX fill routines; no VC1 access found. This part was read for its calls, not line by line.
5. Slot 208 with the move kind only subtracts and clears two counter arrays in the board record.

So on the move the tables change first, then the pixels move, then the background is painted: for a short time the new line tables already assign the vacated area to the root's ID while the old pixels are still there. The work procedure `rrmWorkProc` (0x5e4b8cc0) runs shortly afterwards (about every 50 ms) and sends the window's clip rectangles (`rexValidateClip`, request 1011), which is a hardware-clip update, not a table write. For the other validation kinds (map, unmap, restack, a move combined with a restack or resize) slot 108 is called from `nfbPostValidateTree` instead, after the copy and the paint. Which kind a window-manager drag produces was not determined (the code that picks it is in the core server, not this module). The 5.3 module has the same structure (`vc1LoadDIDTable` 0x5e318954, `nfbPostValidateTree` 0x5e2fa824, `rrmValidateTree` 0x5e31783c), offsets four lower.

**What `vc1LoadDIDTable` does to the chip (established for the store order).** If the board byte at +10 is 0 it clears bits 5:4 of VC1 register 6 first and restores it at the end, waiting for the engine's busy bit at 0x47f8. It writes the new line tables to whichever of 0x2000 and 0x5000 is not in use (toggling a bit in the board's private record), then overwrites the whole frame table in place at 0x0900 (768 sixteen-bit row pointers, 0x600 bytes) with pointers into the new bank, through `vc1LoadSRAM` (0x5e4a45e8): select 5 and 4 set the address, select 2 and the data port at 0x47f0 (and its alias 0x4ff0) write the bytes, then the address is parked at 5 and busy is polled. No `DID_EP` or other register is written afterwards, so the in-place frame-table write is the only commit; since every pointer addresses a complete row list in the bank not being scanned, a half-rewritten frame table still shows a consistent row each. The role of the 0x4ff0 alias (strobe or plain alias) is **inferred**. The line-table bank toggle (0x5e4a6430) was checked; the parked address, the busy poll, the restore of register 6 and the work procedure's period were read in one pass and not cross-checked. Unverified.

**What a model must do.** Decode the DID of each pixel from SRAM at scan-out (frame table, then the row's line table, then the mode word); do not cache a copy built at an earlier write, or invalidate it on any SRAM write. A model that keeps showing the GL window's bank over the vacated area after the guest's table writes is reading stale tables. To check that the guest rewrote them: during a drag there should be stores of 5, 4 and 2 through the `CONFIGSEL` port followed by bytes at 0x2000 or 0x5000 and a 0x600-byte run at 0x0900 (the frame table); if none appears, the guest did not take this path (no descendant with a different ID, or the unknown validation kind) and the fault is elsewhere. **Unknown, with the routes tried:** which kernel routine serves requests 1010, 1011 and 1017 (no symbols in the 6.2 kernel object and the 5.3 `rrm.o` table was not decoded), what enqueues the clip update after a move (the callbacks at 0x5e573850 are reached only from the core server, which was not disassembled), and the meaning of the root's layer value that gates the block fills in `rexValidateVisual`.

## What a model must do

All of this is **inferred** from the software contract: it is the least a model needs for the X server's output to be right.

1. Keep the register file, SRAM, mode table (64 entries of 16 bits) and the DID registers as plain storage that reads back what was
   written (this part is established; see the [read protocol](README.md#readback-and-the-retrace-handler)).
2. When scanning out row y, take the line-table pointer for y from the frame table at `DID_EP`, find the span containing x, read its
   DID, then read mode word `DID` (even half) from the mode table. Row 0 of the display is stored y = 0 (see the REX1 page, Y origin).
3. From the mode word take bank = bits 3:2 and index offset = bits 7:4 shifted left four. Look the pixel up at
   `bank[(pixel + offset) & 0xff]` (OR and add give the same result for every offset the shipped table uses with a pixel below 16).
4. If the DID generator is not enabled (SYS_CTL bit 3; the kernel writes 0xfc, which sets it; the PROM writes 0xb9, which also sets it),
   or the frame table pointer is not yet loaded, use bank 0 with offset 0, which is what the PROM console and the kernel's own
   all-DID-0 tables give.
5. Odd half, `AUXVIDEO_MAP`, `BLKOUT_*` and the divider registers: store and return, no effect.

What would settle the unknowns: a VC1 or LUT1 data sheet (LSI Logic part numbers `L1A6654` and `L1A6651`), or a published description of
the sibling LG2 board's colour map. The X server cannot, since it only writes these registers.

## Open

- The mode word's bits 9:8, 14:12 and 0 and what the second (odd) half is used for. The three bit-0 words are the overlay and pop-up IDs (6 to 8); which plane group they show is on [overlay planes and bank 3](../../platforms/lg1/desktop-and-overlays.md#dids-6-to-8-and-bank-3).
- Whether the index offset is added to, or replaces the high bits of, the pixel value; the shipped table cannot tell them apart.
- Why the line-table writer adds an entry for one VC1 read-back value, and the chip's use of `DID_HOR_DIV` and `DID_HOR_MOD`.
