<!-- generated from devices/rex1/registers.toml by defs-gen - do not edit, change the source -->
<!-- defs-gen 3 -->
<!-- input sha256 f106ffd4ce6216cbcb15142d0f93d5a5d571bf5121dd2e782db212231ef32133 -->

# REX1 raster engine on the Indigo Entry graphics board (LG1)

Register file of the REX1 chip as the Indigo's Entry graphics board presents it on the GIO graphics slot. Offsets are bytes from the board base (0x1f3f0000 for the first head, 0x1f3f8000 for a second). Every register is 32 bits wide. A register written at its offset is only stored (the SET alias). The same register at offset + 0x800 (the GO alias) is stored and then the latched command is executed. Names are the ones the shipped diagnostics (ide) print for the REX register test, where it prints one; the rest use the names of the NetBSD sgimips light driver. The three off-chip ports (WCLOCK, RWDAC, RWVC1) are covered here as REX registers; the chips behind them are in devices/vc1 and devices/bt479. Grades follow AGENTS.md: established means the whole routine was read in the shipped Indigo kernel graphics driver or the Indigo PROM; inferred is a reading with the reasoning given; unknown means no shipped software settles it. Nothing was measured on a board.

Unit `rex1`, macro prefix `REX1`.

Every item has a grade: established, inferred or unknown. A grade says how the item was derived from its source; it does not claim the item was measured on silicon.

## Registers

| Register | Offset | Access | Width | Count | Space | Reset | Grade | Source |
|---|---|---|---|---|---|---|---|---|
| `command` | 0x0 | rw | 32 |  |  | unknown | established |  |
| `aux1` | 0x4 | rw | 32 |  |  | unknown | established |  |
| `xstate` | 0x8 | rw | 32 |  |  | unknown | established |  |
| `xstarti` | 0xc | rw | 32 |  |  | unknown | established |  |
| `xstartf` | 0x10 | rw | 32 |  |  | unknown | established |  |
| `xstart` | 0x14 | rw | 32 |  |  | unknown | established |  |
| `xendf` | 0x18 | rw | 32 |  |  | unknown | established |  |
| `ystarti` | 0x1c | rw | 32 |  |  | unknown | established |  |
| `ystartf` | 0x20 | rw | 32 |  |  | unknown | established |  |
| `ystart` | 0x24 | rw | 32 |  |  | unknown | established |  |
| `yendf` | 0x28 | rw | 32 |  |  | unknown | established |  |
| `xsave` | 0x2c | rw | 32 |  |  | unknown | established |  |
| `minorslope` | 0x30 | rw | 32 |  |  | unknown | established |  |
| `xymove` | 0x34 | rw | 32 |  |  | unknown | established |  |
| `colorredi` | 0x38 | rw | 32 |  |  | unknown | established |  |
| `colorred` | 0x3c | rw | 32 |  |  | unknown | established |  |
| `colorgreeni` | 0x40 | rw | 32 |  |  | unknown | established |  |
| `colorgreen` | 0x44 | rw | 32 |  |  | unknown | established |  |
| `colorbluei` | 0x48 | rw | 32 |  |  | unknown | established |  |
| `colorblue` | 0x4c | rw | 32 |  |  | unknown | established |  |
| `slopered` | 0x50 | rw | 32 |  |  | unknown | established |  |
| `slopegreen` | 0x54 | rw | 32 |  |  | unknown | established |  |
| `slopeblue` | 0x58 | rw | 32 |  |  | unknown | established |  |
| `colorback` | 0x5c | rw | 32 |  |  | unknown | established |  |
| `zpattern` | 0x60 | rw | 32 |  |  | unknown | established |  |
| `lspattern` | 0x64 | rw | 32 |  |  | unknown | established |  |
| `lsmode` | 0x68 | rw | 32 |  |  | unknown | established |  |
| `aweight` | 0x6c | rw | 32 |  |  | unknown | established |  |
| `rwaux1` | 0x70 | rw | 32 |  |  | unknown | established |  |
| `rwaux2` | 0x74 | rw | 32 |  |  | unknown | established |  |
| `rwmask` | 0x78 | rw | 32 |  |  | unknown | established |  |
| `smask1x` | 0x7c | rw | 32 |  |  | unknown | established |  |
| `smask1y` | 0x80 | rw | 32 |  |  | unknown | established |  |
| `xendi` | 0x84 | rw | 32 |  |  | unknown | established |  |
| `yendi` | 0x88 | rw | 32 |  |  | unknown | established |  |
| `smask2x` | 0x4790 | rw | 32 |  |  | unknown | established |  |
| `smask2y` | 0x4794 | rw | 32 |  |  | unknown | established |  |
| `smask3x` | 0x4798 | rw | 32 |  |  | unknown | established |  |
| `smask3y` | 0x479c | rw | 32 |  |  | unknown | established |  |
| `smask4x` | 0x47a0 | rw | 32 |  |  | unknown | established |  |
| `smask4y` | 0x47a4 | rw | 32 |  |  | unknown | established |  |
| `aux2` | 0x47a8 | rw | 32 |  |  | unknown | established |  |
| `diagvram` | 0x47d8 | rw | 32 |  |  | unknown | inferred |  |
| `wclock` | 0x47e4 | rw | 32 |  |  | unknown | established |  |
| `rwdac` | 0x47e8 | rw | 32 |  |  | unknown | established |  |
| `configsel` | 0x47ec | rw | 32 |  |  | unknown | established |  |
| `rwvc1` | 0x47f0 | rw | 32 |  |  | unknown | established |  |
| `togglectxt` | 0x47f4 | w | 32 |  |  | unknown | inferred |  |
| `configmode` | 0x47f8 | rw | 32 |  |  | unknown | established |  |
| `xywin` | 0x47fc | rw | 32 |  |  | unknown | established |  |

### Register `command`

Drawing command. Bits 31:28 hold the logic operation, the low bits the opcode and flags listed as CMD_ constants. A write at 0x000 stores it; a write at 0x800 (or a read of 0x800) executes the command that is now latched, using the coordinate and colour registers as they stand. The PROM's probe writes 0 here and reads 0x800 (a no-op); the kernel's glyph path writes the command, then writes ZPATTERN at its GO alias once per row. A qtest can discriminate: a command written at 0x000 draws nothing, the same word at 0x800 draws, and a read of 0x800 draws what the latched command says. Bits 27:20 of values the kernel and PROM write are zero except bit 23 and bit 24 (ZOPAQUE, ZCONTINUE: not set by shipped code) and bit 21 (all three) and bit 16 (second only) in the pixel-memory probe commands 0x30200021, 0x30210021 and 0x30200023 that lightInitInfo and the PROM board-info routine use (see the CMD_PIXMEM constants and rwaux1). Bit 21 is inferred to be host data through RWAUX1, bit 1 of the last to be a read opcode, and bit 16 is unknown. The direction a pattern or block draw steps y is toward YENDI (inferred from the PROM glyphs, which end at YENDI 0, and NetBSD glyphs, which end below YSTARTI), not a fixed down.

### Register `aux1`

Auxiliary control word, one per window context. initRex zeroes it. lightAux1Register builds a value from a window's saved value with bits 4:2 cleared, sets bit 4 when the request word's second field is 1, bit 2 when bit 0 of its third field is set and bit 3 when bit 1 is set, then stores it here (only for the window that owns the screen) or in the window's saved context. Which pixel behaviour each of bits 2, 3 and 4 enables: unknown, no shipped code names them. The pixel-memory probe also stores 0x100 (bit 8) here before its second write; that bit's role is unknown. ide's register test reads it back whole (test mask 0x3ff).

### Register `xstate`

Draw x state. The only shipped write is the 0x03ff0000 that precedes each full-screen clear; the role is unknown (it may be a pre-loaded x counter for block draws; no source says). Offset established by the ide test. The ide test writes all 32 bits and expects them back unmasked.

### Register `xstarti`

Draw start x as an integer. Twelve bits are kept (the ide test mask is 0xfff) and appear in XSTART at bit 15 and above: lightProbe writes 0x12345678 here and expects 0x033c0000 from XSTART. A qtest can discriminate: write 0x12345678, read XSTART at 0x14, expect 0x033c0000; whether XSTARTI itself reads back is unknown: no shipped code and not the ide test (which reads XSTART) reads offset 0xc. The ide test confirms the derivation: write at 0xc, read at 0x14, expect (value & 0xfff) << 15.

### Register `xstartf`

Draw start x, fraction. Test mask 0x7fffff. Offset read from the ide test. Software that draws only rectangles never writes it. Offset established by the ide test. A write here appears in XSTART bits 26:4 (the ide test reads 0x14, not 0x10). 'F' is the ide name; the readback shows the register feeds XSTART bits 26:4 (inferred as a write alias of XSTART).

### Register `xstart`

Draw start x, integer and fraction combined: 27 bits in the ide test mask, integer in bits 26:15. Read at offset 0x14 by the board probe after XSTARTI was written; the value read is the probe's presence test (PROBE_READBACK). Whether a write here reflects in XSTARTI: unknown.

### Register `xendf`

Draw end x, fraction (ide mask 0x7ff800).  Offset established by the ide test. Holds the end x with the integer in bits 22:11 (a write to XENDI at 0x84 reads back here as value & 0xfff shifted left 11; written directly, only bits 22:11 stick). Not a fraction field as the name suggests.

### Register `ystarti`

Draw start y as an integer, 12 bits kept; the ide test writes it and reads YSTART (0x24) expecting (value & 0xfff) << 15. Software stores 767 minus its own y, which counts up from the bottom, so the stored value is the display row counted from the top of the 768-line screen (inferred: the PROM console prints its first text row at the largest console y, and NetBSD stores unflipped row numbers). See the Y origin section of the REX1 page.

### Register `ystartf`

Draw start y, fraction.  Offset established by the ide test. Mirror of XSTARTF for y; a write appears in YSTART bits 26:4.

### Register `ystart`

Draw start y, integer and fraction combined, counterpart of XSTART. Offset inferred; no shipped code reads it. Offset established by the ide test. Combined y start, integer in bits 26:15 (the same derivation the probe uses for XSTART).

### Register `yendf`

Draw end y, fraction.  Offset established by the ide test. Holds the end y with the integer in bits 22:11, as XENDF.

### Register `xsave`

Saved x start (the x that a block-draw returns to at the start of each row, inferred from its name and the context save). lightPcxSwap saves it with the other window registers. Offset established by the ide test. Twelve bits kept.

### Register `minorslope`

Line-draw minor-axis slope. Never written by the shipped light code for rectangles, text or points. Only the name (ide) and the slot between XSAVE and XYMOVE support it. Offset established by the ide test. Written and read back unmasked.

### Register `xymove`

Copy source offset: x delta in the high 16 bits and y delta in the low 16, each source minus destination (NetBSD: dx is from_x minus to_x). It is written at the GO alias after the rectangle and the copy command are set up. The ide mask 0x7ff07ff shows eleven bits kept per half. A qtest can discriminate: write 0x00100005 at 0x34 and 0x30080329 at 0, then a copy from (x+16, y+5) happens when 0x800 is touched (the polarity of y is unsettled: NetBSD computes source minus destination in top-down rows, while the PROM copy routine stores the differences of its two coordinate pairs in an order that matches only if its second pair is the source, and no caller of it was found in the 4.0.5D console code).

### Register `colorredi`

Foreground pixel colour (the ide test reads a write back through COLORRED at 0x3c as (value & 0xff) << 11), an 8-bit index into the colour map (the board has 8 bits per pixel). The kernel's colour routine stores the index at this offset after the busy bit clears; the PROM's colour routine does too. The ide test calls the register COLORREDI with an 8-bit mask; RED because the chip's colour path starts with red.

### Register `colorred`

Red channel with fraction for shaded draws, 20 bits in the ide mask. Offset by name order. Offset established by the ide test. COLORRED holds the red channel with its integer part (COLORREDI, 8 bits) in bits 18:11.

### Register `colorgreeni`

Green channel integer (shaded draws). Never written by shipped light code. Offset from the ide name order and NetBSD. Offset established by the ide test. A write here appears in COLORGREEN bits 18:11.

### Register `colorgreen`

Green channel with fraction. Offset established by the ide test. 20 bits kept.

### Register `colorbluei`

Blue channel integer. Offset established by the ide test. A write here appears in COLORBLUE bits 18:11.

### Register `colorblue`

Blue channel with fraction. Offset established by the ide test. 20 bits kept.

### Register `slopered`

Red slope for shaded lines and spans. Not written by shipped light code. Offset established by the ide test. Slope registers are signed: the ide test expects bit 19 of the stored value to read back also in bit 20.

### Register `slopegreen`

Green slope. Not written by shipped light code. NetBSD names offset 0x54 of the configuration page WCLOCKREV, which is a different page. Offset established by the ide test. As SLOPERED.

### Register `slopeblue`

Blue slope. Not written by shipped light code. Offset established by the ide test. As SLOPERED.

### Register `colorback`

Background colour index used for pattern zeros when ZOPAQUE is set. The shipped kernel and PROM glyph paths never write it (transparent background); NetBSD does. Offset established by the ide test. Eight bits kept.

### Register `zpattern`

Pixel pattern for the pattern-enabled commands. Software writes it at the GO alias (0x860): each write draws one row of the glyph, taking pattern bits 31 downward, the row's bits shifted into the top half for 16-wide glyphs (the kernel shifts each halfword left by 16) and into bit 24 for 8-wide (NetBSD). With STOPONX, XYCONTINUE and BLOCK, y steps by one row after each write. A qtest can discriminate: set XSTARTI, XENDI, YSTARTI, write command 0x300005b9 at 0 and 0x80000000 at 0x860, and exactly one pixel at the start column is drawn.

### Register `lspattern`

Line stipple pattern. Not written by shipped light code. Offset established by the ide test. Fully read/write.

### Register `lsmode`

Line stipple mode. Not written by shipped light code. NetBSD's configuration-page name CFGMODE for offset 0x68 is a different page. Offset established by the ide test. 20 bits kept.

### Register `aweight`

Antialias weight. Not written by shipped light code. Offset established by the ide test. Fully read/write.

### Register `rwaux1`

Read/write auxiliary word used to read and write pixel memory with a draw command. lightInitInfo writes 0x01081020 here, then 0x09090909 with a 0x30210021 command, runs 0x30200023 and compares the result word read back at 0x870 with 0x01080909 or 0x09091020 to record a 0, 1 or 0xff in byte 0x29 of the board info it hands to GfxRegisterBoard. Data flow (inferred from the constants): the first write puts the four bytes 01 08 10 20 into pixels 0 to 3 of stored row 0, the second replaces exactly one pair of them with 09 (outcome 0 = pixels 2 and 3 replaced, outcome 1 = pixels 0 and 1 replaced, if the high byte is pixel 0), and the read returns the four pixels. All three commands are executed through RWAUX1's GO alias, so RWAUX1 is the data port of the probe. What each outcome means for the board (pixel memory arrangement): unknown; no object read uses info byte 0x29 afterwards. The PROM runs the probe unconditionally; the kernel runs it only when CONFIGMODE bits 7:4 read 0. A qtest can discriminate only by replaying that sequence, which needs the draw unit to move words between RWAUX1 and the frame buffer; any model that yields 0x01080909 or 0x09091020 satisfies every shipped reader, and a choice between them is an approximation.

### Register `rwaux2`

Second read/write auxiliary word. Not written by shipped light code. Offset established by the ide test. Fully read/write.

### Register `rwmask`

Plane write mask for read/write pixel access. lightInitInfo and the PROM write 0xff (all eight planes) before the pixel-memory probe. The ide mask 0xffff shows sixteen bits kept.

### Register `smask1x`

Screen mask 1, x range: maximum x in bits 25:16 and minimum x in bits 9:0, each clipped to 0..1023 (the object clamps with 0x3ff). Software computes the window's visible rectangle clipped to the screen and writes it here when window 1 is the active one.

### Register `smask1y`

Screen mask 1, y range, same packing, clipped to 0..767 (0x2ff). The y values are flipped (height minus row minus one) before packing, so they use the same stored-y convention as the drawing registers: row counted from the top of the screen (see the Y origin section of the REX1 page).

### Register `xendi`

Draw end x (integer, inclusive): the last column a STOPONX command draws. The ide test reads it back through XENDF (0x18) as (value & 0xfff) << 11.

### Register `yendi`

Draw end y (integer, inclusive), top-down row like YSTARTI. The glyph commands also use the order of YSTARTI and YENDI to pick the direction rows advance: toward YENDI. The ide test reads it back through YENDF (0x28) as (value & 0xfff) << 11. light_sboxfi and the PROM fill store 767 minus the top row here and 767 minus the bottom row in YSTARTI, so YSTARTI <= YENDI.

### Register `smask2x`

First of six consecutive screen-mask words, in the order SMASK2X, SMASK2Y, SMASK3X, SMASK3Y, SMASK4X, SMASK4Y. The six-word run is established by the context save and the name-to-word assignment by the ide test's offsets. Packing as smask1x. Offset established by the ide test. The six names map to the six consecutive words in this order.

### Register `smask2y`

Screen mask word 2Y. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six.

### Register `smask3x`

Screen mask word 3X. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six.

### Register `smask3y`

Screen mask word 3Y. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six.

### Register `smask4x`

Screen mask word 4X. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six.

### Register `smask4y`

Screen mask word 4Y. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six.

### Register `aux2`

Second auxiliary control word. Both initialisations store 0x20000000. lightSetDestinationPlanes keeps bits 28:0 of the window's saved value, ORs in the request's top three bits and, for the window on screen, waits for the engine to go idle and stores the result here, so the top three bits select which plane group a draw reaches. The meaning of each of those three bits: unknown (no shipped code names the groups). The ide mask 0x7fffffff shows 31 bits kept.

### Register `diagvram`

VRAM diagnostic access. No shipped kernel or PROM runtime path touches it; the ide VRAM test is the only candidate user and was not read. Offset and role: unknown.

### Register `wclock`

Port to the pixel clock generator and the board configuration byte; the byte is picked by CFGSEL. Reading with CFGSEL 4 (after a dummy read of the GO alias and a one microsecond wait) returns: bits 2:0 board revision, bits 5:3 monitor type, bit 6 set when no video board is present. light_init stores them in bytes 0x28, 0x2b and 0x2c of the board info. Writing with CFGSEL 2 clocks the clock generator's program bytes in: initClock writes 17 bytes in a row to the SET and GO aliases, selected by board revision (below 2: the first of the two 17-byte clock tables in the driver, 2 and above: the second). A qtest can discriminate: CFGSEL 4 then a read of GO and SET returns the configured byte; a model needs a settable board revision to take the revision 1 path (the PROM and kernel need the revision below 2 branch for the Bt479 colour map).

### Register `rwdac`

Port to the colour map chip. CFGSEL picks the chip register (see CFGSEL constants). Software writes the same byte to RWDAC and to its GO alias; the second write is what performs the transfer. A read of its GO alias returns the chip register's value. light_read_bt_colormaps reads the GO alias directly for the palette, the Bt479-based path also reads RWDAC; whether the SET read after a GO read adds anything: unknown, NetBSD's VC1 read does read GO then SET.

### Register `configsel`

Three-bit function selector shared by WCLOCK, RWDAC and RWVC1: the value written here is the chip register index the next access to any of the three ports addresses. Values 0 to 6 are used (CFGSEL constants); 7 is not written by shipped code. Readback returns the written value (lightPositionCursor saves and later restores it by reading it back). A qtest can discriminate: write 5, read back 5; write 8, read back 0 (the 0x7 mask, from the ide test).

### Register `rwvc1`

Port to the video controller (VC1), same SET/GO scheme as RWDAC with its GO alias 0x800 above it. NetBSD's read: write CFGSEL, read the GO alias, read the SET alias; the PROM does the same, with the kernel's read-modify-write sequences storing the value to both aliases. The VC1's internal register file behind CFGSEL is in devices/vc1.

### Register `togglectxt`

Written with 0 in the middle of a window context swap, after the registers for the outgoing window have been saved and before the incoming ones are loaded. Role inferred: switches REX to the other of two register contexts (its ide-visible name is not printed). Whether a read is defined: unknown.

### Register `configmode`

Configuration and status. Bit 0 is the engine busy flag: all software spins until it is clear before touching a drawing register (the kernel and the PROM do it in every drawing routine). Bits 28:24 (mask 0x1f000000) must also be zero before a VC1 access in lightPositionCursor and the retrace handler: inferred to be a count of commands still queued in the FIFO, which the busy bit alone does not cover. Bits 7:4 are read by lightInitInfo (value 0 triggers the pixel-memory probe described under rwaux1, any other value plus one is stored as a board option byte). initRex and the pixel DMA path store 0x807fe000. lightPcxSwap saves the word xor 0x80000000 and restores it unchanged, so bit 31 is read inverted of what was written. Bit 31 and bits 22:13 role: unknown. A qtest can discriminate: bit 0 reads 1 while a command is executing and 0 after; the PROM's 300000 microsecond polling loop in lightProbe (done when bit 0 clears) must not time out.

### Register `xywin`

Window origin offset: x in bits 27:16 and y in bits 11:0, 0x800 each at init (the window offset of 2048 that centres a 12-bit coordinate space; the centring is inferred). NetBSD's match accepts a board whose XYWIN reads 0x08000800. The ide test keeps 12 bits per half.

## Constants

| Constant | Value | Grade | Source | Description |
|---|---|---|---|---|
| `BASE_HEAD0` | 0x1f3f0000 | established |  | Physical address of the first LG1 board, the first entry of the probe address table in the kernel driver and in the PROM. |
| `BASE_HEAD1` | 0x1f3f8000 | established |  | Physical address of the second board of a dual-head system, the second entry of the same probe tables. |
| `CFGSEL_DAC_ADDR` | 0x0 | established |  | CFGSEL value that selects the colour map's address register through RWDAC and the VC1's indirect register window through RWVC1. See the register page. |
| `CFGSEL_HADDR` | 0x5 | established |  | CFGSEL 5: VC1 address high byte. |
| `CFGSEL_LADDR` | 0x4 | established |  | CFGSEL 4: VC1 address low byte; read of WCLOCK returns the board configuration byte. |
| `CFGSEL_PALETTE` | 0x1 | established |  | CFGSEL 1: the colour map's palette data port; the VC1's display-mode (XMAP) window. |
| `CFGSEL_PIXMASK` | 0x2 | established |  | CFGSEL 2: colour map pixel read mask (0xff written at init); VC1 external SRAM window; WCLOCK serial clock program port. |
| `CFGSEL_RDADDR` | 0x3 | established |  | CFGSEL 3: colour map read-address register; VC1 test register (VC1 revision read). |
| `CFGSEL_SYSCTL` | 0x6 | established |  | CFGSEL 6: VC1 SYS_CTL register; colour map command register. |
| `CMD_BLOCK` | 0x8 | established |  | Command flag: fill or copy a rectangle rather than a line or point. Present in every rectangle and glyph command the PROM and kernel issue. |
| `CMD_COPY_RECT` | 0x30080329 | established |  | Screen copy: fill-rectangle with LOGICSRC. The PROM's scroll routine loads the four coordinates, writes XYMOVE (offset 0x34) at its GO alias, and uses this command word; NetBSD issues the same command. |
| `CMD_DRAW` | 0x1 | established |  | Command opcode bit: draw. Value 0 is a no-op that only latches the coordinates (NetBSD and the PROM glyph code both write it through the GO alias before a glyph). |
| `CMD_ENZPATTERN` | 0x400 | established |  | Command flag: pixels are drawn where the ZPATTERN bit is one, taken from bit 31 downward. Used for every font glyph. |
| `CMD_FILL_RECT` | 0x30000329 | established |  | Solid rectangle: logic op 3, STOPONX, STOPONY, QUAD, BLOCK, DRAW. light_sboxfi writes it at the GO alias after loading XSTARTI, YSTARTI, XENDI and YENDI; the PROM does the same. |
| `CMD_GLYPH16` | 0x300005b9 | established |  | Glyph up to 16 pixels wide: ENZPATTERN, STOPONX, XYCONTINUE, QUAD, LENGTH32, BLOCK, DRAW. light_drawbitmap issues it, then writes the ZPATTERN GO alias (0x860) once per row with the row's bits in the high 16. |
| `CMD_GLYPH_PIECE` | 0x300005a1 | established |  | Glyph wider than 16: every 16-pixel piece except the last uses this command (no BLOCK, no LENGTH32), with XSTART advanced by the 0x10 per piece through XENDI loads. The last piece of each row uses 0x300005a9 (adds BLOCK, which is where y advances). |
| `CMD_HOSTDATA` | 0x200000 | inferred |  | Command flag set only in the three pixel-memory probe commands (never in a fill, copy, point or glyph command). Inferred to make the draw take its pixel word from RWAUX1 (the probe writes RWAUX1 at its GO alias to run it) instead of from the colour register, and the read form to return pixels through RWAUX1; inferred from that use and from the compare constants alone. |
| `CMD_LENGTH32` | 0x10 | inferred |  | Command flag named LENGTH32 by NetBSD. Set with the 16-pixel glyph command 0x300005b9, clear with the other two glyph commands. Meaning (32-pixel run, or a pattern width) inferred from the pairing only. |
| `CMD_LOGICOP_SHIFT` | 0x1c | established |  | Bits 31:28 hold the logic operation. 3 is source-replace: every command the PROM, kernel and NetBSD draw with has it (0x30000000). No other value is issued by the objects read, so the table of operations is unknown. |
| `CMD_LOGICSRC` | 0x80000 | inferred |  | Command flag: source is the frame buffer at the XYMOVE offset (a screen copy). Used with value 0x30080329 in the PROM's scroll and NetBSD's copy. Role inferred from use. |
| `CMD_OP_READ` | 0x2 | inferred |  | Opcode bit 1: set only in 0x30200023, the command whose execution (a read of RWAUX1's GO alias) returns pixel data in that read. Inferred to make opcode 3 a pixel read where opcode 1 (CMD_DRAW) is a write; opcode 2 is never issued. |
| `CMD_PIXMEM_BIT16` | 0x10000 | unknown |  | Command bit set only in 0x30210021, the second probe write, together with AUX1 = 0x100. The probe's compare shows that with it exactly one pixel pair of the four written is replaced; which pair, and what the bit selects, is unknown. |
| `CMD_PIXMEM_READ` | 0x30200023 | established |  | Probe read: logic op 3, bit 21, QUAD, opcode bits 1 and 0. Run by reading the RWAUX1 GO alias (the PROM reads it twice and compares the second value; the kernel compares a fresh read each time). The result 0x01080909 gives outcome 0, 0x09091020 gives outcome 1, anything else 0xff. The word is established; its effect is inferred. |
| `CMD_PIXMEM_WRITE_A` | 0x30200021 | established |  | Probe write 1: logic op 3, bit 21, QUAD, DRAW. Run by writing 0x01081020 at the RWAUX1 GO alias with XSTARTI 0, YSTARTI 0, XENDI 3, YENDI 0, RWMASK 0xff and AUX1 0. The word is established; its effect is inferred. |
| `CMD_PIXMEM_WRITE_B` | 0x30210021 | established |  | Probe write 2: as probe write 1 plus bit 16. Run by writing 0x09090909 at the RWAUX1 GO alias with AUX1 set to 0x100 just before. The word is established; its effect is inferred (one pixel pair replaced). |
| `CMD_POINT` | 0x30000001 | established |  | Single point: logic op 3, DRAW. light_pnt2i (kernel) and the PROM both store it at SET (0x0) and then read the GO alias (0x800), which runs it, after XSTARTI and YSTARTI. |
| `CMD_QUAD` | 0x20 | inferred |  | Command flag named QUADMODE by NetBSD. Set in every rectangle command. Role inferred from use only. |
| `CMD_STOPONX` | 0x100 | established |  | Command flag: the draw's x run ends at XENDI (inclusive; NetBSD notes the end is inclusive). |
| `CMD_STOPONY` | 0x200 | established |  | Command flag: the draw's y run ends at YENDI. Set for rectangle fill and copy, clear for the glyph rows (the glyph's y advances once per pattern write). |
| `CMD_XYCONTINUE` | 0x80 | established |  | Command flag: start the draw from the current XSTART/YSTART position the previous command left, not from XSTARTI/YSTARTI. Set in the glyph commands (0x300005a1, 0x300005a9, 0x300005b9) that the kernel and PROM follow with one pattern write per row. |
| `CMD_ZCONTINUE` | 0x1000000 | unknown |  | Defined by NetBSD, never set by the shipped software read. |
| `CMD_ZOPAQUE` | 0x800000 | inferred |  | Command flag named ZOPAQUE by NetBSD: with a pattern, pattern zeros paint COLORBACK instead of leaving the pixel alone. The kernel's and the PROM's glyph commands omit it (transparent background); NetBSD sets it. Inferred from NetBSD's use against the shipped commands. |
| `GO_OFFSET` | 0x800 | established |  | Distance from a register's SET address to its GO alias. light_sboxfi, light_pnt2i and the PROM's rectangle fill write the coordinate and colour registers at their plain offsets and then the command word at 0x800; lightProbe and the PROM probe write the command at 0 and read 0x800. |
| `PROBE_READBACK` | 0x33c0000 | established |  | What the XSTART register reads after 0x12345678 is written to XSTARTI. lightProbe and the PROM probe accept the board when they read it. It is 0x678 shifted left 15: XSTARTI keeps its low 12 bits and XSTART shows them from bit 15 up. |
| `VC1_SYSCTL_CURSOR` | 0x10 | inferred |  | VC1 SYS_CTL bit named in NetBSD for the cursor generator; kernel initialisation leaves the whole byte 0xfc. |
| `VC1_SYSCTL_CURSOR_ON` | 0x20 | inferred |  | VC1 SYS_CTL bit named in NetBSD for cursor display; see above. |
| `VC1_SYSCTL_VIDEO_ON` | 0x4 | established |  | VC1 SYS_CTL bit: video output enabled. The PROM's unblank clears it for an argument of 1 (blank) and sets it otherwise ; NetBSD's names agree. |
| `XRES` | 0x400 | established |  | Horizontal resolution the kernel reports (the board info structure holds 1024 by 768) and the PROM stores. |
| `YRES` | 0x300 | established |  | Vertical resolution. Drawing code addresses y as 767 minus the screen row (light_sboxfi, light_pnt2i, the PROM), and its own y counts up from the bottom, so the stored value is the row counted from the top of the screen: display row = stored y (inferred; see the Y origin section of the REX1 page). |
