/* generated from devices/rex1/registers.toml by defs-gen - do not edit, change
 * the source */
/* defs-gen 3 */
/* input sha256 32b46defb7052aecb55b58a66bcf10e5a513a66f9d7dc9843c8c0b369b55646b */
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
 * not set by shipped code) and bits 21 and 16 in the two probe commands
 * 0x30200021, 0x30210021 and 0x30200023, which lightInitInfo uses to learn the
 * board's pixel memory (see rwaux1); those bits are unknown.
 */
/* command: rw32, reset unknown */
#define REX1_COMMAND_OFFSET                          0x0u /* established */

/*
 * Auxiliary control word, one per window context. initRex zeroes it.
 * lightAux1Register builds a value from a window's saved value with bits 4:2
 * cleared, sets bit 4 when the request word's second field is 1, bit 2 when bit
 * 0 of its third field is set and bit 3 when bit 1 is set, then stores it here
 * (only for the window that owns the screen) or in the window's saved context.
 * Which pixel behaviour each of bits 2, 3 and 4 enables: unknown, no shipped
 * code names them. ide's register test reads it back whole (test mask 0x3ff).
 */
/* aux1: rw32, reset unknown */
#define REX1_AUX1_OFFSET                             0x4u /* established */

/*
 * Draw x state. The only shipped write is the 0x03ff0000 that precedes each
 * full-screen clear; the role is unknown (it may be a pre-loaded x counter for
 * block draws; no source says). Offset established by the ide test. The ide
 * test writes all 32 bits and expects them back unmasked.
 */
/* xstate: rw32, reset unknown */
#define REX1_XSTATE_OFFSET                           0x8u /* established */

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
 * was written; the value read is the probe's presence test (PROBE_READBACK).
 * Whether a write here reflects in XSTARTI: unknown.
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
 * YSTART (0x24) expecting (value & 0xfff) << 15. Software stores 767 minus the
 * row, so y grows upward from the bottom of the 768-line screen.
 */
/* ystarti: rw32, reset unknown */
#define REX1_YSTARTI_OFFSET                          0x1cu /* established */

/*
 * Draw start y, fraction.  Offset established by the ide test. Mirror of
 * XSTARTF for y; a write appears in YSTART bits 26:4.
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
 */
/* xsave: rw32, reset unknown */
#define REX1_XSAVE_OFFSET                            0x2cu /* established */

/*
 * Line-draw minor-axis slope. Never written by the shipped light code for
 * rectangles, text or points. Only the name (ide) and the slot between XSAVE
 * and XYMOVE support it. Offset established by the ide test. Written and read
 * back unmasked.
 */
/* minorslope: rw32, reset unknown */
#define REX1_MINORSLOPE_OFFSET                       0x30u /* established */

/*
 * Copy source offset: x delta in the high 16 bits and y delta in the low 16,
 * each source minus destination (NetBSD: dx is from_x minus to_x). It is
 * written at the GO alias after the rectangle and the copy command are set up.
 * The ide mask 0x7ff07ff shows eleven bits kept per half. A qtest can
 * discriminate: write 0x00100005 at 0x34 and 0x30080329 at 0, then a copy from
 * (x+16, y+5) happens when 0x800 is touched (the exact polarity of y under the
 * bottom-up y axis is inferred).
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
 * channel with its integer part (COLORREDI, 8 bits) in bits 18:11.
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
 * kept.
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
 */
/* colorblue: rw32, reset unknown */
#define REX1_COLORBLUE_OFFSET                        0x4cu /* established */

/*
 * Red slope for shaded lines and spans. Not written by shipped light code.
 * Offset established by the ide test. Slope registers are signed: the ide test
 * expects bit 19 of the stored value to read back also in bit 20.
 */
/* slopered: rw32, reset unknown */
#define REX1_SLOPERED_OFFSET                         0x50u /* established */

/*
 * Green slope. Not written by shipped light code. NetBSD names offset 0x54 of
 * the configuration page WCLOCKREV, which is a different page. Offset
 * established by the ide test. As SLOPERED.
 */
/* slopegreen: rw32, reset unknown */
#define REX1_SLOPEGREEN_OFFSET                       0x54u /* established */

/*
 * Blue slope. Not written by shipped light code. Offset established by the ide
 * test. As SLOPERED.
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
 * established by the ide test. 20 bits kept.
 */
/* lsmode: rw32, reset unknown */
#define REX1_LSMODE_OFFSET                           0x68u /* established */

/*
 * Antialias weight. Not written by shipped light code. Offset established by
 * the ide test. Fully read/write.
 */
/* aweight: rw32, reset unknown */
#define REX1_AWEIGHT_OFFSET                          0x6cu /* established */

/*
 * Read/write auxiliary word used to read and write pixel memory with a draw
 * command. lightInitInfo writes 0x01081020 here, then 0x09090909 with a
 * 0x30210021 command, runs 0x30200023 and compares the result word read back at
 * 0x870 with 0x01080909 or 0x09091020 to record a 0, 1 or 0xff in byte 0x29 of
 * the board info it hands to GfxRegisterBoard. What the three outcomes mean for
 * the board (pixel memory population): unknown. A qtest can discriminate only
 * by replaying that sequence, which needs the draw unit to move words between
 * RWAUX1 and the frame buffer.
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
 * 0xffff shows sixteen bits kept.
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
 * are flipped (height minus row minus one) before packing, so they are in REX's
 * bottom-up coordinates.
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
 * Draw end y (integer, inclusive), bottom-up like YSTARTI. The ide test reads
 * it back through YENDF (0x28) as (value & 0xfff) << 11. light_sboxfi and the
 * PROM fill store 767 minus the top row here and 767 minus the bottom row in
 * YSTARTI, so YSTARTI <= YENDI.
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
 * which plane group a draw reaches. The meaning of each of those three bits:
 * unknown (no shipped code names the groups). The ide mask 0x7fffffff shows 31
 * bits kept.
 */
/* aux2: rw32, reset unknown */
#define REX1_AUX2_OFFSET                             0x47a8u /* established */

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
 * the chip register's value. light_read_bt_colormaps reads the GO alias
 * directly for the palette, the Bt479-based path also reads RWDAC; whether the
 * SET read after a GO read adds anything: unknown, NetBSD's VC1 read does read
 * GO then SET.
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
 * alias 0x800 above it. NetBSD's read: write CFGSEL, read the GO alias, read
 * the SET alias; the PROM does the same, with the kernel's read-modify-write
 * sequences storing the value to both aliases. The VC1's internal register file
 * behind CFGSEL is in devices/vc1.
 */
/* rwvc1: rw32, reset unknown */
#define REX1_RWVC1_OFFSET                            0x47f0u /* established */

/*
 * Written with 0 in the middle of a window context swap, after the registers
 * for the outgoing window have been saved and before the incoming ones are
 * loaded. Role inferred: switches REX to the other of two register contexts
 * (its ide-visible name is not printed). Whether a read is defined: unknown.
 */
/* togglectxt: w32, reset unknown */
#define REX1_TOGGLECTXT_OFFSET                       0x47f4u /* inferred */

/*
 * Configuration and status. Bit 0 is the engine busy flag: all software spins
 * until it is clear before touching a drawing register (the kernel and the PROM
 * do it in every drawing routine). Bits 28:24 (mask 0x1f000000) must also be
 * zero before a VC1 access in lightPositionCursor and the retrace handler:
 * inferred to be a count of commands still queued in the FIFO, which the busy
 * bit alone does not cover. Bits 7:4 are read by lightInitInfo (value 0
 * triggers the pixel-memory probe described under rwaux1, any other value plus
 * one is stored as a board option byte). initRex and the pixel DMA path store
 * 0x807fe000. lightPcxSwap saves the word xor 0x80000000 and restores it
 * unchanged, so bit 31 is read inverted of what was written. Bit 31 and bits
 * 22:13 role: unknown. A qtest can discriminate: bit 0 reads 1 while a command
 * is executing and 0 after; the PROM's 300000 microsecond polling loop in
 * lightProbe (done when bit 0 clears) must not time out.
 */
/* configmode: rw32, reset unknown */
#define REX1_CONFIGMODE_OFFSET                       0x47f8u /* established */

/*
 * Window origin offset: x in bits 27:16 and y in bits 11:0, 0x800 each at init
 * (the window offset of 2048 that centres a 12-bit coordinate space; the
 * centring is inferred). NetBSD's match accepts a board whose XYWIN reads
 * 0x08000800. The ide test keeps 12 bits per half.
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
#define REX1_CMD_COPY_RECT                           0x30080329u
#define REX1_CMD_DRAW                                0x1u /* established */
#define REX1_CMD_ENZPATTERN                          0x400u /* established */
/* established */
#define REX1_CMD_FILL_RECT                           0x30000329u
/* established */
#define REX1_CMD_GLYPH16                             0x300005b9u
/* established */
#define REX1_CMD_GLYPH_PIECE                         0x300005a1u
#define REX1_CMD_LENGTH32                            0x10u /* inferred */
#define REX1_CMD_LOGICOP_SHIFT                       0x1cu /* established */
#define REX1_CMD_LOGICSRC                            0x80000u /* inferred */
/* established */
#define REX1_CMD_POINT                               0x30000001u
#define REX1_CMD_QUAD                                0x20u /* inferred */
#define REX1_CMD_STOPONX                             0x100u /* established */
#define REX1_CMD_STOPONY                             0x200u /* established */
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
