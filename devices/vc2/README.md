# VC2 video controller: the hardware cursor (Newport graphics)

The VC2 is the Newport board's video controller. It generates the video timing, a per-pixel display ID for the XMAP9 and the cursor.
It does this by reading three tables from a 64 KB external RAM that the host fills over REX3's display bus. This page covers the
cursor and the registers a driver needs to show one: the RAM, the glyph format, the position and enable registers, the colours
and the hot spot. The video-timing and display-ID tables are not written up here.

Grades follow [AGENTS.md](../../AGENTS.md). Review 2026-11-27. Nothing was run on a board or in an emulator.

Sources (hashes and paths in [irix-files.md](../../references/irix-files.md)):

- the VC2 Specification, revision 2.0, 17 May 1993 (Library `erikarn-sgi_indy_vc2.pdf`; text read in full, the cursor-table figure
  read as an image);
- the REX3 and XMAP9 specifications, for the bus and the colour-map address;
- the IRIX 6.5.7 source tree's PROM library (`stand/arcs/lib/libsk/graphics/NEWPORT/ng1_init.c`, `np_timing.h`,
  `stand/arcs/lib/libsk/graphics/CURSOR/vc1cursor.c`), the ide diagnostics (`stand/arcs/ide/fforward/graphics/NEWPORT/vc2.c`) and, for
  macro values the Newport tree lacks, the MCO board diagnostics' copy of the VC2 constants
  (`stand/arcs/ide/isddevices/video/MCO/mco_diag.h`, which says it copies the kernel's `vc2.h`);
- the 6.5 base media IP22 kernel archive `ng1.a` (`newport.o`: `newportPositionCursor`, `newportPrivate`; `newport_init.o`: `initVC2`,
  `initNg1Cursor`, `vc2LoadSRAM`, `newportInit`), disassembled and read for those functions;
- the X server module `ng1.so` (`rex3DisplayCursor`, `rex3InstallCursor`, `rex3CursorOn`, `rex3DrawImage*`);
- the IP22 PROM image `ip22prom-5.3revE.bin`: the cursor and display-enable routines at 0xbfc1d8c0 and 0xbfc1d2bc;
- Linux v7.2-rc7 `include/video/newport.h` and `drivers/video/console/newport_con.c`, and NetBSD `sys/arch/sgimips/gio/newport.c`
  and `newportreg.h` (revisions in the irix-files page).

The colour-map (CMAP) specification is not held, so what the colour map does with the cursor colours rests on software.

## Answer

| Question | Answer | Grade |
|---|---|---|
| Glyph size and planes | 32 x 32 pixels, 2 bit planes, 128 sixteen-bit words. A second mode, 64 x 64 x 1 plane (256 words), exists. | **established** (specification); the 64 x 64 mode is used by one ide diagnostic only |
| Bit order | Each row is two 16-bit words, left half first. In a word, the leftmost column is bit 15. The plane for pixel-code bit 0 comes first (words 0 to 63), then the plane for bit 1 (words 64 to 127). | **established**: the specification's figure (columns 0 to 15 printed under bit labels 15 to 0), and the same layout in the PROM glyph, the kernel and the X server |
| Where the glyph lives | VC2 RAM word address **0x500**, set through the Cursor Entry Pointer (index 1). Same in the PROM, the kernel, the X server and the ide diagnostic. Linux defines the constant (`VC2_CGLYPH_ADDR`) but loads its glyph at whatever the entry pointer already holds. | **established** |
| How it is loaded | Index 7 (RAM Address) is written with 0x500, then each 16-bit word is stored to the RAM data register (CRS 3); the address auto-increments after every word. | **established** (specification, kernel, PROM, X server, Linux) |
| Cursor position | Index 2 (X) then index 3 (Y), written in that order; the VC2 latches both at the Y write. Position is the glyph's top-left corner and is measured from a point left of and above the visible screen. IRIX adds **29** to X and **31** to Y after subtracting the hot spot. | **established** for the registers, order and IRIX constants; the origin of 29 is **inferred** |
| Enable and mode | Display Control Register (index 0x10): bit 4 cursor function, bit 7 cursor display, bit 8 crosshair instead of glyph, bit 9 64 x 64 glyph. | **established** (specification, plus macro values from the MCO header and the kernel's `0x9b` constant) |
| Colours | The VC2 drives a 2-bit code per pixel. The XMAP9 turns it into colour-map address `(CRS3 << 5) \| code`; IRIX sets CRS 3 to 0xE7, so **0x1CE0 to 0x1CE3**. Code 0 is transparent. | **established** for the address; that code 1 is the bit-0 plane and 2 the bit-1 plane is **inferred** |
| Hot spot | Not in hardware. The kernel subtracts a per-board hot spot, set by the X server through kernel request 21001, from the pointer position. | **established** |

## The cursor RAM and how to reach it

The VC2 is on the display bus at `DCBADDR` 0. Its RAM is 32K words of 16 bits (specification: "64 K bytes, organized as 32Kx16"). The
specification says all words are big-endian pairs of bytes: first byte (high) then second byte (low), and a host access to RAM or to a
16-bit register must send both bytes, high first. **Established** (specification section 3.3).

| What | Display-bus setup | Grade |
|---|---|---|
| Write a register | `DCBMODE` = **0x0084100b**: `DCBADDR` 0, `DCBCRS` 0, `ENCRSINC`, `DATAWIDTH` 3, `ENASYNCACK`, chip-select setup 1 and hold 1. Then one word store to `DCBDATA0` of `(index << 24) \| (value << 8)`: the first byte goes to the index register (CRS 0), the next two to CRS 1 and 2 as the value. | **established**: the kernel (`newportPositionCursor`, `initVC2`), the X server, the PROM and Linux issue this; the specification describes the three-byte transfer |
| Read a register | `DCBMODE` 0x00841009 (one byte, CRS 0, auto-increment), byte store of the index at `DCBDATA0`+3; then `DCBMODE` 0x0084101a (two bytes, CRS 1, auto-increment) and a halfword load of the value. | **established** (kernel `newportInit` reads the control register this way, PROM at 0xbfc1d2bc) |
| Write RAM | Index 7 written with the start address as above. Then `DCBMODE` = **0x00841032** (`DCBCRS` 3, `DATAWIDTH` 2, no auto-increment), and one halfword store at `DCBDATA0`+2 per 16-bit word. | **established** (kernel `vc2LoadSRAM`, X server `rex3InstallCursor`, PROM routine at 0xbfc1cd44, Linux `newport_reset`) |
| Flow control | The kernel's `vc2LoadSRAM` checks REX3 `STATUS` bit 4 (backend busy) before it starts and after every 16 words, spinning until it clears. | **established** for the kernel; the specification gives the display-bus FIFO depth no role here, so the interval is **inferred** to track that FIFO |

Byte positions for the byte and halfword stores follow the big-endian rule in [byte lanes](../rex3/byte-lanes.md). On a little-endian
CPU the lane rule is **unknown** there.

Other facts from the specification: a write to RAM Address (index 7) resets the high-byte/low-byte phase, the chip must have its soft
reset released (Configuration register bit 0 set) before any register but index and configuration is touched, and the Cursor Entry
Pointer must be on a 128-word boundary for the 32 x 32 glyph and a 256-word boundary for 64 x 64. All **established**. 0x500 meets
both.

### RAM map the IRIX software uses

Word addresses, **established** for the values written. The bounds of each table are the software's, not the chip's.

| Words | Contents | Written by |
|---|---|---|
| 0x0000 to 0x03ff | video-timing line table | PROM, kernel |
| 0x0400 to 0x04ff | video-timing frame table | PROM, kernel |
| **0x0500 to 0x057f** | **cursor glyph (128 words)** | PROM, kernel, X server |
| 0x0600 | display-ID frame table (DID Entry Pointer, index 5) | PROM, kernel |
| 0x1000 | display-ID line table | PROM, kernel |

## Glyph format

**Established** (specification section 3.4.2 figure and text; the PROM, kernel and X server fill the buffer the same way).

32 x 32 x 2:

- Row *r* (0 at the top) of the bit-0 plane is words `2r` and `2r+1` from the Cursor Entry Pointer. Word `2r` holds columns 0 to 15, with
  column 0 in bit 15; word `2r+1` holds columns 16 to 31.
- Row *r* of the bit-1 plane is words `64 + 2r` and `64 + 2r + 1`.
- Equivalent byte view for a big-endian memory image loaded two bytes at a time: 128 bytes of plane 0, each row four bytes with the
  leftmost pixel in bit 7 of the first byte, then 128 bytes of plane 1.
- Pixel code = `(plane-1 bit << 1) | plane-0 bit`. Code 0 shows the frame buffer.
- The specification's internal note says the chip reads each row's four words at offsets +0, +1, +0x40 and +0x41 from a running pointer,
  which is the same layout.

64 x 64 x 1: four words per row (columns 0 to 15, 16 to 31, 32 to 47, 48 to 63; column 0 in bit 15 of the first), 64 rows, 256 words
(specification figure). Only the ide diagnostic `ng1vc2cursormode` writes the mode; it loads 256 words at 0x500 and sets
control bit 9. Which pixel code a set bit gives is **unknown** (see [open](#open)).

Glyph evidence beyond the figure, **established** as software expectation:

- The PROM's arrow (16 x 16, rows of two bytes in `vc1_ptr_bits` and `vc1_ptr_ol_bits`, `vc1cursor.c`) is stored with the
  first byte at the row start in each plane, and its hot spot is column 3, row 1 (`cursor.h`). That point is the arrow's tip, with the
  outline on both sides of it, only when the leftmost column is the most significant bit; this agrees with the figure. Plane 0 holds the
  fill and plane 1 the outline, so the fill is code 1 and the outline code 2.
- Linux sets words 92 and 94 to 0xff00 and clears the rest of 128: plane 1, rows 14 and 15, columns 0 to 7. It is an eight-pixel
  underline in colour code 2 for an 8 x 16 character cell, positioned with Y + 31, which again fits column 0 = bit 15.
- The X server (`rex3DisplayCursor`) builds the glyph in a 256-byte buffer from the X cursor's source and mask bitmaps, rows of 32
  bits with the leftmost pixel in bit 31 and the right edge masked to the cursor width and a height of at most 32. In the common branch plane 0 is
  `source AND mask` and plane 1 is `NOT source AND mask`, so a source-set pixel is code 1 and a mask-only pixel is code 2. When the
  cursor carries a third colour record the branch builds plane 0 = `source` and plane 1 = `source XOR mask`, so a source pixel outside
  the mask is code 3. **Established** as code reading (the branch condition, a flag in the third-colour record, was not decoded).
  `rex3InstallCursor` then loads the 128 words (256 bytes) at 0x500 with the cursor switched off, restores the control word and
  reports the hot spot.

## Position

**Established** (specification section 3.1.6, kernel `newportPositionCursor` at `newport.o` +0x524, PROM routine at 0xbfc1d8c0).

- Registers: Cursor X Location (index 2), Cursor Y Location (index 3). 16 bits each.
- Write X, then Y. The Y write copies the X value into Current Cursor X (index 4, read-only to the host) and the pair is then taken
  during the next vertical blanking, so a position change alone does not need the cursor disabled. The specification asks for the
  cursor to be disabled when the pointer (Cursor Entry Pointer) or mode changes together with the position.
- Glyph mode: the position is the glyph's upper-left corner. Crosshair mode: the position is the crosshair's centre (the specification;
  no shipped code sets a crosshair position other than through the same registers).
- The origin is **31 pixels left of and 31 lines above** the visible screen (specification). A glyph at (0, 0) therefore shows only its
  bottom-right pixel in the screen's top-left corner, and a glyph at (31, 31) is fully visible in the corner. The offset exists so a
  cursor can sit partly off the top and left.
- The kernel's routine takes pointer position (x, y) and writes `x - hotx + 29` to index 2, then `y - hoty - (b164 - b168) + 31` to
  index 3, each masked to 16 bits and sent as the three-byte register write above. It reads `DCBMODE` first, waits for the display bus to
  be idle, and writes the old `DCBMODE` back afterwards. Both bookkeeping words `b164` and `b168` start as `(TOPSCAN + 1) & 0x3ff`; the
  kernel's video-timing routine later rewrites `b164` as `1024 - (a timing field)`. For the usual 1024-line frame buffer and a 1024-line
  mode that term is zero. **Established** for the code; that the term compensates a changed `TOPSCAN` (vertical pan) is **inferred**.
- While a per-board word (`+148`) is non-zero the routine stores (x, y) at `+140` and `+144`, adds one to the word and returns without
  touching the VC2. `newportInitialize` and `newportSetVideoTiming` set the word to 1 around their work and clear it; the pixel DMA
  code clears it and then calls the routine with the saved position. **Established** for the code, **inferred** for the purpose (keeping
  cursor writes off the display bus during those operations).
- Linux positions the console cursor at `col * 8 + 29` and `row * 16 + 31` (21 instead of 29 on board revision 3).

### Where the constant 29 comes from

The specification's origin is 31 pixels left of the visible area, but both IRIX and Linux add 29 to X on most boards. The offset is a
property of the video-timing table, which sets where the internal cursor-position channel `HPOS_VC` starts. In the PROM library's
`np_timing.h` the visible line of every mode asserts `HPOS_VC` before `VIS_LN_VC` by:

- **18** state-run units (2 pixels each) in the unsuffixed tables, which the PROM uses for boards below revision 3, and in the `_r4`
  tables (board revision above 3 with a Bt445 revision above 0xa);
- **14** units in the `_r3` tables, which the PROM uses for board revision 3 and for later boards with an older Bt445 revision. That is
  8 pixels less.

`ng1_init.c` picks the set from the board and Bt445 revisions in this way. Linux's switch from 29 to 21 on board revision 3 is the same 8
pixels. **Established** for the table contents and the selection (decoded from `np_timing.h` for every table: 18 or 14, and 17 in one
case, `n1024_70_r3`) and for Linux's constant; that the 8 pixels are the difference in the cursor origin is **inferred** (the numbers fit:
offset 29 at lead 18 and 21 at lead 14). Two things are not settled: IRIX's routine has no revision term, so whether the kernel's own
tables for a revision 3 board put `HPOS_VC` 18 units ahead is **unknown** (the kernel's tables were not decoded); and the specification's own
figure for the lead is 20 units, which neither set matches.

## Hot spot

**Established** (kernel `newportPrivate` request 21001 in `newport.o`, X server `rex3InstallCursor` and `rex3DisplayCursor`, which print
`ng1InstallCursor: SET_CURSOR_HOTSPOT failed`).

- The hardware has no hot-spot concept. The position registers always take the glyph's top-left.
- The X server passes the cursor's `xhot` and `yhot` as two unsigned 16-bit values in a four-byte structure with request 21001. The kernel
  stores them in the board record (at `+136`, `+138`) and immediately repositions the cursor from the last pointer position it saw, so a
  cursor image change takes effect without waiting for the mouse.
- Every later position update subtracts them as shown above. The X server's crosshair path passes (0, 0).
- The X server does not write the VC2 position registers. `newportPositionCursor` is also referenced from a data table in `newport.o`
  (offset 0x60 of `.data`), **inferred** to be the board's cursor-position entry that the generic graphics layer calls with the pointer
  position.

## Enable and mode

Display Control Register, index 0x10, 16 bits (specification section 3.1.3; all bits clear at power-up). Macro values are from the
MCO diagnostics' copy of the kernel header; the Newport tree names the macros without values. The values agree with the `0x9b` the
PROM and kernel write.

| Bit | Name | Meaning | IRIX use |
|---|---|---|---|
| 0 | VINTR enable | vertical interrupt | set at init |
| 1 | display (blackout off) | 0 forces blanking to the DAC | set at init; the X server's `rex3BlankScreen` clears it to blank and sets it to unblank |
| 2 | video timing enable | | kernel `initVC2` writes 4 first (0x44 for an interlaced mode) |
| 3 | DID function enable | | set at init |
| 4 | **cursor function enable** | the VC2 reads cursor data; when clear, "undefined" cursor values | set at init; the X server sets and clears it with bit 7 |
| 5 | gensync enable | | kernel ORs 0x20 with bit 10 for one flag combination |
| 6 | interlace | | set from a timing flag |
| 7 | **cursor display enable** | 0 drives zeros on the cursor lines, 1 drives the cursor; takes effect at once, not at the next retrace | set at init; the X server sets and clears it with bit 4 |
| 8 | **cursor mode** | 0 glyph, 1 crosshair | X server sets it for the crosshair cursor, clears it for a glyph |
| 9 | **cursor size** | 0 32 x 32 x 2, 1 64 x 64 x 1 (glyph mode only) | only the ide `ng1vc2cursormode` command |
| 10 | genlock select | 0 Gen0, 1 Gen1 | |

**Established** for each use:

- PROM: reads the control register, ORs **0x9b** (bits 0, 1, 3, 4 and 7) and writes it back (0xbfc1d2bc to 0xbfc1d2f4; the source names
  the same five). Then the glyph is loaded and the position set to (0, 0), so the cursor is on but entirely off screen.
- Kernel: `initVC2` calls `initNg1Cursor` (glyph, pointer 0x500, position (0, 0), colours) first. `newportInit` then does the same read, OR
  0x9b and write.
- X server `rex3CursorOn` sets or clears **0x90** in a software copy of the register and writes the whole copy. `rex3InstallCursor` clears
  0x90 before loading a glyph and restores the copy afterwards. `rex3DisplayCursor` sets bit 8 in the copy (and writes it, with the
  hot spot reset to 0, 0) when the cursor shown is the X server's special cross-hair cursor, and clears bit 8 otherwise. That the
  compared cursor is the cross-hair one is **inferred**: the module owns the string `_SGI_CROSSHAIR_CURSOR` and the code does the
  comparison before any glyph work.
- A routine inside the symbol range of `rex3CopyWindow` (it issues kernel request 21006, which looks like a video-mode change)
  ORs **0x9f** into the control register: bit 2 as well. **Inferred** to be a display re-initialisation.
- No write of bit 9 was found in `ng1.so`, the kernel or the PROM, other than in the ide command. The X server module was searched for
  display-bus writes to the VC2 control register (all users of `DCBMODE` 0x0084100b); `rex3CopyWindow`'s range was only read around
  those writes.

The Cursor Entry Pointer (index 1) is latched at vertical blanking, so the glyph never changes mid-frame. Cursor error flag: bit 2 of the
Configuration register (index 0x1f) goes high if cursor processing misses the start of a line; no shipped code was seen to read it.

## Colours

**Established** (XMAP9 specification section 3.4.4, Table 3k; the PROM, kernel and X server writes).

- The VC2 sends two cursor bits per pixel on `CURA` and `CURB` (even and odd pixel). The XMAP9 gives the cursor priority over every other layer
  and ignores window display IDs for it. A code of zero passes the frame buffer through. Otherwise it makes the 13-bit colour-map address
  `(CRS 3 << 5) | (0 << 2) | code`, with CRS 3 the "cursor colour-map MSB" register, which the XMAP9 never modifies. IRIX sets it to **0xE7**
  (PROM `Ng1XmapInit` and kernel `initXMAP9`), so the four cursor entries are colour-map addresses **0x1CE0, 0x1CE1, 0x1CE2 and 0x1CE3**.
- **Inferred**: code 1 is the pixel whose bit-0 plane bit is set, 2 the bit-1 plane, 3 both. The specification's output names pair
  `CUR[1:0]` with the two planes in the figure only by their labels.

| Writer | Entries written | Values |
|---|---|---|
| PROM `Ng1CursorInit`, kernel `initNg1Cursor` | 0x1CE0, 0x1CE1, 0x1CE2 (the address is written once and the three colours follow) | black, red (0xff, 0, 0), white; the PROM passes foreground red and background white |
| X server `rex3DisplayCursor` | 0x1CE1, 0x1CE2, 0x1CE3, each with its own address write | the cursor's foreground colour, background colour, and a third colour from the cursor's extra record or black |

Colours are the high byte of each 16-bit X colour. Entry 0x1CE0 is not touched by the X server, which agrees with code 0 being
transparent. A flag in the board record (`+1228`) chooses the path: with it set the three bytes go out as red, green, blue; with it
clear the server writes one luminance value (a weighted sum of the three, truncated) in all three bytes. **Established** for the code; the flag's meaning
(grey display) is **inferred**.

### Colour-map access

Both colour-map chips are written at once with `DCBADDR` 1 (`DCB_CMAP_ALL` in Linux). Per colour: `DCBMODE` 0x008480b1 (CRS 3, one byte,
no acknowledge, chip-select width 4) and a byte store of **7** at `DCBDATA0`+3; `DCBMODE` 0x1084808a (CRS 0 with auto-increment, two bytes,
`SWAPENDIAN`) and a halfword store of the address at `DCBDATA0`+2; `DCBMODE` 0x008480a3 (CRS 2, three bytes) and a word store of
`red << 24 | green << 16 | blue << 8`. Then, after the last colour, a byte store of **3** to CRS 3. **Established** (kernel
`initNg1Cursor`, X server, and the PROM routine at 0xbfc1d9ac to 0xbfc1dac0). The PROM source comments say writing the table needs the
composite blanking disabled and calls 7 that state, and 3 the normal one ("trip on half full"), so CRS 3 is the colour-map command
register with a bit that holds blanking off during a load: **inferred** from comments, no colour-map specification held. That the
address auto-increments after each RGB triple (the PROM and kernel rely on it for entries 0x1CE0 to 0x1CE2) is likewise **inferred**.

## What a model has to do

1. Keep the VC2's 32K-word RAM and its registers (index 0 to 0x10 and 0x1f), the index latch and the two-byte phase flag. A write to index
   7 resets the phase.
2. Honour three-byte register writes and the byte-pair reads and writes through CRS 1, 2 and 3.
3. When control bits 4 and 7 are both set, in glyph mode with bit 9 clear, draw the 32 x 32 glyph with its top-left at screen pixel
   `(X - 31, Y - 31)` per the specification. The shipped IRIX and Linux code behaves as if the X origin were 29 on most boards (21 on
   board revision 3); a model that follows the specification and the drivers together should take the origin from a property of the
   modelled timing table, or use 29 and accept a 2-pixel difference from the specification. Read both planes from the entry pointer; code 0
   shows the frame buffer and codes 1 to 3 give the colour-map entry `(XMAP9 CRS 3 << 5) + code`.
4. In crosshair mode draw a crosshair through (X, Y); the colour code is **inferred** to be 1 (the specification's block diagram feeds the
   crosshair into the same two-bit output as code 01).
5. Keep position and pointer latched until the next vertical blanking.

## Open

Entered in [questions](../../questions/README.md#vc2-cursor).

- **Origin of the X offset for each board.** Both IRIX and Linux use 29, Linux 21 on board revision 3, and the PROM tables for revision 3
  put the position channel 8 pixels later. Unknown: what the IRIX kernel's tables do on revision 3, and the exact relation between the
  position-channel lead and the cursor origin. Would settle it: decoding the kernel's timing tables in `newport_init.o` and the
  `HPOS` position in them; a published description of the VC2's internal pixel counter.
- **Out-of-range position.** The kernel's routine sends a 16-bit value with no clamp; the specification gives a maximum of 2047 for X in
  the text and 4095 in the register table (and 2047 for Y). What the chip does with a larger or negative (wrapped) value is unknown.
  IRIX can produce such values: a pointer at x = 0 with a hot spot of 31 gives -2 before the 16-bit mask.
- **64 x 64 x 1 colour.** Which two-bit code a set bit in the one plane drives, and which of `CURA` and `CURB` bit it uses. The
  specification does not say. Only the ide diagnostic uses the mode.
- **Crosshair appearance.** Line width, whether the full screen is covered in both axes, and its colour code are specified only as
  "full screen crosshair". The X server's selection of the mode is inferred.
- **X server glyph rows below the cursor height.** `rex3DisplayCursor` copies at most 32 rows of the cursor; whether the buffer's
  other rows are cleared before it is loaded was not read.
- **Configuration revision.** The VC2 revision comes from index 0x1f bits 7 to 5 (000 for the first revision per the specification);
  Linux prints the field. Differences between revisions are not described anywhere read.
