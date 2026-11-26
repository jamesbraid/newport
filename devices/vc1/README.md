# VC1 video controller (Indigo Entry graphics board)

The chip that generates video timing, the hardware cursor and the per-pixel display-mode lookup on the Indigo's Entry (LG1)
graphics board, and holds the tables for them in a small external SRAM. Software reaches it only through the REX1 chip's
`RWVC1` port, with a function selector in `CONFIGSEL` (see [REX1](../rex1/README.md#the-off-chip-ports)). The same part
number also appears on the Indigo's Express (GR2) boards; this page covers the Entry board's use only.

Grades follow [AGENTS.md](../../AGENTS.md). Sources: the IRIX 6.5 IP20 boot object `lg1.a` (member `light_init.o`, functions
`initVC1`, `vc1LoadSRAM`, `initLg1Cursor`, `lightInitInfo`; member `light.o`, functions `lightPositionCursor`,
`lightSetDisplayMode`, `light_read_displaymodes`, `light_read_scan`, `light_read_auxmapindex`), the IP20 PROMs 4.0.5D
(070-8116-004) and 4.0.5G (070-8116-005), the NetBSD sgimips `light.c` and `lightreg.h` (public driver; names and the
SYS_CTL bits), and a photograph of a board. MAME's `vc1.cpp` and `light.cpp` are notes from another project: where this page
agrees with them it says so, and nothing here rests on them. Nothing was measured on a board.

## Identity

- Chip marking, **observed** in a photograph of an LG1 board (Library `photos/sgistuff-indigo/indigo-lg1a-1001.jpg`): an LSI
  Logic package printed `L1A6654 VC1 REV B`. A second LSI Logic part beside it reads `L1A6651 LUT1 REV A` (the colour map, see
  [Bt479 and LUT1](../bt479/README.md)). Board part number `030-8077-004 REV A` is printed on the board. Photographic
  reading of printed text; the revision letters are what the photo shows, not a statement about what software reads.
- Revision as software sees it: **established** that the kernel reads a value from the chip, subtracts one and stores the
  result in the board info structure (byte 0x2a of what `lightInfo` copies out). The read is: `CONFIGSEL` 5, write 0 (address
  high); `CONFIGSEL` 4, write 5 (address low); `CONFIGSEL` 3, one microsecond, read `RWVC1`; revision = (value & 7) - 1. If the
  result is 0, `lightInit` prints a console warning and does not initialise the VC1 (`initVC1` is skipped). The diagnostic
  `lg1_vc1regs` prints "VC1 Chip Revison %d". What value a real rev B returns: **unknown** (no recorded run).

## How the chip is addressed

Established. The three ports in the REX1 page (`WCLOCK`, `RWDAC`, `RWVC1`) share one three-bit selector, `CONFIGSEL`. For the
VC1 the selector value picks which of its eight windows the next `RWVC1` access uses:

| `CONFIGSEL` | Window | Established use |
|---|---|---|
| 0 | internal register file | data port; each access moves to the next byte. The VC1's own address counter (below) is set first. |
| 1 | display-mode (XMAP) table | same byte-at-a-time data port, over the mode table; 2-byte entries |
| 2 | external SRAM | data port, byte at a time, address counter increments |
| 3 | test | read returns the revision value above; writes never seen |
| 4 | address, low byte | write the low 8 bits of the 16-bit address counter |
| 5 | address, high byte | write the high 8 bits |
| 6 | SYS_CTL | one byte of chip control |
| 7 | unused | no shipped code selects it |

`vc1LoadSRAM` also reads the word at board offset 0x7fc after every SRAM data byte and discards it; no register is defined there, so a model must accept a read (any value) at 0x7fc without a fault. Every write stores the byte in `RWVC1` and then in its GO alias (offset + 0x800); the second store is what moves the byte to
the chip. A read writes `CONFIGSEL`, reads the GO alias (discarding the result), waits, then reads `RWVC1` (the PROM and
NetBSD agree; the kernel's colour-map reads read the GO alias directly and use its value). **Established** from every routine
named above. The 16-bit address counter is shared by windows 0, 1 and 2 and auto-increments after each data byte
(inferred: `vc1LoadSRAM` writes up to 0x600 bytes without touching the address registers between bytes; `light_read_scan`
reads 0x300 words the same way).

A qtest discriminator: write address 0x1234 through selectors 5 and 4, write three bytes through selector 2, set the address
back and read them, and check the address reads back as 0x1237 (inferred increment).

## SYS_CTL (`CONFIGSEL` 6)

Established as a byte; bit roles from NetBSD (software expectation) and the kernel's use. `initVC1` ends by writing 0xfc. The
PROM writes 0x03 first (video and cursor off), loads its tables, then writes 0xb9 at the end of its console initialisation;
its unblank routine (called with an argument) then clears bit 2 for 1 and sets it for 0 using a read-modify-write
(`CONFIGSEL` 6, read back, change bit 2, write back). The kernel's `initVC1` writes 3 first, then 0xfc.

| Bit | Value | Role | Grade |
|---|---|---|---|
| 2 | 0x04 | video output on (clear: blank) | established for the sense: the PROM's blank clears it and NetBSD turns video off by clearing it |
| 4 | 0x10 | cursor generator (NetBSD name `CURSOR`) | inferred |
| 5 | 0x20 | cursor displayed (NetBSD name `CURSOR_ON`) | inferred |
| others | | 0xfc sets bits 7:2; 0x03 sets bits 1:0. Roles: **unknown** | unknown |

## Internal register file (`CONFIGSEL` 0)

The 16-bit address counter is first set to the register's offset (through `CONFIGSEL` 5 and 4), then bytes are written or read
through `CONFIGSEL` 0, high byte first for 16-bit values. Offsets used by shipped software, all **established** as
offsets and values; the field names are descriptive (the shipped software gives no names), and the pairing of two
consecutive bytes as one 16-bit big-endian value is inferred from the order they are written in.

| Offset | Written by | Value at init | Reading |
|---|---|---|---|
| 0x00 (2 bytes) | `initVC1` | 0x88, 0x00 | pointer to the first video timing entry (in a form where the high byte's top bit is set) - **inferred** from its position before the 0x14 write and the 0x4000/0x3000 neighbours below |
| 0x14 (2 bytes) | `initVC1` | 0x1d, 0x00 | video enable control - **unknown** role beyond the write |
| 0x20 (2 bytes) | `initLg1Cursor` | 0x30, 0x00 | cursor glyph pointer: 0x3000 is the SRAM address `initLg1Cursor` clears, **inferred**; the X server sets 0x07, 0x00 (SRAM 0x0700), see [cursor](cursor.md) |
| 0x22 (2 bytes) | `lightPositionCursor` | x + 0x8c - x hotspot, high byte then low | cursor x position (high, low); **established** as the location and the added constant 0x8c |
| 0x24 (2 bytes) | `lightPositionCursor` | y + 0x27 - y hotspot, high then low | cursor y position; added constant 0x27 |
| 0x26 | `initLg1Cursor` | 0x00 (after 0x02, 0x40, 0x02, 0x40 written to 0x22 to 0x25) | cursor mode - inferred |
| 0x40 (2 bytes) | `initVC1` | 0x40, 0x00 | display-id frame table pointer: matches `frametable` at SRAM 0x4000 - **inferred** |
| 0x42 (2 bytes) | `initVC1` | 0x46, 0x00 | end of that table: SRAM 0x4600 is the end of the 0x600-byte `frametable` - **inferred** |
| 0x44, 0x45 | `initVC1` | 0xcc, 0x04 | horizontal divide and modulus for the display-id generator - unknown role |
| 0x60, 0x61 | `initVC1` | 0x01, 0x01 | blank-out controls for even and odd lines - unknown role |
| 0x62 | read by `light_read_auxmapindex` | | auxiliary map index (read-back only) |

The X server's different values for registers 0x40 to 0x45 and 0x60 to 0x63, the mode-word layout and how DIDs pick a colour-map bank are on [display IDs and the mode table](did-xmap.md); the cursor glyph format and colours are on [the cursor page](cursor.md).

## Read-back widths (the PROM and ide power-on tests)

Which bits of each register a working board must keep, as the shipped read-back tests expect them. **Established** as what the
software checks: read in full from the 4.0.5G PROM (070-8116-005; the test at 0xbfc06264 to 0xbfc063c8, its width lookup at
0xbfc072b0 (a chain of compares on window and offset, not a data table), the write-and-compare routine at 0xbfc07400) and from the ide diagnostic source for the board
(`stand/arcs/ide/fforward/graphics/LIGHT/vc1.c`, functions `vc1_length` and `test_vc1_register`, **[source]**; the PROM build of the
test is `lg1_pon` in `rex.c` of the same directory). The
4.0.5D PROM runs no such test (its image has no "VC1 power on test failed" text). What the chip does with bits it does not keep
is **inferred**: both tests expect the bits above the width to read back 0 after ones were written to them, and software never
reads them otherwise.

| Offset (window 0) | Name from the shipped header | Bits kept | Expected read-back for 0x5555 / 0xaaaa |
|---|---|---|---|
| 0x00 | VID_EP | 16 | 0x5555 / 0xaaaa |
| 0x20 | CUR_EP | 16 | 0x5555 / 0xaaaa |
| 0x22 | CUR_XL | 11 | 0x555 / 0x2aa |
| 0x24 | CUR_YL | 12 | 0x555 / 0xaaa |
| 0x26 | CUR_MODE | 8 | 0x55 / 0xaa |
| 0x27 | CUR_BX | 8 | 0x55 / 0xaa |
| 0x28 | CUR_LY | 11 | 0x555 / 0x2aa |
| 0x40 | DID_EP | 16 | 0x5555 / 0xaaaa |
| 0x42 | DID_END_EP | 16 | 0x5555 / 0xaaaa |
| 0x44 | DID_HOR_DIV | 8 | 0x55 / 0xaa |
| 0x45 | DID_HOR_MOD | 3 | 0x5 / 0x2 |
| 0x60 | BLKOUT_EVEN | 8 | 0x55 / 0xaa |
| 0x61 | BLKOUT_ODD | 8 | 0x55 / 0xaa |
| 0x62 | AUXVIDEO_MAP | 8 | 0x55 / 0xaa |
| window 1, offset 0 (entry 0 of the display-mode table) | MODE_REG_0_E | 16 | 0x5555 / 0xaaaa |

How the test touches a register, so a model can pass it byte for byte: set the address counter to the offset (select 5 high byte,
select 4 low byte), select the window, write the high byte of the 16-bit pattern then the low byte (two consecutive bytes, so the
second lands at offset + 1), set the address again, select the window, and read two bytes, each with the
usual GO read then plain read, whatever the width; the second byte is compared only for a width above 8. A 16-bit register compares both bytes as one big-endian value against `pattern & ((1 << width) - 1)`;
an 11 or 12-bit register therefore keeps only bits 2:0 or 3:0 of its first (high) byte; a register of 8 bits or less compares its own byte
only, which holds the pattern's high byte (equal to the low byte for these patterns). For CUR_XL the test also writes the same two bytes at 0x24 before
reading 0x22 back. The PROM runs the list twice, with 0x5555 and 0xaaaa, in the order above; a mismatch makes the board test return failure and the System Maintenance Menu
reports "Graphics diagnostic *FAILED*". The ide full test (`test_vc1`) adds the patterns 0 and 0xffff and every entry of window 1: 64 sixteen-bit entries,
offsets 0x00 to 0x3e (the "even" half, `MODE_REG_n_E`) and 0x40 to 0x7e (the "odd" half, `MODE_REG_n_O`), all 16 bits wide. Registers the test does not
list (0x02 to 0x14, 0x2a to 0x30, 0x46 to 0x52, 0x63 and above) have no expected width.

May the model take these as software expectations? Yes: a register file that stores each byte masked to the width above (the second byte written
at offset + 1 also being stored, since the test writes a byte there) passes the PROM test, and storing plain bytes does not (11, 12 and 3-bit rows
fail). They are what the diagnostics expect of a working board, not measured behaviour, and the patterns (0x5555, 0xaaaa, 0, 0xffff) have equal bytes, so the
8-bit rows cannot tell a byte from a masked byte. A qtest can discriminate: write 0x55 then 0x55 at
0x22 through select 0 and read one byte back, expecting 0x05; at 0x45, write 0x55 and expect 0x05; at 0x24, write 0xaa 0xaa and expect 0x0a.

After the registers, `initVC1` clears the first 0x40 bytes of the display-mode table through window 1 (address counter at 0;
see below). `initLg1Cursor` does the cursor setup: clears 0x100 bytes of SRAM at 0x3000 (the cursor glyph
area, all zero so no cursor shape), then sets registers 0x20 to 0x27 as shown.

Cursor placement, **established** from `lightPositionCursor`: it waits until `CONFIGMODE` bits 28:24 and bit 0 clear, writes
x (high then low byte) to register 0x22 and y to 0x24. When SYS_CTL (as read back) shows bit 0 set and the saved `CONFIGSEL`
is 1 or 2 it first drops its own `CONFIGSEL` use, writes registers around the update and restores them; the exact
meaning of that guarded sequence (a workaround for a hazard while the display-mode window is in use) is **unknown**.

## SRAM layout

Established from `initVC1`, `vc1LoadSRAM` and `initLg1Cursor`. The SRAM size is **inferred** only as at least 32K bytes for the kernel (highest address 0x4800 + 0x8a); the X server also uses 0x0700, 0x0900 to 0x0eff and a line table at 0x2000 or 0x5000, so a model should allow 64 KiB. No shipped code states the part size.

| SRAM address | Contents | Loaded from |
|---|---|---|
| 0x0000, 0x23a bytes (PROM: 0x232) | video timing line table | `vtg_ltable` in the kernel, a separate 0x232-byte table in the PROM |
| 0x0800, 0x2c bytes (PROM: 0x2a) | video timing frame table | `vtg_frtable` |
| 0x3000, 0x100 bytes | cursor glyph | zeros |
| 0x4000, 0x600 bytes | display-id frame table | generated: 0x300 pairs of 0x48, 0x00; the last pair 0x48, 0x40 |
| 0x4800, 0x8a bytes | display-id line table | `did_linetable` |

The table bytes are in [timing-tables.md](timing-tables.md). The PROM 4.0.5D and 4.0.5G carry the same PROM tables. The
kernel's and the PROM's tables are different byte strings; both are **established** as bytes. What each entry means (line type,
count, sync polarity), and the 1024 by 768 timing they encode: **unknown**. Route tried: the entries share a
repeating-record structure (header 0x0c .. 0x8c bytes then counted runs) with the Express board's table at the neighbouring
PROM address (0xbfc4cf90 starts the table the LG1 code uses; the Express boards use a table after a monitor string just
before it), but no VC1 datasheet is held and no shipped code interprets the bytes. Next route: the Library for the LSI Logic
VC1 data sheet, then the Express VC1 headers in the techomancer `gr2` repository (a public reference, whose reading counts as
exposure for the Express family only).

## Display-mode (XMAP) table

Window 1 holds the per-pixel display-mode lookup: entries of two bytes, entry n at address 2 * n. **Established**:
`lightSetDisplayMode` writes address 0 (high) / 2n (low) through selectors 5 and 4, then two bytes (high, low of a 16-bit
mode value) through selector 1; `light_read_displaymodes` reads 0x40 entries (0x80 bytes); `initVC1` writes 0x40 zero bytes after setting
the address to 0 (32 entries), and the retrace handler walks 32 swap slots. How many entries the chip has: the ide read-back test ([widths](#read-back-widths-the-prom-and-ide-power-on-tests)) expects 64, all 16 bits wide (software expectation); more than 64: **unknown**. The first 32 start out zero, and the mode value's meaning (which buffer, which colour-map bank) is
**unknown**, except one bit: the kernel's retrace handler (`lightRetraceHandler`, `light_retrace.o`) sets or clears bit 1 of the
second byte of the entry that a pending swap-buffer request names, once the request counts down to zero at vertical retrace.
Bit 1 of that byte selects between the two image buffers of a double-buffered window, **inferred** from its use only for
`lightSchedSwapBuf` requests.

## Readback and the retrace handler

Added from the kernel retrace and cursor code and the X server (IRIX 5.3 and 6.5). Tags and addresses are on the [LG1 board page](../../platforms/lg1/README.md#kernel-and-x-server-irix-53-and-65-what-the-model-needs-beyond-the-prom).

- **Every window is read, not only written (established).** `light_read_displaymodes` reads 0x40 two-byte entries from window 1, `light_read_scan` reads the frame and line tables from window 2 after loading their pointers from register 0x40 and 0x41 of window 0, `light_read_auxmapindex` reads register 0x62, and `lightReadDisplay` copies all of them to user space (request 20006). A model must return what was stored.
- **Read cycle (established for the sequences, inferred for the cause).** A single byte is read with `CONFIGSEL`, a GO read of `RWVC1` whose value is ignored, a delay and a read of `RWVC1`. A run of bytes is read with one ignored GO read and then only GO reads, one per byte. Both are consistent with a GO read that returns the byte fetched by the previous GO read and starts the next fetch (advancing the address counter), and a plain read that returns the byte of the last fetch. A model where a GO read returns and advances at once would make every bulk reader lose its first byte.
- **The address counter is readable (established).** The retrace handler and `lightPositionCursor` select `CONFIGSEL` 4, read, and select 5, read, to learn the low and high bytes of the counter, then write the same bytes back (the low byte is stored again unchanged right after the read). `CONFIGSEL` itself is read first and restored last. A flat counter that reads back what the last write or auto-increment left satisfies this.
- **The odd-address workaround (established as a sequence, inferred as a mechanism).** If the saved low byte is odd and the saved selector is 1 or 2, the handler first sets the address to 0x0080 and reads window 0 once, and when it has finished steps the counter back by one and writes that byte through the saved window. The byte it writes was read from register 0x80, so for the restore to be harmless register 0x80 must read as the last byte transferred through any data window (a data latch). **Unknown:** whether register 0x80 exists in the file otherwise; no shipped code writes it.
- **The X server initialises the VC1 itself.** After the kernel it rewrites registers 0x40 to 0x45 and 0x60 to 0x63 and loads the SRAM at other addresses; the values are on the board page. The register meanings are unchanged ("unknown"); a model that stores and returns them is enough for software, and the display-id mechanism that turns the tables into a colour-map bank and buffer per pixel remains the open question below.

## What the PROM does with it

Established that the PROM mirrors the kernel: it clears the cursor and mode window, loads the two timing tables from its own
copy (lengths 562 and 42), writes the same register values, and finishes by writing SYS_CTL 0xb9 (video off), then its
unblank routine turns the output on. Read in full: the table loads and register writes at PROM 4.0.5D 0xbfc0fd00 to
0xbfc0fe40 and 0xbfc10040 to 0xbfc100dc; the function mapping to the kernel's `initVC1` is by pattern (the stores match one for
one), so **inferred** for the parts not compared byte by byte.

## Open

See the open questions list in [questions/README.md](../../questions/README.md): the table entry format, the register map's
remaining fields and the SRAM size.
