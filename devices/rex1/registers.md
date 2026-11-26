<!-- generated from devices/rex1/registers.toml by defs-gen - do not edit, change the source -->
<!-- defs-gen 3 -->
<!-- input sha256 215500cb7a789af02feb2e9126ba34c2493fb9517b9ac2556b00db0e14f03150 -->

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

Auxiliary control word, one per window context. initRex zeroes it. lightAux1Register builds a value from a window's saved value with bits 4:2 cleared, sets bit 4 when the request word's second field is 1, bit 2 when bit 0 of its third field is set and bit 3 when bit 1 is set, then stores it here (only for the window that owns the screen) or in the window's saved context. The shipped header names the bits FRACTION0 and FRACTION1 (0, 1), DBLDST0 and DBLDST1 (2, 3), DBLSRC (4), DOUBLEBUF (5), COLORCOMPLT, COLORCOMPEQ and COLORCOMPGT (6, 7, 8) and DITHERRANGE (9); the roles are inferred from the names: bits 2 and 3 pick which buffer a draw writes, bit 4 which one it reads, bit 5 turns double buffering on. The X server's four-pixel tile fill and PutImage store 0x28 or 0x2c (DOUBLEBUF with DBLDST1, and DBLDST0 for 0x2c) and its GetImage 0x30 (DOUBLEBUF with DBLSRC). The pixel-memory probe stores 0x100 (COLORCOMPGT) here before its second write. Software expects only bits 9:0 (a software expectation; ten bits is inferred as the hardware width): both the ide register test and the 4.0.5G PROM power-on test write a 32-bit pattern and require the read-back to equal the pattern masked to 0x3ff (0x155 for 0x55555555, 0x2aa for 0xaaaaaaaa), so a store keeps ten bits and a read returns them. A model run that returned the whole word made the PROM print 'Graphics diagnostic FAILED' on the Entry; that comes from a trace of our own model, not from a board. A qtest can write 0x55555555 at 0x004 and read 0x155. The IRIS GL library's context set-up stores 2 (FRACTION1 alone). GL contexts use 0x202 (single-buffered, FRACTION1 and DITHERRANGE) or 0x222 plus buffer bits: GL_FRONT is DBLDST0 (0x226), GL_BACK DBLDST1 and DBLSRC (0x23a), both 0x22e, the pair exchanged after each swap. devices/rex1/gl-context-state.md.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 9 | `ditherrange` | unknown |  |  |  |
| 8 | `colorcompgt` | inferred |  |  |  |
| 7 | `colorcompeq` | inferred |  |  |  |
| 6 | `colorcomplt` | inferred |  |  |  |
| 5 | `doublebuf` | inferred |  |  |  |
| 4 | `dblsrc` | inferred |  |  |  |
| 3 | `dbldst1` | inferred |  |  |  |
| 2 | `dbldst0` | inferred |  |  |  |
| 1:0 | `fraction` | unknown |  |  |  |

### Register `xstate`

Packed draw state word. The kernel stores 0x03ff0000 here before each full-screen clear (rexClear, the command word 0x329 with no logic-operation nibble), and the X server (X server driver functions rexInitHW, rexDrawSolidRects, rexDrawPoints, rexDrawImage, rexCopyRect, rexImageGlyphBltTE8) stores it before nearly every draw. The X server builds it as colour index in bits 7:0, plane write mask in bits 23:16 and the X raster-operation code in bits 27:24 (GXcopy is 3, so the clear value 0x03ff0000 is: replace, all eight planes, colour 0; the copy path ORs 0x20 into the top byte). Those field roles are inferred from what the writers pack, not from a manual. The operation is a value from 0 to 15 shifted left by 24, so it occupies bits 27:24; bit 29 is a separate flag that only the copy words set (0x20000000 in rexCopyRect, 0x23ff0000 in rexValidateWindowPriv), role unknown. Open and settled only as a model constraint: the X server fills with command 0x329 and the colour from here, while the kernel's per-rectangle fill (light_sboxfi) uses 0x30000329 and the colour from COLORREDI (the kernel's rexClear does write XSTATE); rexImageGlyphBltTE8 fills its background with 0x30000329 after writing only XSTATE and loads COLORREDI afterwards, which is the discriminating case for the shared reading. The one reading that satisfies every shipped writer is that XSTATE bits 7:0 and COLORREDI are the same eight bits of state. The shipped header names bits 31:28 XSTATE_ZOPAQUE, XSTATE_LSOPAQUE, XSTATE_LOGICSRC and XSTATE_COLORAUX, the same names as command bits 23, 22, 19 and 21, so the upper nibble is the X server's way of keeping those command flags as state (inferred); the tile fill sets bit 28 and the copy words set bit 29. The ide test writes all 32 bits and expects them back unmasked.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31 | `zopaque` | unknown |  |  |  |
| 30 | `lsopaque` | unknown |  |  |  |
| 29 | `copyflag` | inferred |  |  |  |
| 28 | `coloraux` | inferred |  |  |  |
| 27:24 | `logicop` | inferred |  |  |  |
| 23:16 | `planemask` | inferred |  |  |  |
| 7:0 | `colour` | inferred |  |  |  |

### Register `xstarti`

Draw start x as an integer. Twelve bits are kept (the ide test mask is 0xfff) and appear in XSTART at bit 15 and above: lightProbe writes 0x12345678 here and expects 0x033c0000 from XSTART. A qtest can discriminate: write 0x12345678, read XSTART at 0x14, expect 0x033c0000; whether XSTARTI itself reads back is unknown: no shipped code and not the ide test (which reads XSTART) reads offset 0xc. The ide test confirms the derivation: write at 0xc, read at 0x14, expect (value & 0xfff) << 15.

### Register `xstartf`

Draw start x, fraction. Test mask 0x7fffff. Offset read from the ide test. Software that draws only rectangles never writes it. Offset established by the ide test. A write here appears in XSTART bits 26:4 (the ide test reads 0x14, not 0x10). 'F' is the ide name; the readback shows the register feeds XSTART bits 26:4 (inferred as a write alias of XSTART).

### Register `xstart`

Draw start x, integer and fraction combined: 27 bits in the ide test mask, integer in bits 26:15. Read at offset 0x14 by the board probe after XSTARTI was written; the value read is the probe presence test (PROBE_READBACK). lightPcxSwap reads it back and later stores the saved value at 0x14 itself, so a store here must be kept whole (the same holds for YSTART at 0x24, COLORRED/GREEN/BLUE at 0x3c/0x44/0x4c and the slope registers at 0x50 to 0x58): a model that derives XSTART only from XSTARTI loses a context restore. Whether a write here also reflects in XSTARTI: unknown.

### Register `xendf`

Draw end x, fraction (ide mask 0x7ff800).  Offset established by the ide test. Holds the end x with the integer in bits 22:11 (a write to XENDI at 0x84 reads back here as value & 0xfff shifted left 11; written directly, only bits 22:11 stick). Not a fraction field as the name suggests.

### Register `ystarti`

Draw start y as an integer, 12 bits kept; the ide test writes it and reads YSTART (0x24) expecting (value & 0xfff) << 15. Software stores 767 minus its own y, which counts up from the bottom, so the stored value is the display row counted from the top of the 768-line screen (inferred: the PROM console prints its first text row at the largest console y, and NetBSD stores unflipped row numbers). See the Y origin section of the REX1 page.

### Register `ystartf`

Draw start y, fraction.  Offset established by the ide test. Mirror of XSTARTF for y; a write appears in YSTART bits 26:4. For lines the IRIX 6.2 GL writes the float 4096.0 + y at the centre of the first pixel, so the mantissa is the 12.11 start; the ide read-back shows YSTART = mantissa << 4 (12.15). devices/rex1/true-lines.md.

### Register `ystart`

Draw start y, integer and fraction combined, counterpart of XSTART. Offset inferred; no shipped code reads it. Offset established by the ide test. Combined y start, integer in bits 26:15 (the same derivation the probe uses for XSTART).

### Register `yendf`

Draw end y, fraction.  Offset established by the ide test. Holds the end y with the integer in bits 22:11, as XENDF.

### Register `xsave`

Saved x start (the x that a block-draw returns to at the start of each row, inferred from its name and the context save). lightPcxSwap saves it with the other window registers. Offset established by the ide test. Twelve bits kept. No routine of the IRIX 6.2 GL that draws lines, triangle rows, spans, points, clears or copies stores it. devices/rex1/true-lines.md.

### Register `minorslope`

Line-draw minor-axis slope. Never written by the shipped light code for rectangles, text or points. Only the name (ide) and the slot between XSAVE and XYMOVE support it. Offset established by the ide test. Written and read back unmasked. Sign rule, from the ide REX test: 17 bits are kept, bit 31 is the sign, bit 16 of a negative magnitude is ignored and the result is the 17-bit two's complement. The GL writes 256.0 + m or -256.0 + m (0x43800000 plus the fraction), which gives 15 fraction bits; each step along the major axis adds it to the minor coordinate. devices/rex1/true-lines.md.

### Register `xymove`

Copy source offset: x delta in the high 16 bits and y delta in the low 16, each source minus destination, in stored coordinates (display row = stored y). The X server (X server driver function rexCopyRect) computes dx as source x minus destination x0 and dy as source y minus destination y0, masks dy to 16 bits and stores (dx << 16) | dy at the GO alias (0x834) after the rectangle and the copy command 0x80329 are set up; it chooses XSTARTI..XENDI ascending when dx is not negative and descending when it is, and YSTARTI..YENDI ascending when dy is not negative and descending when it is, so the engine must honour either order of the two registers. That fixes the sign for the X server and agrees with NetBSD. The only remaining doubt is the PROM copy routine, whose callers were not found. For a destination x0 below 4 and dx negative the X server also stores XYWIN 0x07fc0800 around the copy (see XYWIN). The ide mask 0x7ff07ff shows eleven bits kept per half. A qtest can discriminate: write 0x00100005 at 0x34 and 0x80329 or 0x30080329 at 0, then a copy from (x+16, y+5) happens when 0x800 is touched, and a rectangle with YSTARTI greater than YENDI copies bottom row first. The IRIX 6.2 GL's rectangle copy stores the same layout with the word 0x30280329.

### Register `colorredi`

Foreground pixel colour (the ide test reads a write back through COLORRED at 0x3c as (value & 0xff) << 11), an 8-bit index into the colour map (the board has 8 bits per pixel). The kernel's colour routine stores the index at this offset after the busy bit clears; the PROM's colour routine does too. The ide test calls the register COLORREDI with an 8-bit mask; RED because the chip's colour path starts with red.

### Register `colorred`

Red channel with fraction for shaded draws, 20 bits in the ide mask. Offset by name order. Offset established by the ide test. COLORRED holds the red channel with its integer part (COLORREDI, 8 bits) in bits 18:11. Shaded draws: the IRIX 6.2 GL stores the float c + 6144.0, so the word is 0x45c00000 + c * 2048 (bits above 19 are ignored by the chip, 9 integer and 11 fraction bits are kept) and a negative c wraps modulo 512. Whether the chip clamps or wraps out-of-range colours is unknown. devices/rex1/shaded-drawing.md.

### Register `colorgreeni`

Green channel integer (shaded draws). Never written by shipped light code. Offset from the ide name order and NetBSD. Offset established by the ide test. A write here appears in COLORGREEN bits 18:11.

### Register `colorgreen`

Green channel with fraction. Offset established by the ide test. 20 bits kept. Same format as COLORRED.

### Register `colorbluei`

Blue channel integer. Offset established by the ide test. A write here appears in COLORBLUE bits 18:11.

### Register `colorblue`

Blue channel with fraction. Offset established by the ide test. 20 bits kept. Same format as COLORRED. A store at the GO alias (0x84c) runs the latched command: the GL's flat RGB lines and clears end that way.

### Register `slopered`

Red slope for shaded lines and spans. Not written by shipped light code. Offset established by the ide test. Slope registers are signed: the ide test expects bit 19 of the stored value to read back also in bit 20. Sign rule, from the ide REX register test: bit 31 is the sign and bits 19:0 the magnitude; with bit 31 set the stored value is the 21-bit two's complement of the magnitude (bit 20 of the written value is cleared first), read back with bit 20 ORed with bit 19; bits 30:21 of a write are ignored. The GL writes m + 6144.0 for a positive slope and m - 6144.0 for a negative one. devices/rex1/shaded-drawing.md.

### Register `slopegreen`

Green slope. Not written by shipped light code. NetBSD names offset 0x54 of the configuration page WCLOCKREV, which is a different page. Offset established by the ide test. As SLOPERED. Same rule as SLOPERED.

### Register `slopeblue`

Blue slope. Not written by shipped light code. Offset established by the ide test. As SLOPERED. Same rule as SLOPERED. A store at the GO alias (0x858) runs the latched command: the GL's smooth RGB lines end that way.

### Register `colorback`

Background colour index used for pattern zeros when ZOPAQUE is set. The shipped kernel and PROM glyph paths never write it (transparent background); NetBSD does. Offset established by the ide test. Eight bits kept.

### Register `zpattern`

Pixel pattern for the pattern-enabled commands. Software writes it at the GO alias (0x860): each write draws one row of the glyph, taking pattern bits 31 downward, the row's bits shifted into the top half for 16-wide glyphs (the kernel shifts each halfword left by 16) and into bit 24 for 8-wide (NetBSD). With STOPONX, XYCONTINUE and BLOCK, y steps by one row after each write. A qtest can discriminate: set XSTARTI, XENDI, YSTARTI, write command 0x300005b9 at 0 and 0x80000000 at 0x860, and exactly one pixel at the start column is drawn.

### Register `lspattern`

Line stipple pattern. Not written by shipped light code. Offset established by the ide test. Fully read/write. The IRIX 6.2 GL stores the 16-bit GL stipple bit-reversed into both halves; the X server stores a pattern word rotated left by the distance already covered, then a no-op GO store of COMMAND. The first pixel drawn takes bit 31 (inferred from the GL reversal of OpenGL bit-0-first, the X server rotation and the ZPATTERN order). devices/rex1/true-lines.md.

### Register `lsmode`

Line stipple mode. Not written by shipped light code. NetBSD's configuration-page name CFGMODE for offset 0x68 is a different page. Offset established by the ide test. 20 bits kept. The IRIX 6.2 GL line stipple writes 0xf0000 | n << 8 | n: length field 15 in 19:16 (a 32-bit pattern, as the X server's (width - 17) << 16) and n in 15:8 and 7:0, where n is the GL repeat factor 1 to 256 masked to 8 bits (256 is stored as 0; no subtraction of one).

### Register `aweight`

Antialias weight. Not written by shipped light code. Offset established by the ide test. Fully read/write. The IRIX 6.2 GL writes 0xdb987642 once at context set-up (the IRIS GL library holds the same constant) and nothing in it reads or rewrites the register; the GL antialiases lines in software. No dither role is evidenced, and no shipped software varies it or issues the antialias opcodes with it (the IRIS GL library writes the same constant at set-up). Its eight nibbles fall steadily (13, 11, 9, 8, 7, 6, 4, 2). devices/rex1/shaded-drawing.md.

### Register `rwaux1`

Read/write auxiliary word used to read and write pixel memory with a draw command. lightInitInfo writes 0x01081020 here, then 0x09090909 with a 0x30210021 command, runs 0x30200023 and compares the result word read back at 0x870 with 0x01080909 or 0x09091020 to record a 0, 1 or 0xff in byte 0x29 of the board info it hands to GfxRegisterBoard. Data flow (inferred from the constants): the first write puts the four bytes 01 08 10 20 into pixels 0 to 3 of stored row 0, the second replaces exactly one pair of them with 09 (outcome 0 = pixels 2 and 3 replaced, outcome 1 = pixels 0 and 1 replaced, if the high byte is pixel 0), and the read returns the four pixels. All three commands are executed through RWAUX1's GO alias, so RWAUX1 is the data port of the probe. What each outcome means for the board (pixel memory arrangement): unknown; no object read uses info byte 0x29 afterwards. The PROM runs the probe unconditionally; the kernel runs it only when CONFIGMODE bits 7:4 read 0. A qtest can discriminate only by replaying that sequence, which needs the draw unit to move words between RWAUX1 and the frame buffer; any model that yields 0x01080909 or 0x09091020 satisfies every shipped reader, and a choice between them is an approximation.

### Register `rwaux2`

Second read/write auxiliary word. Not written by shipped light code. Offset established by the ide test. Fully read/write.

### Register `rwmask`

Plane write mask for read/write pixel access. lightInitInfo and the PROM write 0xff (all eight planes) before the pixel-memory probe. The ide mask 0xffff shows sixteen bits kept, and the ide graphics shell's write-mask command stores its argument here, so the low byte is the pixel write mask (the shipped header's comment calls the register readmask and writemask, in that order, without saying which half is which). The kernel's board-info routine writes it only when CONFIGMODE bits 7:4 read 0; the PROM writes it unconditionally. The X server never writes RWMASK: it keeps the write mask in XSTATE bits 23:16, but it is not the 0xff the board-info routine left: lightPcxSwap saves RWMASK into, and restores it from, the rendering node's image, a node made by lightCreateDDRN has a zero image, and the first load of a never-saved node writes 0 (platforms/lg1/colormap-install.md). The shipped desktop draws with RWMASK 0 and would be blank if hardware gated RWAUX1 host-data writes or reads (tile fill, PutImage, GetImage) with it, so it is inferred not to. The X server's lines, dashes and glyphs also draw with a non-zero logic-operation nibble and RWMASK 0, taking the plane mask from XSTATE 23:16, so the nibble does not decide either. The IRIX 6.2 GL stores 0xff at context set-up, then after every draw-buffer change the window's full mask (0xf for the 4-bit window, 3 for the overlay, 0xff for the 8-bit one) or 0 when the GL draw buffer is none, and no other value, and never stores XSTATE. The hardware rule for how RWMASK and XSTATE 23:16 combine is unknown; every shipped writer is satisfied by their OR. devices/rex1/gl-context-state.md.

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

Second auxiliary control word. Both initialisations store 0x20000000. lightSetDestinationPlanes keeps bits 28:0 of the window's saved value, ORs in the request's top three bits and, for the window on screen, waits for the engine to go idle and stores the result here, so the top three bits select which plane group a draw reaches. The shipped header names them as one three-bit code, not as three flags: NOPLANES 0, PIXELPLANES 1, OVERLAYPLANES 2 and CIDPLANES 3 (shifted left 29). The X server's plane-group writes agree: 0x20000000 for the displayed pixel planes, 0x40000000 for the overlay clear and 0x60000000 for the window-id fill, whose value is limited to 0 to 3 (rexDrawCID) like the ide CID memory test. The ide mask 0x7fffffff shows 31 bits kept. The X server's line, point and span batches (rexLineSS, rexSegmentSS, rexPolyPoint, rexSolidFillSpans) store (group << 29) | 0xf11 at the start and plain group << 29 at the end, so the low twelve bits are used and the value 0xf11 is not a command word. The header names bits 3:0 SMASK0 to SMASK3 (screen mask enables), bits 7:4 their inside/outside polarity and bits 23:8 four CID match nibbles, so 0xf11 reads as screen mask 0 enabled, inside polarity and CID match nibble 1 set to 0xf (inferred from the names; no shipped code states the effect). The X server's clip table for rendering-node windows (rexValidateClip, 6.2 data 0x5e573830) enables one more screen mask per visible rectangle, up to three (table in devices/rex1/gl-context-state.md; inside polarity everywhere, one 0xf CID nibble per enabled mask); the kernel's lightValidateClip builds 0xf1 | (1 << cid) << 8 for CID-clipped windows; for four to ten visible rectangles rexValidateClip sends the table entry for the obscured-rectangle count ANDed with 0x00ffff1f, clearing polarity bits 7:5, so the enabled masks 1 to 3 have the clear polarity (read as outside, a software expectation from that use and the header names). GL and kernel window contexts use 0xff1 in the low twelve bits (the X server's batches 0xf11): by the header's names screen mask enable bit 0 (the first pair, SMASK1X and SMASK1Y) with inside polarity bit 4, polarity bits 7:5 set on disabled masks, CID match nibble 1 = 0xf. devices/rex1/gl-context-state.md.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31:29 | `planegroup` | inferred |  |  |  |
| 23:20 | `cidmatch4` | inferred |  |  |  |
| 19:16 | `cidmatch3` | inferred |  |  |  |
| 15:12 | `cidmatch2` | inferred |  |  |  |
| 11:8 | `cidmatch1` | inferred |  |  |  |
| 7:4 | `smask_inside` | inferred |  |  |  |
| 3:0 | `smask_enable` | inferred |  |  |  |

### Register `diagvram`

VRAM diagnostic access. No shipped kernel or PROM runtime path touches it; the ide VRAM test is the only candidate user and was not read. Offset and role: unknown.

### Register `wclock`

Port to the pixel clock generator and the board configuration byte; the byte is picked by CFGSEL. Reading with CFGSEL 4 (after a dummy read of the GO alias and a one microsecond wait) returns: bits 2:0 board revision, bits 5:3 monitor type, bit 6 set when no video board is present. light_init stores them in bytes 0x28, 0x2b and 0x2c of the board info. Writing with CFGSEL 2 clocks the clock generator's program bytes in: initClock writes 17 bytes in a row to the SET and GO aliases, selected by board revision (below 2: the first of the two 17-byte clock tables in the driver, 2 and above: the second). A qtest can discriminate: CFGSEL 4 then a read of GO and SET returns the configured byte; a model needs a settable board revision to take the revision 1 path (the PROM and kernel need the revision below 2 branch for the Bt479 colour map).

### Register `rwdac`

Port to the colour map chip. CFGSEL picks the chip register (see CFGSEL constants). Software writes the same byte to RWDAC and to its GO alias; the second write is what performs the transfer. A read of its GO alias returns the chip register value. light_read_bt_colormaps and light_read_lut_colormaps issue one GO read, discard it, and then read the GO alias 768 times per bank (bulk reads: the same one-deep pipeline as RWVC1 fits). The X server reads the command register back (CONFIGSEL 6: GO read, then RWDAC read) for read-modify-write of the blank bit (X server driver function rexBlankScreen) and in rexDisplayCursor, so the DAC command register must be readable. Whether the SET read after a GO read adds anything beyond the pipeline: unknown.

### Register `configsel`

Three-bit function selector shared by WCLOCK, RWDAC and RWVC1: the value written here is the chip register index the next access to any of the three ports addresses. Values 0 to 6 are used (CFGSEL constants); 7 is not written by shipped code. Readback returns the written value (lightPositionCursor saves and later restores it by reading it back). A qtest can discriminate: write 5, read back 5; write 8, read back 0 (the 0x7 mask, from the ide test).

### Register `rwvc1`

Port to the video controller (VC1), same SET/GO scheme as RWDAC with its GO alias 0x800 above it. A write stores the byte at SET and again at GO; a GO store alone also works (lightSetDisplayMode stores only the GO alias). Reads: every reader does GO read then SET read for a single byte, and the bulk readers (light_read_displaymodes, light_read_scan) issue one GO read whose value they discard and then read only the GO alias, once per byte. Both fit a one-deep read pipeline: a GO read returns the byte fetched by the previous GO read and starts the fetch of the next, and a SET read returns the byte the last GO read fetched; a model where a GO read returns and consumes the current byte makes every bulk reader skip its first byte. The kernel retrace handler and lightPositionCursor read the VC1 address counter back through CONFIGSEL 4 (low) and 5 (high) while a user process may be in the middle of a data transfer; see devices/vc1. The VC1 internal register file behind CFGSEL is in devices/vc1.

### Register `togglectxt`

Written with 0 in the middle of a window context swap. lightPcxSwap reads ten registers (XSTART, YSTART, COLORRED, COLORGREEN, COLORBLUE, LSPATTERN, LSMODE, ZPATTERN, XSAVE, RWAUX1), stores 0 here, then reads about twenty-four more (XSTART, YSTART, the colour and slope registers, XENDF, YENDF, AUX1, the pattern registers, XSAVE, MINORSLOPE, XYMOVE, COLORBACK, AWEIGHT, RWAUX1, RWAUX2, RWMASK, COMMAND, SMASK1X, SMASK1Y); the load side mirrors it. Inferred from the repeated registers (XSTART, COLORRED and others appear in both passes): the engine holds two copies of part of the drawing state and a write here switches which one the register offsets address. A flat model that keeps one copy and ignores the write returns the same values in both passes and restores consistently. Whether a read is defined: unknown.

### Register `configmode`

Configuration and status. Bit 0 is the engine busy flag: all software spins until it is clear before touching a drawing register (the kernel and the PROM do it in every drawing routine). Bits 28:24 (mask 0x1f000000) must also be zero before a VC1 access in lightPositionCursor and the retrace handler: inferred to be a count of commands still queued in the FIFO, which the busy bit alone does not cover. The X server polls a second count, bits 12:8 (five bits): before a burst of register stores it waits until that field is at most 21 minus its gfifo level setting, 14 at the default level 7 (rexLineSS, rexPolyPoint, rexZeroPolyArc, rexImageGlyphBltTE8; fixed limits of 5 and 8 appear in rexSolidFillSpans), so the 5-bit field is inferred to be the graphics FIFO fill level, with the level setting the number of stores the X server allows per primitive. Bits 7:4 are read by lightInitInfo (value 0 triggers the pixel-memory probe described under rwaux1, any other value plus one is stored as a board option byte). initRex and the pixel DMA path store 0x807fe000. The X server (driver function rexInitHW) stores 0x80000000 | 0x40000000 | 0x00180000 | (level << 13) with level 7 by default (see the CPU-board ranges below, or the number in the environment variable REX_GFIFO_LEVEL), raises the level field to 31 for glyph and arc runs (0xc01be000) and writes 0x80000000 | 0x00180000 | (level << 13), without bit 30, only around the pixel DMA of a large PutImage (the CPU-store PutImage path leaves bit 30 set); so bits 17:13 are inferred to be a FIFO-level threshold (the interrupt on GIO line 0 or the stall point), bits 20:19 are constant 11 in every X server store, and bit 30 is set except while the pixel DMA feeds RWAUX1 (role unknown). The default level of 7 becomes 9 or 11 only when an inventory value in the CPU-board range is read at start (0x400 to 0x43f: 9, or 11 with the board-info flags bit 6 set; 0x440 to 0x1fff: 7, or 9 with bit 6 set). lightPcxSwap saves the word xor 0x80000000 and restores it unchanged, so bit 31 is read inverted of what was written. Role of bit 31 and of bits 22:21: unknown. A qtest can discriminate: bit 0 reads 1 while a command is executing and 0 after; the PROM 300000 microsecond polling loop in lightProbe (done when bit 0 clears) must not time out; a model with synchronous drawing may return 0 in bits 28:24 and 12:8 and satisfy every shipped reader.

### Register `xywin`

Window origin offset: x in bits 27:16 and y in bits 11:0, 0x800 each at init (the window offset of 2048 that centres a 12-bit coordinate space; the centring is inferred). NetBSD match accepts a board whose XYWIN reads 0x08000800. The X server stores 0x08000800 in rexInitHW and, for a right-to-left copy or a PutImage that starts below x = 4, temporarily stores 0x07fc0800 (x origin 4 lower) and loads XSTARTI and XENDI 4 higher, then restores 0x08000800 (X server driver functions rexCopyRect, rexDrawImage, rexValidateWindowPriv). Inferred from that pairing: drawing coordinate = loaded coordinate plus (x origin minus 0x800), so the pair puts the screen x of the run unchanged while keeping the engine coordinate at 4 or more; a model that applies the origin offset to the coordinates gets the right pixels, one that ignores XYWIN draws four pixels to the right. The ide test keeps 12 bits per half.

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
| `CMD_CLEAR_RGB_DITHER` | 0x3000c329 | established |  | The pixel-plane clear of the IRIX 6.2 GL: the block fill 0x329 with the RGBMODECMD and DITHER bits. The overlay clear is 0x30008329 (DITHER alone, an index colour); without GL_DITHER the words are 0x30004329 and 0x30000329. The plane group is AUX2 31:29, not these bits. |
| `CMD_COPY_RECT` | 0x30080329 | established |  | Screen copy: fill-rectangle with LOGICSRC. The PROM's scroll routine loads the four coordinates, writes XYMOVE (offset 0x34) at its GO alias, and uses this command word; NetBSD issues the same command. |
| `CMD_COPY_RECT_GL` | 0x30280329 | established |  | The rectangle copy of the IRIX 6.2 GL: LOGICSRC and bit 21 with the block fill 0x329 and XYMOVE = (x delta << 16) \| (y delta & 0xffff); the GO store of COMMAND runs it. The effect of bit 21 here is unknown. |
| `CMD_COPY_RECT_STATE` | 0x80329 | established |  | Screen copy with an empty logic-operation nibble (X server rexCopyRect, rexValidateWindowPriv): CMD_COPY_RECT without bits 31:28; XYMOVE at its GO alias executes it. |
| `CMD_DITHER` | 0x8000 | inferred |  | Command flag named DITHER in the shipped header. The GL adds it whenever GL_DITHER is enabled, for colour-index and RGB draws alike (clears 0x30008329 and 0x3000c329, spans, points, lines, triangle rows), and omits its own rounding offsets in that case. Position-dependent rounding of the colour to the pixel; the matrix and amplitude are unknown. devices/rex1/shaded-drawing.md. |
| `CMD_DRAW` | 0x1 | established |  | Command opcode bit: draw. Value 0 is a no-op that only latches the coordinates (NetBSD and the PROM glyph code both write it through the GO alias before a glyph). |
| `CMD_ENLSPATTERN` | 0x800 | inferred |  | Command flag named ENLSPATTERN in the shipped header: use LSPATTERN and LSMODE as the line stipple. Set by the stippled span words (0x921), the X server's stippled rectangles (0x9a9) and the GL stippled lines. |
| `CMD_ENZPATTERN` | 0x400 | established |  | Command flag: pixels are drawn where the ZPATTERN bit is one, taken from bit 31 downward. Used for every font glyph. |
| `CMD_FILL_RECT` | 0x30000329 | established |  | Solid rectangle: logic op 3, STOPONX, STOPONY, QUAD, BLOCK, DRAW. light_sboxfi writes it at the GO alias after loading XSTARTI, YSTARTI, XENDI and YENDI; the PROM does the same. |
| `CMD_FILL_RECT_STATE` | 0x329 | established |  | Rectangle fill with an empty logic-operation nibble: the X server (rexDrawSolidRects, rexDrawCID, rexInitHW, rexClearOverlays) and the kernel clear (rexClear) store this at SET and take the operation, mask and colour from XSTATE; the executing store is the YENDI GO alias. The word is established; taking the operation from XSTATE is inferred. |
| `CMD_GLYPH16` | 0x300005b9 | established |  | Glyph up to 16 pixels wide: ENZPATTERN, STOPONX, XYCONTINUE, QUAD, LENGTH32, BLOCK, DRAW. light_drawbitmap issues it, then writes the ZPATTERN GO alias (0x860) once per row with the row's bits in the high 16. |
| `CMD_GLYPH_PIECE` | 0x300005a1 | established |  | Glyph wider than 16: every 16-pixel piece except the last uses this command (no BLOCK, no LENGTH32), with XSTART advanced by the 0x10 per piece through XENDI loads. The last piece of each row uses 0x300005a9 (adds BLOCK, which is where y advances). |
| `CMD_GL_TRIANGLE_ROW_SHADED_MASKED` | 0x3212c5b1 | established |  | The word the IRIX 6.2 GL builds (__glRexPickTriangleProcs) for a smooth-shaded RGB triangle row with a depth mask: logic op 3, LRQPOLY, SHADECONTINUE, SHADE, DITHER, RGBMODECMD, ENZPATTERN, XYCONTINUE, LENGTH32, QUADMODE, STOPONX, DRAW. Run by the ZPATTERN GO store of each 32-pixel piece. The word is established; the effect of the shaded and LRQPOLY bits is inferred and unknown respectively. |
| `CMD_HOSTDATA` | 0x200000 | inferred |  | Command flag; the shipped header names bit 21 COLORAUX. Set in the three pixel-memory probe commands, in PutImage (0x2000a9), GetImage (0x2000ab) and the four-pixel tile fill (0x200121); never in a fill, copy, point or glyph command. Inferred, from the name and from every use, to take the pixel word from RWAUX1 (written at its GO alias to run the draw) instead of from the colour registers, and in the read form to return pixels through RWAUX1. The X server also sets the matching XSTATE bit 28 (coloraux) in the tile fill. |
| `CMD_HOSTDATA_READ` | 0x2000ab | established |  | Host pixel read block (X server GetImage, rexReadImage): CMD_HOSTDATA_WRITE plus opcode bit 1, AUX1 0x30; the X server reads RWAUX1 GO once per four pixels. Effect inferred. |
| `CMD_HOSTDATA_WRITE` | 0x2000a9 | established |  | Host pixel write block (X server PutImage, rexDrawImage; rexRevADrawImage issues 0x2000a1, without BLOCK): HOSTDATA, XYCONTINUE, QUAD, BLOCK, DRAW with the X raster operation in bits 31:28. The X server then stores one 32-bit word per four pixels, first pixel in the high byte, at the RWAUX1 GO alias (0x870); the run ends at XENDI without a STOPONX flag. AUX1 is 0x28 or 0 around it. Effect inferred. |
| `CMD_INITFRAC` | 0x40000 | unknown |  | Command flag named INITFRAC in the shipped header. Set by the ide _line (which writes no fraction register) and by every command word the IRIS GL library builds (0x30040001, 0x30040129, 0x300405a1, 0x30040801, 0x30240089, 0x32040121, which write integer start registers only); never by the OpenGL library, which writes XSTARTF or YSTARTF and float colours instead. Read as start the minor coordinate and colour fractions at a default instead of the stored ones. Effect unknown. devices/rex1/true-lines.md. |
| `CMD_LENGTH32` | 0x10 | inferred |  | Command flag named LENGTH32 by NetBSD. Set with the 16-pixel glyph command 0x300005b9, clear with the other two glyph commands. Meaning (32-pixel run, or a pattern width) inferred from the pairing only. |
| `CMD_LOGICOP_SHIFT` | 0x1c | established |  | Bits 31:28 hold the logic operation. 3 is source-replace: every command the PROM, kernel and NetBSD draw with has it (0x30000000). No other value is issued by the objects read, so the table of operations is unknown. |
| `CMD_LOGICSRC` | 0x80000 | inferred |  | Command flag: source is the frame buffer at the XYMOVE offset (a screen copy). Used with value 0x30080329 in the PROM's scroll and NetBSD's copy. Role inferred from use. |
| `CMD_LRQPOLY` | 0x2000000 | unknown |  | Command flag named LRQPOLY in the shipped header. Set by every triangle row command of the IRIX 6.2 OpenGL library (flat and shaded, index and RGB, masked or not) and, in the IRIS GL library, by the plain polygon span word 0x32040121 only. Effect unknown and no shipped software depends on it: the ide _span draws the same span shape without it. A model draws the row as if it were clear. devices/rex1/shaded-drawing.md. |
| `CMD_LSADVLAST` | 0x1000 | inferred |  | Command flag named LSADVLAST in the shipped header. The GL ORs it with ENLSPATTERN into every stippled line. Effect unknown; both the GL and the X server always set it together with ENLSPATTERN. |
| `CMD_LSCONTINUE` | 0x2000 | inferred |  | Command flag named LSCONTINUE in the shipped header. The GL adds it to the later segments of a stippled line strip or loop so that the pattern carries across the joint; the X server sets it on every dashed draw and reloads the pattern with LSPATTERN and a no-op GO store before each piece. Read as: start from the working stipple position the previous draw left instead of loading it from LSPATTERN. devices/rex1/true-lines.md. |
| `CMD_OP_READ` | 0x2 | inferred |  | Opcode bit 1: set only in 0x30200023, the command whose execution (a read of RWAUX1's GO alias) returns pixel data in that read. Inferred to make opcode 3 a pixel read where opcode 1 (CMD_DRAW) is a write; opcode 2 is never issued. |
| `CMD_PIXMEM_BIT16` | 0x10000 | inferred |  | Command bit 16, named COLORCOMP in the shipped header (as are AUX1 bit 6 COLORCOMPLT, bit 7 COLORCOMPEQ and bit 8 COLORCOMPGT). Set only in 0x30210021, the second probe write, which the PROM library source issues with AUX1 = 0x100 (COLORCOMPGT). Read as a colour compare: the second write (0x09090909) goes over pixels 01 08 10 20 and replaces only those whose old value compares on the selected side, so one pixel pair of the four changes. Which side a given REX revision implements is the probe: outcome 0x09091020 (data replaces the smaller old values) is what the software calls REX revision B and 0x01080909 (data replaces the larger) revision A; which sense is the intended one is unknown. |
| `CMD_PIXMEM_READ` | 0x30200023 | established |  | Probe read: logic op 3, bit 21, QUAD, opcode bits 1 and 0. Run by reading the RWAUX1 GO alias (the PROM reads it twice and compares the second value; the kernel compares a fresh read each time). The result 0x01080909 gives outcome 0, 0x09091020 gives outcome 1, anything else 0xff. The word is established; its effect is inferred. |
| `CMD_PIXMEM_WRITE_A` | 0x30200021 | established |  | Probe write 1: logic op 3, bit 21, QUAD, DRAW. Run by writing 0x01081020 at the RWAUX1 GO alias with XSTARTI 0, YSTARTI 0, XENDI 3, YENDI 0, RWMASK 0xff and AUX1 0. The word is established; its effect is inferred. |
| `CMD_PIXMEM_WRITE_B` | 0x30210021 | established |  | Probe write 2: as probe write 1 plus bit 16. Run by writing 0x09090909 at the RWAUX1 GO alias with AUX1 set to 0x100 just before. The word is established; its effect is inferred (one pixel pair replaced). |
| `CMD_POINT` | 0x30000001 | established |  | Single point: logic op 3, DRAW. light_pnt2i (kernel) and the PROM both store it at SET (0x0) and then read the GO alias (0x800), which runs it, after XSTARTI and YSTARTI. |
| `CMD_QUAD` | 0x20 | inferred |  | Command flag named QUADMODE by NetBSD. Set in every rectangle command. Role inferred from use only. |
| `CMD_RGBMODE` | 0x4000 | inferred |  | Command flag named RGBMODECMD in the shipped header. Set by every IRIX 6.2 GL draw in an RGB window; the colour comes from the three colour registers instead of the index in COLORRED. The X server never sets it. devices/rex1/shaded-drawing.md. |
| `CMD_SHADE` | 0x20000 | inferred |  | Command flag named SHADE in the shipped header: the slope registers advance the colour from pixel to pixel (colour of pixel i = start + i * slope). Set by the GL's shaded spans, triangle rows and lines; the ide _span uses it (and _polygon through it); the ide _line does not. devices/rex1/shaded-drawing.md. |
| `CMD_SHADECONTINUE` | 0x100000 | inferred |  | Command flag named SHADECONTINUE in the shipped header. The GL sets it only together with SHADE on rows driven from ZPATTERN words (0x5b1), the rows that arrive as several 32-pixel pieces; read as: keep the colour running from one piece into the next. devices/rex1/shaded-drawing.md. |
| `CMD_SPAN` | 0x121 | established |  | Draw, QUAD, STOPONX with no BLOCK: one horizontal run from XSTARTI to XENDI. Used by the X server for solid spans, polygon and triangle fill (rexSolidSpans, rexSolidFillSpans, rexFillTriangle, rexFillPolygon). The line code (rexLineSS, rexSegmentSS, rexSolidZeroSeg) issues (op << 28) \| 0x121 for horizontal runs and (op << 28) \| 0x329 for vertical runs (built as 0x328 ORed into a word that holds the operation and DRAW; there is no draw-less command). Whether the run is one row and how the line variants use MINORSLOPE: unknown (not read in full). |
| `CMD_SPAN_LSPATTERN` | 0x921 | inferred |  | CMD_SPAN plus bit 11 (0x800), used by rexStippledFS and the stippled line code together with LSPATTERN and LSMODE. Bit 11 is inferred to enable the line stipple; no other source names it. |
| `CMD_STOPONX` | 0x100 | established |  | Command flag: the draw's x run ends at XENDI (inclusive; NetBSD notes the end is inclusive). |
| `CMD_STOPONY` | 0x200 | established |  | Command flag: the draw's y run ends at YENDI. Set for rectangle fill and copy, clear for the glyph rows (the glyph's y advances once per pattern write). |
| `CMD_TILE_HOSTDATA` | 0x200121 | established |  | CMD_SPAN plus HOSTDATA: tile fill, rexTileRects, with AUX1 set to 0x28 or 0x2c (by a board-info flag word being 1 or -1) and the tile words written through RWAUX1 GO. Effect inferred. |
| `CMD_XMAJOR` | 0x40 | inferred |  | Command flag named XMAJOR in the shipped header. The IRIX 6.2 GL ORs it with STOPONX (0x140) into every line whose x extent is the larger one, and ORs STOPONY alone (0x200) for the others. Read as: step along x and accumulate MINORSLOPE into y. devices/rex1/true-lines.md. |
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
