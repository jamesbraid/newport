/* generated from devices/rex1/registers.toml by defs-gen - do not edit, change
 * the source */
/* defs-gen 3 */
/* input sha256 2b518def1651291ae77838755f667396319226c08ae62a681b0af5a31a025992 */
/* REX1 raster engine on the Indigo Entry graphics board (LG1) */
#ifndef REX1_GEN_H
#define REX1_GEN_H

#include <stdint.h>


/*
 * Drawing command. Bits 31:28 hold the logic operation, the low bits the opcode
 * and flags listed as CMD_ constants. A write at 0x000 stores it; a write at
 * 0x800 (or a read of 0x800) executes the command that is now latched, using
 * the coordinate and colour registers as they stand. The PROM's probe writes 0
 * here and reads 0x800 (a no-op); the kernel's glyph path writes the command,
 * then writes ZPATTERN at its GO alias once per row. A qtest can discriminate:
 * a command written at 0x000 draws nothing, the same word at 0x800 draws, and a
 * read of 0x800 draws what the latched command says. Bits 27:20 of values the
 * kernel and PROM write are zero except bit 23 and bit 24 (ZOPAQUE, ZCONTINUE:
 * not set by shipped code) and bit 21 (all three) and bit 16 (second only) in
 * the pixel-memory probe commands 0x30200021, 0x30210021 and 0x30200023 that
 * lightInitInfo and the PROM board-info routine use (see the CMD_PIXMEM
 * constants and rwaux1). Bit 21 is inferred to be host data through RWAUX1, bit
 * 1 of the last to be a read opcode, and bit 16 is unknown. The direction a
 * pattern or block draw steps y is toward YENDI (inferred from the PROM glyphs,
 * which end at YENDI 0, and NetBSD glyphs, which end below YSTARTI), not a
 * fixed down.
 */
/* command: rw32, reset unknown */
#define REX1_COMMAND_OFFSET                          0x0u /* established */

/*
 * Auxiliary control word, one per window context. initRex zeroes it.
 * lightAux1Register builds a value from a window's saved value with bits 4:2
 * cleared, sets bit 4 when the request word's second field is 1, bit 2 when bit
 * 0 of its third field is set and bit 3 when bit 1 is set, then stores it here
 * (only for the window that owns the screen) or in the window's saved context.
 * The shipped header names the bits FRACTION0 and FRACTION1 (0, 1), DBLDST0 and
 * DBLDST1 (2, 3), DBLSRC (4), DOUBLEBUF (5), COLORCOMPLT, COLORCOMPEQ and
 * COLORCOMPGT (6, 7, 8) and DITHERRANGE (9); the roles are inferred from the
 * names: bits 2 and 3 pick which buffer a draw writes, bit 4 which one it
 * reads, bit 5 turns double buffering on. The X server's four-pixel tile fill
 * and PutImage store 0x28 or 0x2c (DOUBLEBUF with DBLDST1, and DBLDST0 for
 * 0x2c) and its GetImage 0x30 (DOUBLEBUF with DBLSRC). The pixel-memory probe
 * stores 0x100 (COLORCOMPGT) here before its second write. Only bits 9:0 exist:
 * both the ide register test and the 4.0.5G PROM power-on test write a 32-bit
 * pattern and require the read-back to equal the pattern masked to 0x3ff (0x155
 * for 0x55555555, 0x2aa for 0xaaaaaaaa), so a store must keep ten bits and a
 * read return them. A model that returns the whole word fails the PROM test
 * ('Graphics diagnostic FAILED' on the Entry). A qtest can write 0x55555555 at
 * 0x004 and read 0x155. GL contexts use 0x202 (single-buffered, FRACTION1 and
 * DITHERRANGE) or 0x222 plus buffer bits: GL_FRONT is DBLDST0 (0x226), GL_BACK
 * DBLDST1 and DBLSRC (0x23a), both 0x22e, the pair exchanged after each swap.
 * devices/rex1/gl-context-state.md.
 */
/* aux1: rw32, reset unknown */
#define REX1_AUX1_OFFSET                             0x4u /* established */
#define REX1_AUX1_DITHERRANGE_SHIFT                  9 /* unknown */
#define REX1_AUX1_DITHERRANGE_MASK                   0x1u
#define REX1_AUX1_DITHERRANGE_INPLACE (REX1_AUX1_DITHERRANGE_MASK << REX1_AUX1_DITHERRANGE_SHIFT)
#define REX1_AUX1_COLORCOMPGT_SHIFT                  8 /* inferred */
#define REX1_AUX1_COLORCOMPGT_MASK                   0x1u
#define REX1_AUX1_COLORCOMPGT_INPLACE (REX1_AUX1_COLORCOMPGT_MASK << REX1_AUX1_COLORCOMPGT_SHIFT)
#define REX1_AUX1_COLORCOMPEQ_SHIFT                  7 /* inferred */
#define REX1_AUX1_COLORCOMPEQ_MASK                   0x1u
#define REX1_AUX1_COLORCOMPEQ_INPLACE (REX1_AUX1_COLORCOMPEQ_MASK << REX1_AUX1_COLORCOMPEQ_SHIFT)
#define REX1_AUX1_COLORCOMPLT_SHIFT                  6 /* inferred */
#define REX1_AUX1_COLORCOMPLT_MASK                   0x1u
#define REX1_AUX1_COLORCOMPLT_INPLACE (REX1_AUX1_COLORCOMPLT_MASK << REX1_AUX1_COLORCOMPLT_SHIFT)
#define REX1_AUX1_DOUBLEBUF_SHIFT                    5 /* inferred */
#define REX1_AUX1_DOUBLEBUF_MASK                     0x1u
#define REX1_AUX1_DOUBLEBUF_INPLACE (REX1_AUX1_DOUBLEBUF_MASK << REX1_AUX1_DOUBLEBUF_SHIFT)
#define REX1_AUX1_DBLSRC_SHIFT                       4 /* inferred */
#define REX1_AUX1_DBLSRC_MASK                        0x1u
#define REX1_AUX1_DBLSRC_INPLACE (REX1_AUX1_DBLSRC_MASK << REX1_AUX1_DBLSRC_SHIFT)
#define REX1_AUX1_DBLDST1_SHIFT                      3 /* inferred */
#define REX1_AUX1_DBLDST1_MASK                       0x1u
#define REX1_AUX1_DBLDST1_INPLACE (REX1_AUX1_DBLDST1_MASK << REX1_AUX1_DBLDST1_SHIFT)
#define REX1_AUX1_DBLDST0_SHIFT                      2 /* inferred */
#define REX1_AUX1_DBLDST0_MASK                       0x1u
#define REX1_AUX1_DBLDST0_INPLACE (REX1_AUX1_DBLDST0_MASK << REX1_AUX1_DBLDST0_SHIFT)
#define REX1_AUX1_FRACTION_SHIFT                     0 /* unknown */
#define REX1_AUX1_FRACTION_MASK                      0x3u
#define REX1_AUX1_FRACTION_INPLACE (REX1_AUX1_FRACTION_MASK << REX1_AUX1_FRACTION_SHIFT)

/*
 * Packed draw state word. The kernel stores 0x03ff0000 here before each
 * full-screen clear (rexClear, the command word 0x329 with no logic-operation
 * nibble), and the X server (X server driver functions rexInitHW,
 * rexDrawSolidRects, rexDrawPoints, rexDrawImage, rexCopyRect,
 * rexImageGlyphBltTE8) stores it before nearly every draw. The X server builds
 * it as colour index in bits 7:0, plane write mask in bits 23:16 and the X
 * raster-operation code in bits 27:24 (GXcopy is 3, so the clear value
 * 0x03ff0000 is: replace, all eight planes, colour 0; the copy path ORs 0x20
 * into the top byte). Those field roles are inferred from what the writers
 * pack, not from a manual. The operation is a value from 0 to 15 shifted left
 * by 24, so it occupies bits 27:24; bit 29 is a separate flag that only the
 * copy words set (0x20000000 in rexCopyRect, 0x23ff0000 in
 * rexValidateWindowPriv), role unknown. Open and settled only as a model
 * constraint: the X server fills with command 0x329 and the colour from here,
 * while the kernel's per-rectangle fill (light_sboxfi) uses 0x30000329 and the
 * colour from COLORREDI (the kernel's rexClear does write XSTATE);
 * rexImageGlyphBltTE8 fills its background with 0x30000329 after writing only
 * XSTATE and loads COLORREDI afterwards, which is the discriminating case for
 * the shared reading. The one reading that satisfies every shipped writer is
 * that XSTATE bits 7:0 and COLORREDI are the same eight bits of state. The
 * shipped header names bits 31:28 XSTATE_ZOPAQUE, XSTATE_LSOPAQUE,
 * XSTATE_LOGICSRC and XSTATE_COLORAUX, the same names as command bits 23, 22,
 * 19 and 21, so the upper nibble is the X server's way of keeping those command
 * flags as state (inferred); the tile fill sets bit 28 and the copy words set
 * bit 29. The ide test writes all 32 bits and expects them back unmasked.
 */
/* xstate: rw32, reset unknown */
#define REX1_XSTATE_OFFSET                           0x8u /* established */
#define REX1_XSTATE_ZOPAQUE_SHIFT                    31 /* unknown */
#define REX1_XSTATE_ZOPAQUE_MASK                     0x1u
#define REX1_XSTATE_ZOPAQUE_INPLACE (REX1_XSTATE_ZOPAQUE_MASK << REX1_XSTATE_ZOPAQUE_SHIFT)
#define REX1_XSTATE_LSOPAQUE_SHIFT                   30 /* unknown */
#define REX1_XSTATE_LSOPAQUE_MASK                    0x1u
#define REX1_XSTATE_LSOPAQUE_INPLACE (REX1_XSTATE_LSOPAQUE_MASK << REX1_XSTATE_LSOPAQUE_SHIFT)
#define REX1_XSTATE_COPYFLAG_SHIFT                   29 /* inferred */
#define REX1_XSTATE_COPYFLAG_MASK                    0x1u
#define REX1_XSTATE_COPYFLAG_INPLACE (REX1_XSTATE_COPYFLAG_MASK << REX1_XSTATE_COPYFLAG_SHIFT)
#define REX1_XSTATE_COLORAUX_SHIFT                   28 /* inferred */
#define REX1_XSTATE_COLORAUX_MASK                    0x1u
#define REX1_XSTATE_COLORAUX_INPLACE (REX1_XSTATE_COLORAUX_MASK << REX1_XSTATE_COLORAUX_SHIFT)
#define REX1_XSTATE_LOGICOP_SHIFT                    24 /* inferred */
#define REX1_XSTATE_LOGICOP_MASK                     0xfu
#define REX1_XSTATE_LOGICOP_INPLACE (REX1_XSTATE_LOGICOP_MASK << REX1_XSTATE_LOGICOP_SHIFT)
#define REX1_XSTATE_PLANEMASK_SHIFT                  16 /* inferred */
#define REX1_XSTATE_PLANEMASK_MASK                   0xffu
#define REX1_XSTATE_PLANEMASK_INPLACE (REX1_XSTATE_PLANEMASK_MASK << REX1_XSTATE_PLANEMASK_SHIFT)
#define REX1_XSTATE_COLOUR_SHIFT                     0 /* inferred */
#define REX1_XSTATE_COLOUR_MASK                      0xffu
#define REX1_XSTATE_COLOUR_INPLACE (REX1_XSTATE_COLOUR_MASK << REX1_XSTATE_COLOUR_SHIFT)

/*
 * Draw start x as an integer. Twelve bits are kept (the ide test mask is 0xfff)
 * and appear in XSTART at bit 15 and above: lightProbe writes 0x12345678 here
 * and expects 0x033c0000 from XSTART. A qtest can discriminate: write
 * 0x12345678, read XSTART at 0x14, expect 0x033c0000; whether XSTARTI itself
 * reads back is unknown: no shipped code and not the ide test (which reads
 * XSTART) reads offset 0xc. The ide test confirms the derivation: write at 0xc,
 * read at 0x14, expect (value & 0xfff) << 15.
 */
/* xstarti: rw32, reset unknown */
#define REX1_XSTARTI_OFFSET                          0xcu /* established */

/*
 * Draw start x, fraction. Test mask 0x7fffff. Offset read from the ide test.
 * Software that draws only rectangles never writes it. Offset established by
 * the ide test. A write here appears in XSTART bits 26:4 (the ide test reads
 * 0x14, not 0x10). 'F' is the ide name; the readback shows the register feeds
 * XSTART bits 26:4 (inferred as a write alias of XSTART).
 */
/* xstartf: rw32, reset unknown */
#define REX1_XSTARTF_OFFSET                          0x10u /* established */

/*
 * Draw start x, integer and fraction combined: 27 bits in the ide test mask,
 * integer in bits 26:15. Read at offset 0x14 by the board probe after XSTARTI
 * was written; the value read is the probe presence test (PROBE_READBACK).
 * lightPcxSwap reads it back and later stores the saved value at 0x14 itself,
 * so a store here must be kept whole (the same holds for YSTART at 0x24,
 * COLORRED/GREEN/BLUE at 0x3c/0x44/0x4c and the slope registers at 0x50 to
 * 0x58): a model that derives XSTART only from XSTARTI loses a context restore.
 * Whether a write here also reflects in XSTARTI: unknown.
 */
/* xstart: rw32, reset unknown */
#define REX1_XSTART_OFFSET                           0x14u /* established */

/*
 * Draw end x, fraction (ide mask 0x7ff800).  Offset established by the ide
 * test. Holds the end x with the integer in bits 22:11 (a write to XENDI at
 * 0x84 reads back here as value & 0xfff shifted left 11; written directly, only
 * bits 22:11 stick). Not a fraction field as the name suggests.
 */
/* xendf: rw32, reset unknown */
#define REX1_XENDF_OFFSET                            0x18u /* established */

/*
 * Draw start y as an integer, 12 bits kept; the ide test writes it and reads
 * YSTART (0x24) expecting (value & 0xfff) << 15. Software stores 767 minus its
 * own y, which counts up from the bottom, so the stored value is the display
 * row counted from the top of the 768-line screen (inferred: the PROM console
 * prints its first text row at the largest console y, and NetBSD stores
 * unflipped row numbers). See the Y origin section of the REX1 page.
 */
/* ystarti: rw32, reset unknown */
#define REX1_YSTARTI_OFFSET                          0x1cu /* established */

/*
 * Draw start y, fraction.  Offset established by the ide test. Mirror of
 * XSTARTF for y; a write appears in YSTART bits 26:4. For lines the IRIX 6.2 GL
 * writes the float 4096.0 + y at the centre of the first pixel, so the mantissa
 * is the 12.11 start; the ide read-back shows YSTART = mantissa << 4 (12.15).
 * devices/rex1/true-lines.md.
 */
/* ystartf: rw32, reset unknown */
#define REX1_YSTARTF_OFFSET                          0x20u /* established */

/*
 * Draw start y, integer and fraction combined, counterpart of XSTART. Offset
 * inferred; no shipped code reads it. Offset established by the ide test.
 * Combined y start, integer in bits 26:15 (the same derivation the probe uses
 * for XSTART).
 */
/* ystart: rw32, reset unknown */
#define REX1_YSTART_OFFSET                           0x24u /* established */

/*
 * Draw end y, fraction.  Offset established by the ide test. Holds the end y
 * with the integer in bits 22:11, as XENDF.
 */
/* yendf: rw32, reset unknown */
#define REX1_YENDF_OFFSET                            0x28u /* established */

/*
 * Saved x start (the x that a block-draw returns to at the start of each row,
 * inferred from its name and the context save). lightPcxSwap saves it with the
 * other window registers. Offset established by the ide test. Twelve bits kept.
 * No routine of the IRIX 6.2 GL that draws lines, triangle rows, spans, points,
 * clears or copies stores it. devices/rex1/true-lines.md.
 */
/* xsave: rw32, reset unknown */
#define REX1_XSAVE_OFFSET                            0x2cu /* established */

/*
 * Line-draw minor-axis slope. Never written by the shipped light code for
 * rectangles, text or points. Only the name (ide) and the slot between XSAVE
 * and XYMOVE support it. Offset established by the ide test. Written and read
 * back unmasked. Sign rule, from the ide REX test: 17 bits are kept, bit 31 is
 * the sign, bit 16 of a negative magnitude is ignored and the result is the
 * 17-bit two's complement. The GL writes 256.0 + m or -256.0 + m (0x43800000
 * plus the fraction), which gives 15 fraction bits; each step along the major
 * axis adds it to the minor coordinate. devices/rex1/true-lines.md.
 */
/* minorslope: rw32, reset unknown */
#define REX1_MINORSLOPE_OFFSET                       0x30u /* established */

/*
 * Copy source offset: x delta in the high 16 bits and y delta in the low 16,
 * each source minus destination, in stored coordinates (display row = stored
 * y). The X server (X server driver function rexCopyRect) computes dx as source
 * x minus destination x0 and dy as source y minus destination y0, masks dy to
 * 16 bits and stores (dx << 16) | dy at the GO alias (0x834) after the
 * rectangle and the copy command 0x80329 are set up; it chooses XSTARTI..XENDI
 * ascending when dx is not negative and descending when it is, and
 * YSTARTI..YENDI ascending when dy is not negative and descending when it is,
 * so the engine must honour either order of the two registers. That fixes the
 * sign for the X server and agrees with NetBSD. The only remaining doubt is the
 * PROM copy routine, whose callers were not found. For a destination x0 below 4
 * and dx negative the X server also stores XYWIN 0x07fc0800 around the copy
 * (see XYWIN). The ide mask 0x7ff07ff shows eleven bits kept per half. A qtest
 * can discriminate: write 0x00100005 at 0x34 and 0x80329 or 0x30080329 at 0,
 * then a copy from (x+16, y+5) happens when 0x800 is touched, and a rectangle
 * with YSTARTI greater than YENDI copies bottom row first. The IRIX 6.2 GL's
 * rectangle copy stores the same layout with the word 0x30280329.
 */
/* xymove: rw32, reset unknown */
#define REX1_XYMOVE_OFFSET                           0x34u /* established */

/*
 * Foreground pixel colour (the ide test reads a write back through COLORRED at
 * 0x3c as (value & 0xff) << 11), an 8-bit index into the colour map (the board
 * has 8 bits per pixel). The kernel's colour routine stores the index at this
 * offset after the busy bit clears; the PROM's colour routine does too. The ide
 * test calls the register COLORREDI with an 8-bit mask; RED because the chip's
 * colour path starts with red.
 */
/* colorredi: rw32, reset unknown */
#define REX1_COLORREDI_OFFSET                        0x38u /* established */

/*
 * Red channel with fraction for shaded draws, 20 bits in the ide mask. Offset
 * by name order. Offset established by the ide test. COLORRED holds the red
 * channel with its integer part (COLORREDI, 8 bits) in bits 18:11. Shaded
 * draws: the IRIX 6.2 GL stores the float c + 6144.0, so the word is 0x45c00000
 * + c * 2048 (bits above 19 are ignored by the chip, 9 integer and 11 fraction
 * bits are kept) and a negative c wraps modulo 512. Whether the chip clamps or
 * wraps out-of-range colours is unknown. devices/rex1/shaded-drawing.md.
 */
/* colorred: rw32, reset unknown */
#define REX1_COLORRED_OFFSET                         0x3cu /* established */

/*
 * Green channel integer (shaded draws). Never written by shipped light code.
 * Offset from the ide name order and NetBSD. Offset established by the ide
 * test. A write here appears in COLORGREEN bits 18:11.
 */
/* colorgreeni: rw32, reset unknown */
#define REX1_COLORGREENI_OFFSET                      0x40u /* established */

/*
 * Green channel with fraction. Offset established by the ide test. 20 bits
 * kept. Same format as COLORRED.
 */
/* colorgreen: rw32, reset unknown */
#define REX1_COLORGREEN_OFFSET                       0x44u /* established */

/*
 * Blue channel integer. Offset established by the ide test. A write here
 * appears in COLORBLUE bits 18:11.
 */
/* colorbluei: rw32, reset unknown */
#define REX1_COLORBLUEI_OFFSET                       0x48u /* established */

/*
 * Blue channel with fraction. Offset established by the ide test. 20 bits kept.
 * Same format as COLORRED. A store at the GO alias (0x84c) runs the latched
 * command: the GL's flat RGB lines and clears end that way.
 */
/* colorblue: rw32, reset unknown */
#define REX1_COLORBLUE_OFFSET                        0x4cu /* established */

/*
 * Red slope for shaded lines and spans. Not written by shipped light code.
 * Offset established by the ide test. Slope registers are signed: the ide test
 * expects bit 19 of the stored value to read back also in bit 20. Sign rule,
 * from the ide REX register test: bit 31 is the sign and bits 19:0 the
 * magnitude; with bit 31 set the stored value is the 21-bit two's complement of
 * the magnitude (bit 20 of the written value is cleared first), read back with
 * bit 20 ORed with bit 19; bits 30:21 of a write are ignored. The GL writes m +
 * 6144.0 for a positive slope and m - 6144.0 for a negative one.
 * devices/rex1/shaded-drawing.md.
 */
/* slopered: rw32, reset unknown */
#define REX1_SLOPERED_OFFSET                         0x50u /* established */

/*
 * Green slope. Not written by shipped light code. NetBSD names offset 0x54 of
 * the configuration page WCLOCKREV, which is a different page. Offset
 * established by the ide test. As SLOPERED. Same rule as SLOPERED.
 */
/* slopegreen: rw32, reset unknown */
#define REX1_SLOPEGREEN_OFFSET                       0x54u /* established */

/*
 * Blue slope. Not written by shipped light code. Offset established by the ide
 * test. As SLOPERED. Same rule as SLOPERED. A store at the GO alias (0x858)
 * runs the latched command: the GL's smooth RGB lines end that way.
 */
/* slopeblue: rw32, reset unknown */
#define REX1_SLOPEBLUE_OFFSET                        0x58u /* established */

/*
 * Background colour index used for pattern zeros when ZOPAQUE is set. The
 * shipped kernel and PROM glyph paths never write it (transparent background);
 * NetBSD does. Offset established by the ide test. Eight bits kept.
 */
/* colorback: rw32, reset unknown */
#define REX1_COLORBACK_OFFSET                        0x5cu /* established */

/*
 * Pixel pattern for the pattern-enabled commands. Software writes it at the GO
 * alias (0x860): each write draws one row of the glyph, taking pattern bits 31
 * downward, the row's bits shifted into the top half for 16-wide glyphs (the
 * kernel shifts each halfword left by 16) and into bit 24 for 8-wide (NetBSD).
 * With STOPONX, XYCONTINUE and BLOCK, y steps by one row after each write. A
 * qtest can discriminate: set XSTARTI, XENDI, YSTARTI, write command 0x300005b9
 * at 0 and 0x80000000 at 0x860, and exactly one pixel at the start column is
 * drawn.
 */
/* zpattern: rw32, reset unknown */
#define REX1_ZPATTERN_OFFSET                         0x60u /* established */

/*
 * Line stipple pattern. Not written by shipped light code. Offset established
 * by the ide test. Fully read/write.
 */
/* lspattern: rw32, reset unknown */
#define REX1_LSPATTERN_OFFSET                        0x64u /* established */

/*
 * Line stipple mode. Not written by shipped light code. NetBSD's
 * configuration-page name CFGMODE for offset 0x68 is a different page. Offset
 * established by the ide test. 20 bits kept. The IRIX 6.2 GL line stipple
 * writes 0xf0000 | n << 8 | n: length field 15 in 19:16 (a 32-bit pattern, as
 * the X server's (width - 17) << 16) and n in 15:8 and 7:0, where n is the GL
 * repeat factor 1 to 256 masked to 8 bits (256 is stored as 0; no subtraction
 * of one).
 */
/* lsmode: rw32, reset unknown */
#define REX1_LSMODE_OFFSET                           0x68u /* established */

/*
 * Antialias weight. Not written by shipped light code. Offset established by
 * the ide test. Fully read/write. The IRIX 6.2 GL writes 0xdb987642 once at
 * context set-up (the IRIS GL library holds the same constant) and nothing in
 * it reads or rewrites the register; the GL antialiases lines in software. No
 * dither role is evidenced. devices/rex1/shaded-drawing.md.
 */
/* aweight: rw32, reset unknown */
#define REX1_AWEIGHT_OFFSET                          0x6cu /* established */

/*
 * Read/write auxiliary word used to read and write pixel memory with a draw
 * command. lightInitInfo writes 0x01081020 here, then 0x09090909 with a
 * 0x30210021 command, runs 0x30200023 and compares the result word read back at
 * 0x870 with 0x01080909 or 0x09091020 to record a 0, 1 or 0xff in byte 0x29 of
 * the board info it hands to GfxRegisterBoard. Data flow (inferred from the
 * constants): the first write puts the four bytes 01 08 10 20 into pixels 0 to
 * 3 of stored row 0, the second replaces exactly one pair of them with 09
 * (outcome 0 = pixels 2 and 3 replaced, outcome 1 = pixels 0 and 1 replaced, if
 * the high byte is pixel 0), and the read returns the four pixels. All three
 * commands are executed through RWAUX1's GO alias, so RWAUX1 is the data port
 * of the probe. What each outcome means for the board (pixel memory
 * arrangement): unknown; no object read uses info byte 0x29 afterwards. The
 * PROM runs the probe unconditionally; the kernel runs it only when CONFIGMODE
 * bits 7:4 read 0. A qtest can discriminate only by replaying that sequence,
 * which needs the draw unit to move words between RWAUX1 and the frame buffer;
 * any model that yields 0x01080909 or 0x09091020 satisfies every shipped
 * reader, and a choice between them is an approximation.
 */
/* rwaux1: rw32, reset unknown */
#define REX1_RWAUX1_OFFSET                           0x70u /* established */

/*
 * Second read/write auxiliary word. Not written by shipped light code. Offset
 * established by the ide test. Fully read/write.
 */
/* rwaux2: rw32, reset unknown */
#define REX1_RWAUX2_OFFSET                           0x74u /* established */

/*
 * Plane write mask for read/write pixel access. lightInitInfo and the PROM
 * write 0xff (all eight planes) before the pixel-memory probe. The ide mask
 * 0xffff shows sixteen bits kept, and the ide graphics shell's write-mask
 * command stores its argument here, so the low byte is the pixel write mask
 * (the shipped header's comment calls the register readmask and writemask, in
 * that order, without saying which half is which). The kernel's board-info
 * routine writes it only when CONFIGMODE bits 7:4 read 0; the PROM writes it
 * unconditionally. The X server never writes RWMASK: it keeps the write mask in
 * XSTATE bits 23:16, but it is not the 0xff the board-info routine left:
 * lightPcxSwap saves RWMASK into, and restores it from, the rendering node's
 * image, a node made by lightCreateDDRN has a zero image, and the first load of
 * a never-saved node writes 0 (platforms/lg1/colormap-install.md). The shipped
 * desktop draws with RWMASK 0 and would be blank if hardware gated RWAUX1
 * host-data writes or reads (tile fill, PutImage, GetImage) with it, so it is
 * inferred not to; what it does gate is unknown. The IRIX 6.2 GL stores 0xff at
 * context set-up, then after every draw-buffer change the window's full mask
 * (0xf for the 4-bit window, 3 for the overlay, 0xff for the 8-bit one) or 0
 * when the GL draw buffer is none, and no other value; it expects the mask to
 * gate its own draws (nonzero logic-operation nibble, no COLORAUX). Inferred;
 * devices/rex1/gl-context-state.md.
 */
/* rwmask: rw32, reset unknown */
#define REX1_RWMASK_OFFSET                           0x78u /* established */

/*
 * Screen mask 1, x range: maximum x in bits 25:16 and minimum x in bits 9:0,
 * each clipped to 0..1023 (the object clamps with 0x3ff). Software computes the
 * window's visible rectangle clipped to the screen and writes it here when
 * window 1 is the active one.
 */
/* smask1x: rw32, reset unknown */
#define REX1_SMASK1X_OFFSET                          0x7cu /* established */

/*
 * Screen mask 1, y range, same packing, clipped to 0..767 (0x2ff). The y values
 * are flipped (height minus row minus one) before packing, so they use the same
 * stored-y convention as the drawing registers: row counted from the top of the
 * screen (see the Y origin section of the REX1 page).
 */
/* smask1y: rw32, reset unknown */
#define REX1_SMASK1Y_OFFSET                          0x80u /* established */

/*
 * Draw end x (integer, inclusive): the last column a STOPONX command draws. The
 * ide test reads it back through XENDF (0x18) as (value & 0xfff) << 11.
 */
/* xendi: rw32, reset unknown */
#define REX1_XENDI_OFFSET                            0x84u /* established */

/*
 * Draw end y (integer, inclusive), top-down row like YSTARTI. The glyph
 * commands also use the order of YSTARTI and YENDI to pick the direction rows
 * advance: toward YENDI. The ide test reads it back through YENDF (0x28) as
 * (value & 0xfff) << 11. light_sboxfi and the PROM fill store 767 minus the top
 * row here and 767 minus the bottom row in YSTARTI, so YSTARTI <= YENDI.
 */
/* yendi: rw32, reset unknown */
#define REX1_YENDI_OFFSET                            0x88u /* established */

/*
 * First of six consecutive screen-mask words, in the order SMASK2X, SMASK2Y,
 * SMASK3X, SMASK3Y, SMASK4X, SMASK4Y. The six-word run is established by the
 * context save and the name-to-word assignment by the ide test's offsets.
 * Packing as smask1x. Offset established by the ide test. The six names map to
 * the six consecutive words in this order.
 */
/* smask2x: rw32, reset unknown */
#define REX1_SMASK2X_OFFSET                          0x4790u /* established */

/*
 * Screen mask word 2Y. Packing as smask1x. Added in the 2026-11-23 review so
 * the generated header names all six.
 */
/* smask2y: rw32, reset unknown */
#define REX1_SMASK2Y_OFFSET                          0x4794u /* established */

/*
 * Screen mask word 3X. Packing as smask1x. Added in the 2026-11-23 review so
 * the generated header names all six.
 */
/* smask3x: rw32, reset unknown */
#define REX1_SMASK3X_OFFSET                          0x4798u /* established */

/*
 * Screen mask word 3Y. Packing as smask1x. Added in the 2026-11-23 review so
 * the generated header names all six.
 */
/* smask3y: rw32, reset unknown */
#define REX1_SMASK3Y_OFFSET                          0x479cu /* established */

/*
 * Screen mask word 4X. Packing as smask1x. Added in the 2026-11-23 review so
 * the generated header names all six.
 */
/* smask4x: rw32, reset unknown */
#define REX1_SMASK4X_OFFSET                          0x47a0u /* established */

/*
 * Screen mask word 4Y. Packing as smask1x. Added in the 2026-11-23 review so
 * the generated header names all six.
 */
/* smask4y: rw32, reset unknown */
#define REX1_SMASK4Y_OFFSET                          0x47a4u /* established */

/*
 * Second auxiliary control word. Both initialisations store 0x20000000.
 * lightSetDestinationPlanes keeps bits 28:0 of the window's saved value, ORs in
 * the request's top three bits and, for the window on screen, waits for the
 * engine to go idle and stores the result here, so the top three bits select
 * which plane group a draw reaches. The shipped header names them as one
 * three-bit code, not as three flags: NOPLANES 0, PIXELPLANES 1, OVERLAYPLANES
 * 2 and CIDPLANES 3 (shifted left 29). The X server's plane-group writes agree:
 * 0x20000000 for the displayed pixel planes, 0x40000000 for the overlay clear
 * and 0x60000000 for the window-id fill, whose value is limited to 0 to 3
 * (rexDrawCID) like the ide CID memory test. The ide mask 0x7fffffff shows 31
 * bits kept. The X server's line, point and span batches (rexLineSS,
 * rexSegmentSS, rexPolyPoint, rexSolidFillSpans) store (group << 29) | 0xf11 at
 * the start and plain group << 29 at the end, so the low twelve bits are used
 * and the value 0xf11 is not a command word. The header names bits 3:0 SMASK0
 * to SMASK3 (screen mask enables), bits 7:4 their inside/outside polarity and
 * bits 23:8 four CID match nibbles, so 0xf11 reads as screen mask 0 enabled,
 * inside polarity and CID match nibble 1 set to 0xf (inferred from the names;
 * no shipped code states the effect). GL and kernel window contexts use 0xff1
 * in the low twelve bits (the X server's batches 0xf11): by the header's names
 * screen mask enable bit 0 (the first pair, SMASK1X and SMASK1Y) with inside
 * polarity bit 4, polarity bits 7:5 set on disabled masks, CID match nibble 1 =
 * 0xf. devices/rex1/gl-context-state.md.
 */
/* aux2: rw32, reset unknown */
#define REX1_AUX2_OFFSET                             0x47a8u /* established */
#define REX1_AUX2_PLANEGROUP_SHIFT                   29 /* inferred */
#define REX1_AUX2_PLANEGROUP_MASK                    0x7u
#define REX1_AUX2_PLANEGROUP_INPLACE (REX1_AUX2_PLANEGROUP_MASK << REX1_AUX2_PLANEGROUP_SHIFT)
#define REX1_AUX2_CIDMATCH4_SHIFT                    20 /* inferred */
#define REX1_AUX2_CIDMATCH4_MASK                     0xfu
#define REX1_AUX2_CIDMATCH4_INPLACE (REX1_AUX2_CIDMATCH4_MASK << REX1_AUX2_CIDMATCH4_SHIFT)
#define REX1_AUX2_CIDMATCH3_SHIFT                    16 /* inferred */
#define REX1_AUX2_CIDMATCH3_MASK                     0xfu
#define REX1_AUX2_CIDMATCH3_INPLACE (REX1_AUX2_CIDMATCH3_MASK << REX1_AUX2_CIDMATCH3_SHIFT)
#define REX1_AUX2_CIDMATCH2_SHIFT                    12 /* inferred */
#define REX1_AUX2_CIDMATCH2_MASK                     0xfu
#define REX1_AUX2_CIDMATCH2_INPLACE (REX1_AUX2_CIDMATCH2_MASK << REX1_AUX2_CIDMATCH2_SHIFT)
#define REX1_AUX2_CIDMATCH1_SHIFT                    8 /* inferred */
#define REX1_AUX2_CIDMATCH1_MASK                     0xfu
#define REX1_AUX2_CIDMATCH1_INPLACE (REX1_AUX2_CIDMATCH1_MASK << REX1_AUX2_CIDMATCH1_SHIFT)
#define REX1_AUX2_SMASK_INSIDE_SHIFT                 4 /* inferred */
#define REX1_AUX2_SMASK_INSIDE_MASK                  0xfu
#define REX1_AUX2_SMASK_INSIDE_INPLACE (REX1_AUX2_SMASK_INSIDE_MASK << REX1_AUX2_SMASK_INSIDE_SHIFT)
#define REX1_AUX2_SMASK_ENABLE_SHIFT                 0 /* inferred */
#define REX1_AUX2_SMASK_ENABLE_MASK                  0xfu
#define REX1_AUX2_SMASK_ENABLE_INPLACE (REX1_AUX2_SMASK_ENABLE_MASK << REX1_AUX2_SMASK_ENABLE_SHIFT)

/*
 * VRAM diagnostic access. No shipped kernel or PROM runtime path touches it;
 * the ide VRAM test is the only candidate user and was not read. Offset and
 * role: unknown.
 */
/* diagvram: rw32, reset unknown */
#define REX1_DIAGVRAM_OFFSET                         0x47d8u /* inferred */

/*
 * Port to the pixel clock generator and the board configuration byte; the byte
 * is picked by CFGSEL. Reading with CFGSEL 4 (after a dummy read of the GO
 * alias and a one microsecond wait) returns: bits 2:0 board revision, bits 5:3
 * monitor type, bit 6 set when no video board is present. light_init stores
 * them in bytes 0x28, 0x2b and 0x2c of the board info. Writing with CFGSEL 2
 * clocks the clock generator's program bytes in: initClock writes 17 bytes in a
 * row to the SET and GO aliases, selected by board revision (below 2: the first
 * of the two 17-byte clock tables in the driver, 2 and above: the second). A
 * qtest can discriminate: CFGSEL 4 then a read of GO and SET returns the
 * configured byte; a model needs a settable board revision to take the revision
 * 1 path (the PROM and kernel need the revision below 2 branch for the Bt479
 * colour map).
 */
/* wclock: rw32, reset unknown */
#define REX1_WCLOCK_OFFSET                           0x47e4u /* established */

/*
 * Port to the colour map chip. CFGSEL picks the chip register (see CFGSEL
 * constants). Software writes the same byte to RWDAC and to its GO alias; the
 * second write is what performs the transfer. A read of its GO alias returns
 * the chip register value. light_read_bt_colormaps and light_read_lut_colormaps
 * issue one GO read, discard it, and then read the GO alias 768 times per bank
 * (bulk reads: the same one-deep pipeline as RWVC1 fits). The X server reads
 * the command register back (CONFIGSEL 6: GO read, then RWDAC read) for
 * read-modify-write of the blank bit (X server driver function rexBlankScreen)
 * and in rexDisplayCursor, so the DAC command register must be readable.
 * Whether the SET read after a GO read adds anything beyond the pipeline:
 * unknown.
 */
/* rwdac: rw32, reset unknown */
#define REX1_RWDAC_OFFSET                            0x47e8u /* established */

/*
 * Three-bit function selector shared by WCLOCK, RWDAC and RWVC1: the value
 * written here is the chip register index the next access to any of the three
 * ports addresses. Values 0 to 6 are used (CFGSEL constants); 7 is not written
 * by shipped code. Readback returns the written value (lightPositionCursor
 * saves and later restores it by reading it back). A qtest can discriminate:
 * write 5, read back 5; write 8, read back 0 (the 0x7 mask, from the ide test).
 */
/* configsel: rw32, reset unknown */
#define REX1_CONFIGSEL_OFFSET                        0x47ecu /* established */

/*
 * Port to the video controller (VC1), same SET/GO scheme as RWDAC with its GO
 * alias 0x800 above it. A write stores the byte at SET and again at GO; a GO
 * store alone also works (lightSetDisplayMode stores only the GO alias). Reads:
 * every reader does GO read then SET read for a single byte, and the bulk
 * readers (light_read_displaymodes, light_read_scan) issue one GO read whose
 * value they discard and then read only the GO alias, once per byte. Both fit a
 * one-deep read pipeline: a GO read returns the byte fetched by the previous GO
 * read and starts the fetch of the next, and a SET read returns the byte the
 * last GO read fetched; a model where a GO read returns and consumes the
 * current byte makes every bulk reader skip its first byte. The kernel retrace
 * handler and lightPositionCursor read the VC1 address counter back through
 * CONFIGSEL 4 (low) and 5 (high) while a user process may be in the middle of a
 * data transfer; see devices/vc1. The VC1 internal register file behind CFGSEL
 * is in devices/vc1.
 */
/* rwvc1: rw32, reset unknown */
#define REX1_RWVC1_OFFSET                            0x47f0u /* established */

/*
 * Written with 0 in the middle of a window context swap. lightPcxSwap reads ten
 * registers (XSTART, YSTART, COLORRED, COLORGREEN, COLORBLUE, LSPATTERN,
 * LSMODE, ZPATTERN, XSAVE, RWAUX1), stores 0 here, then reads about twenty-four
 * more (XSTART, YSTART, the colour and slope registers, XENDF, YENDF, AUX1, the
 * pattern registers, XSAVE, MINORSLOPE, XYMOVE, COLORBACK, AWEIGHT, RWAUX1,
 * RWAUX2, RWMASK, COMMAND, SMASK1X, SMASK1Y); the load side mirrors it.
 * Inferred from the repeated registers (XSTART, COLORRED and others appear in
 * both passes): the engine holds two copies of part of the drawing state and a
 * write here switches which one the register offsets address. A flat model that
 * keeps one copy and ignores the write returns the same values in both passes
 * and restores consistently. Whether a read is defined: unknown.
 */
/* togglectxt: w32, reset unknown */
#define REX1_TOGGLECTXT_OFFSET                       0x47f4u /* inferred */

/*
 * Configuration and status. Bit 0 is the engine busy flag: all software spins
 * until it is clear before touching a drawing register (the kernel and the PROM
 * do it in every drawing routine). Bits 28:24 (mask 0x1f000000) must also be
 * zero before a VC1 access in lightPositionCursor and the retrace handler:
 * inferred to be a count of commands still queued in the FIFO, which the busy
 * bit alone does not cover. The X server polls a second count, bits 12:8 (five
 * bits): before a burst of register stores it waits until that field is at most
 * 21 minus its gfifo level setting, 14 at the default level 7 (rexLineSS,
 * rexPolyPoint, rexZeroPolyArc, rexImageGlyphBltTE8; fixed limits of 5 and 8
 * appear in rexSolidFillSpans), so the 5-bit field is inferred to be the
 * graphics FIFO fill level, with the level setting the number of stores the X
 * server allows per primitive. Bits 7:4 are read by lightInitInfo (value 0
 * triggers the pixel-memory probe described under rwaux1, any other value plus
 * one is stored as a board option byte). initRex and the pixel DMA path store
 * 0x807fe000. The X server (driver function rexInitHW) stores 0x80000000 |
 * 0x40000000 | 0x00180000 | (level << 13) with level 7 by default (see the
 * CPU-board ranges below, or the number in the environment variable
 * REX_GFIFO_LEVEL), raises the level field to 31 for glyph and arc runs
 * (0xc01be000) and writes 0x80000000 | 0x00180000 | (level << 13), without bit
 * 30, only around the pixel DMA of a large PutImage (the CPU-store PutImage
 * path leaves bit 30 set); so bits 17:13 are inferred to be a FIFO-level
 * threshold (the interrupt on GIO line 0 or the stall point), bits 20:19 are
 * constant 11 in every X server store, and bit 30 is set except while the pixel
 * DMA feeds RWAUX1 (role unknown). The default level of 7 becomes 9 or 11 only
 * when an inventory value in the CPU-board range is read at start (0x400 to
 * 0x43f: 9, or 11 with the board-info flags bit 6 set; 0x440 to 0x1fff: 7, or 9
 * with bit 6 set). lightPcxSwap saves the word xor 0x80000000 and restores it
 * unchanged, so bit 31 is read inverted of what was written. Role of bit 31 and
 * of bits 22:21: unknown. A qtest can discriminate: bit 0 reads 1 while a
 * command is executing and 0 after; the PROM 300000 microsecond polling loop in
 * lightProbe (done when bit 0 clears) must not time out; a model with
 * synchronous drawing may return 0 in bits 28:24 and 12:8 and satisfy every
 * shipped reader.
 */
/* configmode: rw32, reset unknown */
#define REX1_CONFIGMODE_OFFSET                       0x47f8u /* established */

/*
 * Window origin offset: x in bits 27:16 and y in bits 11:0, 0x800 each at init
 * (the window offset of 2048 that centres a 12-bit coordinate space; the
 * centring is inferred). NetBSD match accepts a board whose XYWIN reads
 * 0x08000800. The X server stores 0x08000800 in rexInitHW and, for a
 * right-to-left copy or a PutImage that starts below x = 4, temporarily stores
 * 0x07fc0800 (x origin 4 lower) and loads XSTARTI and XENDI 4 higher, then
 * restores 0x08000800 (X server driver functions rexCopyRect, rexDrawImage,
 * rexValidateWindowPriv). Inferred from that pairing: drawing coordinate =
 * loaded coordinate plus (x origin minus 0x800), so the pair puts the screen x
 * of the run unchanged while keeping the engine coordinate at 4 or more; a
 * model that applies the origin offset to the coordinates gets the right
 * pixels, one that ignores XYWIN draws four pixels to the right. The ide test
 * keeps 12 bits per half.
 */
/* xywin: rw32, reset unknown */
#define REX1_XYWIN_OFFSET                            0x47fcu /* established */

/* established */
#define REX1_BASE_HEAD0                              0x1f3f0000u
/* established */
#define REX1_BASE_HEAD1                              0x1f3f8000u
#define REX1_CFGSEL_DAC_ADDR                         0x0u /* established */
#define REX1_CFGSEL_HADDR                            0x5u /* established */
#define REX1_CFGSEL_LADDR                            0x4u /* established */
#define REX1_CFGSEL_PALETTE                          0x1u /* established */
#define REX1_CFGSEL_PIXMASK                          0x2u /* established */
#define REX1_CFGSEL_RDADDR                           0x3u /* established */
#define REX1_CFGSEL_SYSCTL                           0x6u /* established */
#define REX1_CMD_BLOCK                               0x8u /* established */
/* established */
#define REX1_CMD_CLEAR_RGB_DITHER                    0x3000c329u
/* established */
#define REX1_CMD_COPY_RECT                           0x30080329u
/* established */
#define REX1_CMD_COPY_RECT_GL                        0x30280329u
#define REX1_CMD_COPY_RECT_STATE                     0x80329u /* established */
#define REX1_CMD_DITHER                              0x8000u /* inferred */
#define REX1_CMD_DRAW                                0x1u /* established */
#define REX1_CMD_ENLSPATTERN                         0x800u /* inferred */
#define REX1_CMD_ENZPATTERN                          0x400u /* established */
/* established */
#define REX1_CMD_FILL_RECT                           0x30000329u
#define REX1_CMD_FILL_RECT_STATE                     0x329u /* established */
/* established */
#define REX1_CMD_GLYPH16                             0x300005b9u
/* established */
#define REX1_CMD_GLYPH_PIECE                         0x300005a1u
/* established */
#define REX1_CMD_GL_TRIANGLE_ROW_SHADED_MASKED       0x3212c5b1u
#define REX1_CMD_HOSTDATA                            0x200000u /* inferred */
#define REX1_CMD_HOSTDATA_READ                       0x2000abu /* established */
#define REX1_CMD_HOSTDATA_WRITE                      0x2000a9u /* established */
#define REX1_CMD_INITFRAC                            0x40000u /* unknown */
#define REX1_CMD_LENGTH32                            0x10u /* inferred */
#define REX1_CMD_LOGICOP_SHIFT                       0x1cu /* established */
#define REX1_CMD_LOGICSRC                            0x80000u /* inferred */
#define REX1_CMD_LRQPOLY                             0x2000000u /* unknown */
#define REX1_CMD_LSADVLAST                           0x1000u /* inferred */
#define REX1_CMD_LSCONTINUE                          0x2000u /* inferred */
#define REX1_CMD_OP_READ                             0x2u /* inferred */
#define REX1_CMD_PIXMEM_BIT16                        0x10000u /* inferred */
/* established */
#define REX1_CMD_PIXMEM_READ                         0x30200023u
/* established */
#define REX1_CMD_PIXMEM_WRITE_A                      0x30200021u
/* established */
#define REX1_CMD_PIXMEM_WRITE_B                      0x30210021u
/* established */
#define REX1_CMD_POINT                               0x30000001u
#define REX1_CMD_QUAD                                0x20u /* inferred */
#define REX1_CMD_RGBMODE                             0x4000u /* inferred */
#define REX1_CMD_SHADE                               0x20000u /* inferred */
#define REX1_CMD_SHADECONTINUE                       0x100000u /* inferred */
#define REX1_CMD_SPAN                                0x121u /* established */
#define REX1_CMD_SPAN_LSPATTERN                      0x921u /* inferred */
#define REX1_CMD_STOPONX                             0x100u /* established */
#define REX1_CMD_STOPONY                             0x200u /* established */
#define REX1_CMD_TILE_HOSTDATA                       0x200121u /* established */
#define REX1_CMD_XMAJOR                              0x40u /* inferred */
#define REX1_CMD_XYCONTINUE                          0x80u /* established */
#define REX1_CMD_ZCONTINUE                           0x1000000u /* unknown */
#define REX1_CMD_ZOPAQUE                             0x800000u /* inferred */
#define REX1_GO_OFFSET                               0x800u /* established */
/* established */
#define REX1_PROBE_READBACK                          0x33c0000u
#define REX1_VC1_SYSCTL_CURSOR                       0x10u /* inferred */
#define REX1_VC1_SYSCTL_CURSOR_ON                    0x20u /* inferred */
#define REX1_VC1_SYSCTL_VIDEO_ON                     0x4u /* established */
#define REX1_XRES                                    0x400u /* established */
#define REX1_YRES                                    0x300u /* established */

#endif /* REX1_GEN_H */
