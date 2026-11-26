# REX1 true lines: what the IRIX 6.2 GL sends

The sloped-line commands of the Indigo Entry board as the OpenGL library drives them: the command words, which registers carry the end points, the slope and the colour, and how the minor coordinate is accumulated. Nothing in the Entry-run trace draws a line (the shaded torus is triangles only), so everything here is read from the library, not from a run. The register list is in [registers.md](registers.md); colour, dither and the slope sign rule are on [shaded drawing](shaded-drawing.md); buffers, masks and clip on [GL context state](gl-context-state.md).

Grades, tags and the objects read are those of the shaded-drawing page (`libGLcore.so` of `usr/gfx/arch/IP20LG1MC` in IRIX 6.2, MIPS disassembly read by hand; ide sources for the register behaviour): **established** for what the routines store, **inferred** for what the chip does with it. The routines: `__glRexPickLineProcs` (0x0dab0538) builds the command word, `__glRexLine_asm` (0x0db5bac4) computes and stores the end points and slope of one line, `__glRexInitLineData` (0x0db5b510) does the same set-up for a connected run of lines, and the colour routines below finish and start the draw. `__glRexWideLine_asm` (0x0db5be90) was not read in full.

## The command words

`__glRexPickLineProcs` builds the base word once per state change (stored in the context, read by the line routine). **[binary]** It is the logic operation in bits 31:28 (the GL logic-op state when enabled, 3 otherwise) with the opcode `DRAW` (1), plus:

| Bit | Value | Added when |
|---|---|---|
| 14 | 0x4000 | the window is RGB (`RGBMODECMD`) |
| 17 | 0x20000 | the line is smooth-shaded (`SHADE`) |
| 15 | 0x8000 | `GL_DITHER` is enabled (`DITHER`) |
| 11, 12 | 0x800, 0x1000 | the line is stippled (`ENLSPATTERN`, `LSADVLAST`) |
| 13 | 0x2000 | stippled and the stipple is continuing from the previous segment (`LSCONTINUE`), set by the colour routines |

The line routine then adds the major-axis bits. For an x-major line it ORs 0x140, that is `XMAJOR` (bit 6) and `STOPONX` (bit 8); for a y-major line it ORs 0x200, `STOPONY` (bit 9), with `XMAJOR` clear. There is no `BLOCK`, `QUADMODE` or `XYCONTINUE`. So the words are, for example, 0x30004141 (flat RGB, x-major), 0x3000c141 (the same dithered), 0x30024141 and 0x3002c141 (smooth), 0x30004201 (flat RGB, y-major), 0x30000141 and 0x30000201 for colour index, and with a stipple 0x30005941 (flat RGB, x-major) and the like. Bit 18 (`INITFRAC`) is never set by the GL; the ide `_line` sets it and writes no fraction ([source] `minigl.c`), which is the evidence that `INITFRAC` is "start the minor coordinate at a default fraction (the pixel centre) instead of the one in `XSTARTF`/`YSTARTF`" (**inferred**; names and use only).

## Which line is x-major, where it starts and ends

For the line (x0, y0) to (x1, y1) in window coordinates (floats whose low 11 mantissa bits are the fraction; the library reads fraction and integer straight out of the bit pattern): **[binary]**

- **Major axis.** x-major when |dy| < |dx|; a tie goes to y-major.
- **First pixel and end boundary.** The first pixel is the integer part of the start coordinate along the major axis, plus one (in the direction of travel) when the offset of the start point ahead of its pixel centre, plus the absolute offset across the line, exceeds 1/2 (the code compares 11-bit fractions against 1024); points behind the centre never trigger it. The end point goes through the same test, giving the boundary just past the last lit pixel, so a pixel is lit when the line leaves its diamond: the GL diamond-exit rule (**inferred** from the arithmetic; it is the library's rule, not necessarily the chip's). The **count** of pixels is the difference of the two. When it is zero the routine returns before storing a slope, a colour or the command: no pixel is drawn.
- **Stores, x-major, left to right** (the other three directions swap the signs): `XSTARTI` (0x0c) the first pixel; `XENDI` (0x84) the end boundary minus one, the last lit pixel (an inclusive end, matching `STOPONX`); `YSTARTF` (0x20) the line's y at the **centre of the first pixel**, as `y0 + slope * (first_x + 0.5 - x0)` in the same float form (so its mantissa is a 12-bit integer and 11 fraction bits); `MINORSLOPE` (0x30). `YSTARTI` is not written. A y-major line is the mirror: `YSTARTI` (0x1c), `YENDI` (0x88), `XSTARTF` (0x10), `MINORSLOPE`, with the slope dx/dy.
- **`MINORSLOPE` value.** The slope plus or minus 256.0: `256.0 + m` for a positive slope and `-256.0 + m` (a negative float of magnitude 256 + |m|) for a negative one; the constant sits in the context at 0x43800000. With the library's constants a slope below 1 has bits 14:0 of the float as the fraction (15 bits) and bit 31 as the sign, which is the format the 17-bit register accepts ([slope sign rule](shaded-drawing.md#4-slope-sign-bit-31-or-bit-19)). **Established** for the stores.

## How the steps accumulate

**Inferred**, from the register widths the ide test establishes and the way the library uses them: the engine takes one step along the major axis per pixel, in the direction from `XSTARTI` toward `XENDI` (or `YSTARTI` toward `YENDI`), and draws the pixel at (major coordinate, integer part of the minor accumulator). The minor accumulator is the 27-bit `YSTART` (or `XSTART`): 12 integer bits and 15 fraction bits, initialised from the float written to `YSTARTF` (the ide read-back shows `YSTART` = the 23-bit mantissa shifted left four), and each step adds the sign-extended `MINORSLOPE` (15 fraction bits). The library has already moved the sample to the pixel centre, so **no rounding is done on the way out: the pixel row is the integer part of the accumulator**, not its nearest integer. The slope's sign decides whether the minor coordinate counts up or down; the coordinates are the stored ones (display row = stored y, [Y origin](README.md#y-origin)), which the library's vertex coordinates already are.

**`XSAVE` and `XYMOVE`.** Neither is written by any line routine. `XSAVE` was not found stored in the line, triangle-row, span, point or clear routines at all; `XYMOVE` is written only by the library's rectangle-copy routine (0x0dab7ac4 to 0x0dab7c60, inside the range of the export `__glSetDrawBuffer`): the word 0x30280329 (`LOGICSRC`, `COLORAUX` and the block fill) with `XYMOVE` = (x delta << 16) | (y delta & 0xffff), the layout the X server uses ([registers.md](registers.md)). The context-switch code of the kernel saves both because it saves every register, not because lines need them. **Established** for the absence in the routines read, which are the line, triangle, span, point, clear and copy routines named on these pages; the rest of the library was not searched.

## Colour along the line

The colour routine runs last, from the jump at the end of `__glRexLine_asm` (its address is in the context: one routine per line type). **[binary]**

- **Two variants of each colour routine.** The plain routines add only 6144.0 to the colour: they serve the dither-on case. The `D` routines (`__glRexFlatRGBLineD_asm` 0x0db5c72c, `__glRexSmoothRGBLineD_asm` 0x0db5c66c and the colour-index and stippled siblings) also add the rounding offsets of [shaded drawing](shaded-drawing.md) (15.0 to red and green, or 0.5 for an index): they serve dither off (for colour index only in a single-buffered window; in a double-buffered RGB window the offsets are 0.0). `__glRexPickLineProcs` chooses between them from the context's dither enable.
- **Flat RGB** (`__glRexFlatRGBLine_asm`, 0x0db5c450): the colour of the second vertex plus 6144.0 into `COLORRED` and `COLORGREEN`; `COMMAND` stored at its SET address; then `COLORBLUE` stored at its **GO alias** (0x84c), which runs the line. Flat colour index (`__glRexFlatCILine_asm`): `COMMAND` at SET, then the index plus 6144.0 stored once, at the GO alias of `COLORRED` (0x83c). A line that uses the colour already in the registers: a store of the command at its GO alias (0x800).
- **Smooth RGB** (`__glRexSmoothRGBLine_asm`, 0x0db5c348): the start colour of the first vertex (plus 6144.0, and the offsets in the `D` routine) into the three colour registers, and for each channel the slope `(c1 - c0) / count` with the sign carried in the constant (`+6144.0` or `-6144.0`, by the sign of the difference) into `SLOPERED`, `SLOPEGREEN`, `SLOPEBLUE`; the order is `COLORRED`, `SLOPERED`, `COLORGREEN`, `SLOPEGREEN`, `COLORBLUE`, the command at SET, then a GO store of `SLOPEBLUE` (0x858), which runs it. Smooth colour index: `COLORRED`, the command at SET, and a GO store of `SLOPERED` (0x850). So the **last register written is the trigger**: the draw runs on the GO-alias store of the last colour or slope register, with the command word already latched at SET. The colour of pixel k is the start colour plus k times the slope: the same rule as a span ([shaded drawing](shaded-drawing.md#3-the-colour-dda)), with the step taken per major-axis pixel.
- The start colour is the vertex's own colour, not the colour at the centre of the first pixel; the library does not correct for the sub-pixel start, so a smooth line's first pixel carries exactly the first vertex's colour.

## Stippled lines

For a stipple, `__glRexPickLineProcs` loads `LSPATTERN` (0x64) with the 16-bit GL stipple, bit-reversed through a table and written into both halves of the word, and `LSMODE` (0x68) with `0xf0000 | n << 8 | n`, where n is the low 8 bits of the GL repeat factor (clamped to 1..256 by `glLineStipple`, so 256 is stored as 0; there is no subtraction of one); the command gets `ENLSPATTERN` and `LSADVLAST`. The pattern length field (bits 19:16) is 0xf, which agrees with the X server's `LSMODE` = (width - 17) << 16 for a 32-bit width ([getimage and stipple](getimage-and-stipple.md)): the 16-bit pattern is presented as a 32-bit one, repeated. What the length and repeat fields mean is under [LSMODE](#lsmode-length-and-repeat). Within a connected run each later segment adds `LSCONTINUE` once the first has drawn, so the pattern carries across the joint. **Established** for the stores; the lookup table is the 256-entry byte bit-reversal (its first entries read 0x00, 0x80, 0x40, 0xc0), so GL stipple bit 0 lands in bit 15 and bit 31 of `LSPATTERN`.

**Which bit a line draws first: bit 31 (MSB first), inferred.** Three software facts agree and none contradicts. (1) OpenGL draws stipple bit 0 first (the Khronos `glLineStipple` reference page: "Bit zero is used first"), and the GL reverses the bits through a table before storing them, which puts the first bit at the top of each half. (2) The X server's dashed-line code (`rexLineSD`, 6.2 `lg1mc.so` 0x5e51ff40) rotates its pattern word left by the distance already covered (mod the pattern width) before it stores `LSPATTERN`; a left rotation by k moves the bit that is k places below the top to the top, so the top bit is the one drawn at the start of the piece. (3) The `ZPATTERN` word of the glyph and triangle-row paths also starts at bit 31 ([REX1 page](README.md)). No manual states it, so it stays inferred.

**Phase across a joint (inferred).** The X server loads a pattern with a store to `LSPATTERN` followed by a `COMMAND` GO store of 0 (a no-op command: 0x5e5200d4 and 0x5e5200dc), once at the start and again before every later piece of a dashed line, each time with the pattern rotated for the distance skipped (clipped parts are skipped by software). Every draw it then issues carries `ENLSPATTERN`, `LSADVLAST` and `LSCONTINUE` (0x3a01 for the vertical runs, 0x3941 for the horizontal ones, ORed with the operation in 31:28 and `LSOPAQUE` for opaque dashes: 0x5e520314 and 0x5e5205fc). The reading that fits both clients: the chip keeps a working stipple position apart from `LSPATTERN`; the no-op GO store after a `LSPATTERN` write loads that position from `LSPATTERN` and `LSMODE` (bit 31 next); a draw without `LSCONTINUE` loads it from `LSPATTERN` at its start; a draw with `LSCONTINUE` carries on from where the previous draw left it. The GL's first segment of a run has no `LSCONTINUE` and starts at bit 31, and each later segment has it, so the pattern runs on across the joint with no repeat: the diamond-exit rule above gives every segment an exclusive end, so the joint pixel belongs to one segment only. The position moves by one bit for each pixel the draw writes, in the direction the draw runs from the start register to the end register (the X server rotates for either direction by the distance from the piece's own start; that part was read, not traced in full). What `LSADVLAST` does is unknown: both clients always set it with `ENLSPATTERN`, the ide tests never use a stipple, and the name suggests the position steps past the last pixel.

## LSMODE: length and repeat

Read 2026-11-26. Every writer in the shipped software is here; all are **established** as stores, and what the fields do is **inferred** from the values written and
from what each client does around them. No software reads `LSMODE` back except the kernel's window context switch (`lightPcxSwap`, save and restore) and the ide register test
(write, read back, 20 bits kept).

| Writer | Value | Source |
|---|---|---|
| X server, dashed lines (`rexLineSD`, 0x5e51ff40, store at 0x5e5200c8) | `((len - 17) << 16) \| 0x0101`, len 17 to 32 | 6.2 `lg1mc.so` |
| X server, stippled fills (`rexStippledFS`, 0x5e4ae6f4; `rexStippledFillRects`, 0x5e49ed40) | `(w - 17) << 16`, repeat bytes 0 | 6.2 `lg1mc.so` |
| OpenGL, stippled line set-up (`__glRexPickLineProcs` +0x2a4; reloaded by `__glRexWideLine_asm` for each copy of a wide line) | `0xf0000 \| n << 8 \| n`, n = factor & 0xff | 6.2 `libGLcore.so` |
| IRIS GL `lsrepeat` (`gl_i_lsrepeat`, `gl_c_lsrepeat`, `_popattributes`, and reloads in `_C_line_alpha`, `_C_line_zb`, `_C_line_sm`, `_C_line_sm_zb`, `__xwide`) | `0xf0000 \| n << 8 \| n`, n clamped to 1 to 255 | 6.2 `libgl.so` |
| ide REX register test | test patterns, mask 0xfffff | `stand/arcs/ide/fforward/graphics/LIGHT/rex.c`, **[source]** |
| 4.0.5G PROM | none: no store at 0x68 or 0x868 from a non-stack base in the whole image | 070-8116-005 |

IRIS GL `setlinestyle` writes only `LSPATTERN` (the style's 32-bit word); `LSMODE` is written by `lsrepeat` and the reloads. `deflinestyle` builds the word by reversing the 16-bit
mask and storing it in both halves.

**Length: field + 17, from 17 to 32 bits [inferred, from every writer agreeing].** The X server stores `len - 17` for the whole range 17 to 32, and it builds
every pattern it sends so that the length is in that range: the dash builder at 0x5e4a053c adds up the dash lengths, hands the line to software when the total is above 32, and
otherwise doubles the pattern (12 becomes 24, 5 becomes 20, 16 becomes 32) until it is at least 17 bits, shifts it to the top of the word, and rotates it left by the dash offset. Both GL libraries
send a 16-bit stipple as two copies in one 32-bit word with field 15. Nothing writes a length of 16 or below, and a length of "field + 1" would make field 15 sixteen bits long, which
contradicts the X server's 32-bit dashes. The sibling Newport ide command uses the same rule (`(n - 17)` for n 17 to 32, placed in a higher field there), which is a hint, not evidence for this chip.
The pattern is top-aligned: bit 31 is the first pixel and only the top `length` bits are used. The X server's rotation `(word << k) | (word >> (length - k))` leaves stray bits
below position `length`, so the chip must ignore them (inferred from that, not seen).

**Repeat: each pattern bit is held for n pixels [inferred].** The IRIS GL call is named `lsrepeat` and the OpenGL factor has that meaning in its own specification; both write n in 7:0 and 15:8,
n = 1 being the default (one pixel per bit, which is also what the X server's dashes need: it rotates its pattern by the distance in pixels and stores 0x0101). Which of the two bytes
is the working counter and which the reload value is **unknown**: every software that sets them writes both alike (the X server's fills write both as 0).

**Advance rule for a model (inferred).** With L = field + 17 and r = max(repeat byte, 1), the pixel drawn k pixels after the start of the stipple (counting each pixel the
draw writes, in draw order) uses bit `31 - ((k div r) mod L)` of `LSPATTERN`. A draw with `LSCONTINUE` carries k on from the previous draw; a draw without it, and the no-op `COMMAND` GO store after a
`LSPATTERN` write, restart at k = 0. With the GL's field 15 and a doubled 16-bit pattern this is the 16-pixel stipple with each bit held n pixels.

**Conflict on a repeat of 0.** The X server's stippled fills store 0 in both bytes and need one pixel per bit; the OpenGL library stores 256 as 0 and means 256. Both cannot be true of one
counter. The two paths differ in the command word (the fills use 0x921, with no `LSADVLAST`; every line has it), but nothing shows that the repeat count depends on that bit. A model should
treat 0 as 1 (the fills are on every desktop and the GL case is a factor of 256) and count how often a draw with `LSADVLAST` arrives with a repeat of 0. What would settle it: a
published description of the REX1 stipple unit, or a recorded GL run at factor 256.

**Unverified side finding.** `rexValidateWindowGC` takes the stipple fast path for any stipple pixmap up to 32 pixels wide, with no lower limit, while the pixmap padding routine (`mfbPadPixmap`)
widens only widths that divide 32 (1, 2, 4, 8, 16). For a width such as 5 or 12 the server stores `(w - 17) << 16`, a negative value whose bits 19:16 are w - 1; with length = field + 17 the chip would
then take w + 16 pixels. Not traced further; no software reads the result, and real hardware behaviour here is unknown.

## What a model must do

1. Treat a command with `DRAW`, `STOPONX` or `STOPONY` and no `BLOCK` or `QUADMODE` as a line: step one pixel along the major axis per iteration from the start toward the end register, inclusive of both.
2. Keep `XSTART`/`YSTART` as 12.15 and load their fraction from `XSTARTF`/`YSTARTF` (the ide shift of four); accumulate `MINORSLOPE` as a 17-bit two's-complement 15-fraction-bit number; the pixel is the integer part. Do not round.
3. Run the draw when the command is latched and a **GO-alias** store hits `COMMAND`, `COLORRED`, `COLORBLUE`, `SLOPERED` or `SLOPEBLUE` (any register at its GO alias runs the latched command; the library chooses the last one it writes).
4. Colour: the same slope and 11-fraction-bit rule as a span, with one step per major pixel.
5. Stipple: keep a working position (bit 31 first, one bit per pixel written, in draw order) apart from `LSPATTERN`; a draw without `LSCONTINUE` starts it at bit 31, a draw with it carries on, and a no-op GO store after a `LSPATTERN` write reloads it (all **inferred**). `LSADVLAST` has no known effect. The length (`LSMODE` 19:16 plus 17, so 17 to 32) and the repeat count (7:0) apply as under [LSMODE](#lsmode-length-and-repeat); a model that supports only the length 32 and repeat 1 covers the GL's default and every X server dash pattern of 32 bits.
6. `XSAVE` and `XYMOVE` have no effect on lines.

A test for the accumulator, which is a prediction of the inferred model and not a measurement: `XSTARTI` 10, `XENDI` 13, `YSTARTF` 0x45802e00 (4096.0 + 5.75), `MINORSLOPE` 0x43804000 (256.0 + 0.5), command 0x30000141 at SET with colour index 7, then a GO store of `COMMAND`. The accumulator runs 5.75, 6.25, 6.75, 7.25, so the pixels are (10, 5), (11, 6), (12, 6) and (13, 7).

## Open

Filed in [questions/README.md](../../questions/README.md): the effect of `INITFRAC`, the chip's behaviour when the slope or the accumulator overflows, and the wide-line routine.
