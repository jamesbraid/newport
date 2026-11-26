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

**`XSAVE` and `XYMOVE`.** Neither is written by any line routine. `XSAVE` was not found stored in the line, triangle-row, span, point or clear routines at all; `XYMOVE` is written only by the library's rectangle-copy routine (0x0dab7bd0 to 0x0dab7c60, inside the range of the export `__glSetDrawBuffer`): the word 0x30280329 (`LOGICSRC`, `COLORAUX` and the block fill) with `XYMOVE` = (x delta << 16) | (y delta & 0xffff), the layout the X server uses ([registers.md](registers.md)). The context-switch code of the kernel saves both because it saves every register, not because lines need them. **Established** for the absence in the routines read, which are the line, triangle, span, point, clear and copy routines named on these pages; the rest of the library was not searched.

## Colour along the line

The colour routine runs last, from the jump at the end of `__glRexLine_asm` (its address is in the context: one routine per line type). **[binary]**

- **Flat RGB** (`__glRexFlatRGBLine_asm`, 0x0db5c450): the colour of the second vertex plus 6144.0 (plus the rounding offsets of [shaded drawing](shaded-drawing.md) when dither is off) into `COLORRED`, `COLORGREEN` and `COLORBLUE`; `COMMAND` stored at its SET address; the store of `COLORBLUE` at its **GO alias** (0x84c) runs the line. Flat colour index: `COLORRED`, then `COMMAND`, then a GO store of `COLORRED` (0x83c). A line that uses the colour already in the registers: a store of the command at its GO alias (0x800).
- **Smooth RGB** (`__glRexSmoothRGBLine_asm`, 0x0db5c348): the start colour of the first vertex (plus 6144.0 and the offsets) into the three colour registers, and for each channel the slope `(c1 - c0) / count` with the sign carried in the constant (`+6144.0` or `-6144.0`, by the sign of the difference) into `SLOPERED`, `SLOPEGREEN`, `SLOPEBLUE`; the order is `COLORRED`, `SLOPERED`, `COLORGREEN`, `SLOPEGREEN`, `COLORBLUE`, the command at SET, then a GO store of `SLOPEBLUE` (0x858), which runs it. Smooth colour index: `COLORRED`, the command at SET, and a GO store of `SLOPERED` (0x850). So the **last register written is the trigger**: the draw runs on the GO-alias store of the last colour or slope register, with the command word already latched at SET. The colour of pixel k is the start colour plus k times the slope: the same rule as a span ([shaded drawing](shaded-drawing.md#3-the-colour-dda)), with the step taken per major-axis pixel.
- The start colour is the vertex's own colour, not the colour at the centre of the first pixel; the library does not correct for the sub-pixel start, so a smooth line's first pixel carries exactly the first vertex's colour.

## Stippled lines

For a stipple, `__glRexPickLineProcs` loads `LSPATTERN` (0x64) with the 16-bit GL stipple, bit-reversed through a table and written into both halves of the word, and `LSMODE` (0x68) with `0xf0000 | (repeat - 1) << 8 | (repeat - 1)`, the repeat factor clamped to 1..256; the command gets `ENLSPATTERN` and `LSADVLAST`. The pattern length field (bits 19:16) is 0xf, which agrees with the X server's `LSMODE` = (width - 17) << 16 for a 32-bit width ([getimage and stipple](getimage-and-stipple.md)): the 16-bit pattern is presented as a 32-bit one, repeated. Within a connected run each later segment adds `LSCONTINUE` once the first has drawn, so the pattern carries across the joint. **Established** for the stores; the library passes each byte of the user's stipple through a lookup table first, and which bit is drawn first (and whether the table reverses bits) was not decoded: **unknown**.

## What a model must do

1. Treat a command with `DRAW`, `STOPONX` or `STOPONY` and no `BLOCK` or `QUADMODE` as a line: step one pixel along the major axis per iteration from the start toward the end register, inclusive of both.
2. Keep `XSTART`/`YSTART` as 12.15 and load their fraction from `XSTARTF`/`YSTARTF` (the ide shift of four); accumulate `MINORSLOPE` as a 17-bit two's-complement 15-fraction-bit number; the pixel is the integer part. Do not round.
3. Run the draw when the command is latched and a **GO-alias** store hits `COMMAND`, `COLORRED`, `COLORBLUE`, `SLOPERED` or `SLOPEBLUE` (any register at its GO alias runs the latched command; the library chooses the last one it writes).
4. Colour: the same slope and 11-fraction-bit rule as a span, with one step per major pixel.
5. Stipple bits and `LSCONTINUE` are stored; the pattern order and its phase across segments are an **approximation** with no evidence beyond the library's own use.
6. `XSAVE` and `XYMOVE` have no effect on lines.

A test for the accumulator, which is a prediction of the inferred model and not a measurement: `XSTARTI` 10, `XENDI` 13, `YSTARTF` 0x45802e00 (4096.0 + 5.75), `MINORSLOPE` 0x43804000 (256.0 + 0.5), command 0x30000141 at SET with colour index 7, then a GO store of `COMMAND`. The accumulator runs 5.75, 6.25, 6.75, 7.25, so the pixels are (10, 5), (11, 6), (12, 6) and (13, 7).

## Open

Filed in [questions/README.md](../../questions/README.md): the effect of `INITFRAC`, the chip's behaviour when the slope or the accumulator overflows, and the wide-line routine.
