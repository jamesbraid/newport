/* generated from devices/rex3/registers.toml by defs-gen - do not edit, change
 * the source */
/* SPDX-License-Identifier: BSD-3-Clause */
/* defs-gen 5 */
/* input sha256 ee5e5491333c9e9d96a9a57592a7f3eddc481a4336dd6192b5e160e71e5f7324 */
/* REX3 raster engine (Indy and Indigo2 graphics) */
#ifndef REX3_GEN_H
#define REX3_GEN_H

#include <stdint.h>


/* enum adrmode: Addressing mode. NetBSD defines span to aline; Linux also names
 * the last two, which no second source confirms. */
#define REX3_ADRMODE_SPAN                            0 /* established */
#define REX3_ADRMODE_BLOCK                           1 /* established */
#define REX3_ADRMODE_ILINE                           2 /* established */
#define REX3_ADRMODE_FLINE                           3 /* established */
#define REX3_ADRMODE_ALINE                           4 /* established */
#define REX3_ADRMODE_TLINE                           5 /* inferred */
#define REX3_ADRMODE_BLINE                           6 /* inferred */

/* enum dcbaddr: Display-bus slave address. Values 0 to 9 are in both headers
 * (NetBSD names 7 the DAC, Linux Bt445). Values 10, 11 and 15 are in Linux
 * alone, where they select the LG3 board-version and clock chips and a reserved
 * slot. */
#define REX3_DCBADDR_VC2                             0 /* established */
#define REX3_DCBADDR_CMAP_ALL                        1 /* established */
#define REX3_DCBADDR_CMAP0                           2 /* established */
#define REX3_DCBADDR_CMAP1                           3 /* established */
#define REX3_DCBADDR_XMAP_ALL                        4 /* established */
#define REX3_DCBADDR_XMAP0                           5 /* established */
#define REX3_DCBADDR_XMAP1                           6 /* established */
#define REX3_DCBADDR_RAMDAC                          7 /* established */
#define REX3_DCBADDR_VIDEO_CC1                       8 /* established */
#define REX3_DCBADDR_VIDEO_AB1                       9 /* established */
#define REX3_DCBADDR_LG3_BDVERS0                     10 /* inferred */
#define REX3_DCBADDR_ICS1562                         11 /* inferred */
#define REX3_DCBADDR_RESERVED                        15 /* inferred */

/* enum dcbwidth: Number of bytes of a DCBDATA word that go over the display
 * bus, as Linux's W4, W1, W2 and W3 name the values 0 to 3
 * (devices/rex3/byte-lanes.md). */
#define REX3_DCBWIDTH_W4                             0 /* established */
#define REX3_DCBWIDTH_W1                             1 /* established */
#define REX3_DCBWIDTH_W2                             2 /* established */
#define REX3_DCBWIDTH_W3                             3 /* established */

/* enum depth: Frame-buffer plane depth in bits, as the headers name the values
 * DD4, DD8, DD12 and DD24. */
#define REX3_DEPTH_D4                                0 /* established */
#define REX3_DEPTH_D8                                1 /* established */
#define REX3_DEPTH_D12                               2 /* established */
#define REX3_DEPTH_D24                               3 /* established */

/* enum dfactor: Blend destination factor (zero, one, source colour, its
 * complement, source alpha, its complement). Values 6 and 7 are not named. */
#define REX3_DFACTOR_ZERO                            0 /* established */
#define REX3_DFACTOR_ONE                             1 /* established */
#define REX3_DFACTOR_SC                              2 /* established */
#define REX3_DFACTOR_MSC                             3 /* established */
#define REX3_DFACTOR_SA                              4 /* established */
#define REX3_DFACTOR_MSA                             5 /* established */

/* enum hostdepth: Host pixel depth in bits. Linux names value 3 HD32 and NetBSD
 * HD24; devices/rex3/host-pixels.md grades the packing, which has an 8-8-8-8
 * word. */
#define REX3_HOSTDEPTH_H4                            0 /* established */
#define REX3_HOSTDEPTH_H8                            1 /* established */
#define REX3_HOSTDEPTH_H12                           2 /* established */
#define REX3_HOSTDEPTH_H32                           3 /* established */

/* enum logicop: Logic operation applied between the new and the old pixel, in
 * the order and with the names both headers give. The value names which
 * operation; value 3, replace, is what NetBSD's console fill and glyph code
 * use. The operand roles follow the names and are inferred. */
#define REX3_LOGICOP_ZERO                            0 /* established */
#define REX3_LOGICOP_AND                             1 /* established */
#define REX3_LOGICOP_ANDR                            2 /* established */
#define REX3_LOGICOP_SRC                             3 /* established */
#define REX3_LOGICOP_ANDI                            4 /* established */
#define REX3_LOGICOP_DST                             5 /* established */
#define REX3_LOGICOP_XOR                             6 /* established */
#define REX3_LOGICOP_OR                              7 /* established */
#define REX3_LOGICOP_NOR                             8 /* established */
#define REX3_LOGICOP_XNOR                            9 /* established */
#define REX3_LOGICOP_NDST                            10 /* established */
#define REX3_LOGICOP_ORR                             11 /* established */
#define REX3_LOGICOP_NSRC                            12 /* established */
#define REX3_LOGICOP_ORI                             13 /* established */
#define REX3_LOGICOP_NAND                            14 /* established */
#define REX3_LOGICOP_ONE                             15 /* established */

/* enum opcode: Primitive opcode, as both headers name it. */
#define REX3_OPCODE_NOOP                             0 /* established */
#define REX3_OPCODE_READ                             1 /* established */
#define REX3_OPCODE_DRAW                             2 /* established */
#define REX3_OPCODE_SCR2SCR                          3 /* established */

/* enum planes: Which plane group a draw writes, as named in the public headers.
 * NetBSD names value 1 both RGB and CI (colour index in the same plane group);
 * value 3 and 7 are not named by either header. */
#define REX3_PLANES_NONE                             0 /* established */
#define REX3_PLANES_RGB                              1 /* established */
#define REX3_PLANES_RGBA                             2 /* established */
#define REX3_PLANES_OLAY                             4 /* established */
#define REX3_PLANES_PUP                              5 /* established */
#define REX3_PLANES_CID                              6 /* established */

/* enum sfactor: Blend source factor, named as the headers name them (zero, one,
 * destination colour, its complement, source alpha, its complement). Values 6
 * and 7 are not named. */
#define REX3_SFACTOR_ZERO                            0 /* established */
#define REX3_SFACTOR_ONE                             1 /* established */
#define REX3_SFACTOR_DC                              2 /* established */
#define REX3_SFACTOR_MDC                             3 /* established */
#define REX3_SFACTOR_SA                              4 /* established */
#define REX3_SFACTOR_MSA                             5 /* established */

/*
 * Draw mode word 1: the plane group and depth a draw writes, the host-port
 * packing (RWPACKED, HOSTDEPTH, RWDOUBLE, SWAPENDIAN, written up in
 * devices/rex3/host-pixels.md), the compare, dither, blend and logic-operation
 * state. Every bit and value here is named at the same position in both headers
 * (two value names differ, noted on the enums); what a bit does is graded per
 * field, and only the host-port fields have a reading beyond the name.
 */
/* drawmode1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_DRAWMODE1 */
#define REX3_DRAWMODE1_OFFSET                        0x0u /* established */
#define REX3_DRAWMODE1_LOGICOP_SHIFT                 28 /* established */
#define REX3_DRAWMODE1_LOGICOP_MASK                  0xfu
#define REX3_DRAWMODE1_LOGICOP_INPLACE (REX3_DRAWMODE1_LOGICOP_MASK << REX3_DRAWMODE1_LOGICOP_SHIFT)
#define REX3_DRAWMODE1_BLENDALPHA_SHIFT              27 /* established */
#define REX3_DRAWMODE1_BLENDALPHA_MASK               0x1u
#define REX3_DRAWMODE1_BLENDALPHA_INPLACE (REX3_DRAWMODE1_BLENDALPHA_MASK << REX3_DRAWMODE1_BLENDALPHA_SHIFT)
#define REX3_DRAWMODE1_PREFETCH_SHIFT                26 /* established */
#define REX3_DRAWMODE1_PREFETCH_MASK                 0x1u
#define REX3_DRAWMODE1_PREFETCH_INPLACE (REX3_DRAWMODE1_PREFETCH_MASK << REX3_DRAWMODE1_PREFETCH_SHIFT)
#define REX3_DRAWMODE1_BACKBLEND_SHIFT               25 /* established */
#define REX3_DRAWMODE1_BACKBLEND_MASK                0x1u
#define REX3_DRAWMODE1_BACKBLEND_INPLACE (REX3_DRAWMODE1_BACKBLEND_MASK << REX3_DRAWMODE1_BACKBLEND_SHIFT)
#define REX3_DRAWMODE1_DFACTOR_SHIFT                 22 /* established */
#define REX3_DRAWMODE1_DFACTOR_MASK                  0x7u
#define REX3_DRAWMODE1_DFACTOR_INPLACE (REX3_DRAWMODE1_DFACTOR_MASK << REX3_DRAWMODE1_DFACTOR_SHIFT)
#define REX3_DRAWMODE1_SFACTOR_SHIFT                 19 /* established */
#define REX3_DRAWMODE1_SFACTOR_MASK                  0x7u
#define REX3_DRAWMODE1_SFACTOR_INPLACE (REX3_DRAWMODE1_SFACTOR_MASK << REX3_DRAWMODE1_SFACTOR_SHIFT)
#define REX3_DRAWMODE1_BLEND_SHIFT                   18 /* established */
#define REX3_DRAWMODE1_BLEND_MASK                    0x1u
#define REX3_DRAWMODE1_BLEND_INPLACE (REX3_DRAWMODE1_BLEND_MASK << REX3_DRAWMODE1_BLEND_SHIFT)
#define REX3_DRAWMODE1_FASTCLEAR_SHIFT               17 /* established */
#define REX3_DRAWMODE1_FASTCLEAR_MASK                0x1u
#define REX3_DRAWMODE1_FASTCLEAR_INPLACE (REX3_DRAWMODE1_FASTCLEAR_MASK << REX3_DRAWMODE1_FASTCLEAR_SHIFT)
#define REX3_DRAWMODE1_DITHER_SHIFT                  16 /* established */
#define REX3_DRAWMODE1_DITHER_MASK                   0x1u
#define REX3_DRAWMODE1_DITHER_INPLACE (REX3_DRAWMODE1_DITHER_MASK << REX3_DRAWMODE1_DITHER_SHIFT)
#define REX3_DRAWMODE1_RGBMODE_SHIFT                 15 /* established */
#define REX3_DRAWMODE1_RGBMODE_MASK                  0x1u
#define REX3_DRAWMODE1_RGBMODE_INPLACE (REX3_DRAWMODE1_RGBMODE_MASK << REX3_DRAWMODE1_RGBMODE_SHIFT)
#define REX3_DRAWMODE1_COMPARE_GT_SHIFT              14 /* established */
#define REX3_DRAWMODE1_COMPARE_GT_MASK               0x1u
#define REX3_DRAWMODE1_COMPARE_GT_INPLACE (REX3_DRAWMODE1_COMPARE_GT_MASK << REX3_DRAWMODE1_COMPARE_GT_SHIFT)
#define REX3_DRAWMODE1_COMPARE_EQ_SHIFT              13 /* established */
#define REX3_DRAWMODE1_COMPARE_EQ_MASK               0x1u
#define REX3_DRAWMODE1_COMPARE_EQ_INPLACE (REX3_DRAWMODE1_COMPARE_EQ_MASK << REX3_DRAWMODE1_COMPARE_EQ_SHIFT)
#define REX3_DRAWMODE1_COMPARE_LT_SHIFT              12 /* established */
#define REX3_DRAWMODE1_COMPARE_LT_MASK               0x1u
#define REX3_DRAWMODE1_COMPARE_LT_INPLACE (REX3_DRAWMODE1_COMPARE_LT_MASK << REX3_DRAWMODE1_COMPARE_LT_SHIFT)
#define REX3_DRAWMODE1_SWAPENDIAN_SHIFT              11 /* established */
#define REX3_DRAWMODE1_SWAPENDIAN_MASK               0x1u
#define REX3_DRAWMODE1_SWAPENDIAN_INPLACE (REX3_DRAWMODE1_SWAPENDIAN_MASK << REX3_DRAWMODE1_SWAPENDIAN_SHIFT)
#define REX3_DRAWMODE1_RWDOUBLE_SHIFT                10 /* established */
#define REX3_DRAWMODE1_RWDOUBLE_MASK                 0x1u
#define REX3_DRAWMODE1_RWDOUBLE_INPLACE (REX3_DRAWMODE1_RWDOUBLE_MASK << REX3_DRAWMODE1_RWDOUBLE_SHIFT)
#define REX3_DRAWMODE1_HOSTDEPTH_SHIFT               8 /* established */
#define REX3_DRAWMODE1_HOSTDEPTH_MASK                0x3u
#define REX3_DRAWMODE1_HOSTDEPTH_INPLACE (REX3_DRAWMODE1_HOSTDEPTH_MASK << REX3_DRAWMODE1_HOSTDEPTH_SHIFT)
#define REX3_DRAWMODE1_RWPACKED_SHIFT                7 /* established */
#define REX3_DRAWMODE1_RWPACKED_MASK                 0x1u
#define REX3_DRAWMODE1_RWPACKED_INPLACE (REX3_DRAWMODE1_RWPACKED_MASK << REX3_DRAWMODE1_RWPACKED_SHIFT)
#define REX3_DRAWMODE1_YFLIP_SHIFT                   6 /* inferred */
#define REX3_DRAWMODE1_YFLIP_MASK                    0x1u
#define REX3_DRAWMODE1_YFLIP_INPLACE (REX3_DRAWMODE1_YFLIP_MASK << REX3_DRAWMODE1_YFLIP_SHIFT)
#define REX3_DRAWMODE1_DBLSRC_SHIFT                  5 /* established */
#define REX3_DRAWMODE1_DBLSRC_MASK                   0x1u
#define REX3_DRAWMODE1_DBLSRC_INPLACE (REX3_DRAWMODE1_DBLSRC_MASK << REX3_DRAWMODE1_DBLSRC_SHIFT)
#define REX3_DRAWMODE1_DRAWDEPTH_SHIFT               3 /* established */
#define REX3_DRAWMODE1_DRAWDEPTH_MASK                0x3u
#define REX3_DRAWMODE1_DRAWDEPTH_INPLACE (REX3_DRAWMODE1_DRAWDEPTH_MASK << REX3_DRAWMODE1_DRAWDEPTH_SHIFT)
#define REX3_DRAWMODE1_PLANES_SHIFT                  0 /* established */
#define REX3_DRAWMODE1_PLANES_MASK                   0x7u
#define REX3_DRAWMODE1_PLANES_INPLACE (REX3_DRAWMODE1_PLANES_MASK << REX3_DRAWMODE1_PLANES_SHIFT)

/*
 * Draw mode word 0, the command register: the opcode, the addressing mode and
 * the per-primitive option bits. NetBSD's console code draws with opcode draw
 * in block mode and copies with scr2scr; the host-pixel paths are in
 * devices/rex3/host-pixels.md. Bit positions and names are the same in both
 * headers, except that only Linux names addressing modes 5 and 6. What each
 * option bit does is not read beyond its name, except where the field says
 * otherwise.
 */
/* drawmode0: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_DRAWMODE0 */
#define REX3_DRAWMODE0_OFFSET                        0x4u /* established */
#define REX3_DRAWMODE0_YSTRIDE_SHIFT                 23 /* established */
#define REX3_DRAWMODE0_YSTRIDE_MASK                  0x1u
#define REX3_DRAWMODE0_YSTRIDE_INPLACE (REX3_DRAWMODE0_YSTRIDE_MASK << REX3_DRAWMODE0_YSTRIDE_SHIFT)
#define REX3_DRAWMODE0_ENDPTFILTER_SHIFT             22 /* established */
#define REX3_DRAWMODE0_ENDPTFILTER_MASK              0x1u
#define REX3_DRAWMODE0_ENDPTFILTER_INPLACE (REX3_DRAWMODE0_ENDPTFILTER_MASK << REX3_DRAWMODE0_ENDPTFILTER_SHIFT)
#define REX3_DRAWMODE0_CICLAMP_SHIFT                 21 /* established */
#define REX3_DRAWMODE0_CICLAMP_MASK                  0x1u
#define REX3_DRAWMODE0_CICLAMP_INPLACE (REX3_DRAWMODE0_CICLAMP_MASK << REX3_DRAWMODE0_CICLAMP_SHIFT)
#define REX3_DRAWMODE0_XYOFFSET_SHIFT                20 /* established */
#define REX3_DRAWMODE0_XYOFFSET_MASK                 0x1u
#define REX3_DRAWMODE0_XYOFFSET_INPLACE (REX3_DRAWMODE0_XYOFFSET_MASK << REX3_DRAWMODE0_XYOFFSET_SHIFT)
#define REX3_DRAWMODE0_LRONLY_SHIFT                  19 /* established */
#define REX3_DRAWMODE0_LRONLY_MASK                   0x1u
#define REX3_DRAWMODE0_LRONLY_INPLACE (REX3_DRAWMODE0_LRONLY_MASK << REX3_DRAWMODE0_LRONLY_SHIFT)
#define REX3_DRAWMODE0_SHADE_SHIFT                   18 /* established */
#define REX3_DRAWMODE0_SHADE_MASK                    0x1u
#define REX3_DRAWMODE0_SHADE_INPLACE (REX3_DRAWMODE0_SHADE_MASK << REX3_DRAWMODE0_SHADE_SHIFT)
#define REX3_DRAWMODE0_LSOPAQUE_SHIFT                17 /* inferred */
#define REX3_DRAWMODE0_LSOPAQUE_MASK                 0x1u
#define REX3_DRAWMODE0_LSOPAQUE_INPLACE (REX3_DRAWMODE0_LSOPAQUE_MASK << REX3_DRAWMODE0_LSOPAQUE_SHIFT)
#define REX3_DRAWMODE0_ZPOPAQUE_SHIFT                16 /* inferred */
#define REX3_DRAWMODE0_ZPOPAQUE_MASK                 0x1u
#define REX3_DRAWMODE0_ZPOPAQUE_INPLACE (REX3_DRAWMODE0_ZPOPAQUE_MASK << REX3_DRAWMODE0_ZPOPAQUE_SHIFT)
#define REX3_DRAWMODE0_LENGTH32_SHIFT                15 /* established */
#define REX3_DRAWMODE0_LENGTH32_MASK                 0x1u
#define REX3_DRAWMODE0_LENGTH32_INPLACE (REX3_DRAWMODE0_LENGTH32_MASK << REX3_DRAWMODE0_LENGTH32_SHIFT)
#define REX3_DRAWMODE0_LSADVLAST_SHIFT               14 /* established */
#define REX3_DRAWMODE0_LSADVLAST_MASK                0x1u
#define REX3_DRAWMODE0_LSADVLAST_INPLACE (REX3_DRAWMODE0_LSADVLAST_MASK << REX3_DRAWMODE0_LSADVLAST_SHIFT)
#define REX3_DRAWMODE0_ENLSPATTERN_SHIFT             13 /* established */
#define REX3_DRAWMODE0_ENLSPATTERN_MASK              0x1u
#define REX3_DRAWMODE0_ENLSPATTERN_INPLACE (REX3_DRAWMODE0_ENLSPATTERN_MASK << REX3_DRAWMODE0_ENLSPATTERN_SHIFT)
#define REX3_DRAWMODE0_ENZPATTERN_SHIFT              12 /* established */
#define REX3_DRAWMODE0_ENZPATTERN_MASK               0x1u
#define REX3_DRAWMODE0_ENZPATTERN_INPLACE (REX3_DRAWMODE0_ENZPATTERN_MASK << REX3_DRAWMODE0_ENZPATTERN_SHIFT)
#define REX3_DRAWMODE0_SKIPLAST_SHIFT                11 /* established */
#define REX3_DRAWMODE0_SKIPLAST_MASK                 0x1u
#define REX3_DRAWMODE0_SKIPLAST_INPLACE (REX3_DRAWMODE0_SKIPLAST_MASK << REX3_DRAWMODE0_SKIPLAST_SHIFT)
#define REX3_DRAWMODE0_SKIPFIRST_SHIFT               10 /* established */
#define REX3_DRAWMODE0_SKIPFIRST_MASK                0x1u
#define REX3_DRAWMODE0_SKIPFIRST_INPLACE (REX3_DRAWMODE0_SKIPFIRST_MASK << REX3_DRAWMODE0_SKIPFIRST_SHIFT)
#define REX3_DRAWMODE0_STOPONY_SHIFT                 9 /* established */
#define REX3_DRAWMODE0_STOPONY_MASK                  0x1u
#define REX3_DRAWMODE0_STOPONY_INPLACE (REX3_DRAWMODE0_STOPONY_MASK << REX3_DRAWMODE0_STOPONY_SHIFT)
#define REX3_DRAWMODE0_STOPONX_SHIFT                 8 /* established */
#define REX3_DRAWMODE0_STOPONX_MASK                  0x1u
#define REX3_DRAWMODE0_STOPONX_INPLACE (REX3_DRAWMODE0_STOPONX_MASK << REX3_DRAWMODE0_STOPONX_SHIFT)
#define REX3_DRAWMODE0_ALPHAHOST_SHIFT               7 /* established */
#define REX3_DRAWMODE0_ALPHAHOST_MASK                0x1u
#define REX3_DRAWMODE0_ALPHAHOST_INPLACE (REX3_DRAWMODE0_ALPHAHOST_MASK << REX3_DRAWMODE0_ALPHAHOST_SHIFT)
#define REX3_DRAWMODE0_COLORHOST_SHIFT               6 /* established */
#define REX3_DRAWMODE0_COLORHOST_MASK                0x1u
#define REX3_DRAWMODE0_COLORHOST_INPLACE (REX3_DRAWMODE0_COLORHOST_MASK << REX3_DRAWMODE0_COLORHOST_SHIFT)
#define REX3_DRAWMODE0_DOSETUP_SHIFT                 5 /* established */
#define REX3_DRAWMODE0_DOSETUP_MASK                  0x1u
#define REX3_DRAWMODE0_DOSETUP_INPLACE (REX3_DRAWMODE0_DOSETUP_MASK << REX3_DRAWMODE0_DOSETUP_SHIFT)
#define REX3_DRAWMODE0_ADRMODE_SHIFT                 2 /* established */
#define REX3_DRAWMODE0_ADRMODE_MASK                  0x7u
#define REX3_DRAWMODE0_ADRMODE_INPLACE (REX3_DRAWMODE0_ADRMODE_MASK << REX3_DRAWMODE0_ADRMODE_SHIFT)
#define REX3_DRAWMODE0_OPCODE_SHIFT                  0 /* established */
#define REX3_DRAWMODE0_OPCODE_MASK                   0x3u
#define REX3_DRAWMODE0_OPCODE_INPLACE (REX3_DRAWMODE0_OPCODE_MASK << REX3_DRAWMODE0_OPCODE_SHIFT)

/*
 * Line-stipple mode word. Its field layout is in neither header, so none is
 * given here.
 */
/* lsmode: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_LSMODE */
#define REX3_LSMODE_OFFSET                           0x8u /* established */

/*
 * Line-stipple pattern word.
 */
/* lspattern: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_LSPATTERN */
#define REX3_LSPATTERN_OFFSET                        0xcu /* established */

/*
 * Backup copy of the stipple pattern, named save by Linux's comment (a backup
 * of the pattern).
 */
/* lspatsave: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_LSPATSAVE */
#define REX3_LSPATSAVE_OFFSET                        0x10u /* established */

/*
 * Per-pixel pattern word; NetBSD's glyph path writes it at the GO alias once
 * per row, with the row's glyph bits.
 */
/* zpattern: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_ZPATTERN */
#define REX3_ZPATTERN_OFFSET                         0x14u /* established */

/*
 * Background colour. NetBSD stores the glyph background colour index here.
 */
/* colorback: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_COLORBACK */
#define REX3_COLORBACK_OFFSET                        0x18u /* established */

/*
 * Clear colour for the fast VRAM clear (Linux comment); NetBSD's rectangle fill
 * writes the colour here with FASTCLEAR set.
 */
/* colorvram: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_COLORVRAM */
#define REX3_COLORVRAM_OFFSET                        0x1cu /* established */

/*
 * Reference alpha value for the alpha-function compare (Linux comment).
 */
/* alpharef: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_ALPHAREF */
#define REX3_ALPHAREF_OFFSET                         0x20u /* established */

/*
 * NetBSD names this word a stall register and its comment says a write waits
 * until the engine is idle. Linux declares only a pad here. Role inferred from
 * NetBSD's name and comment; neither driver writes it.
 */
/* stall0: rw32, reset unknown; NetBSD sgimips Newport register header
 * REX3_REG_STALL0; Linux Newport framebuffer header leaves the word undeclared
 */
#define REX3_STALL0_OFFSET                           0x24u /* inferred */

/*
 * Screen mask 0, x extent: a minimum and a maximum packed in one word (NetBSD's
 * comment says min and max, 16.16). Which half is which is not read.
 */
/* smask0x: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK0X */
#define REX3_SMASK0X_OFFSET                          0x28u /* established */

/*
 * Screen mask 0, y extent, packed as SMASK0X.
 */
/* smask0y: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK0Y */
#define REX3_SMASK0Y_OFFSET                          0x2cu /* established */

/*
 * Setup trigger. Both headers declare it; neither drives it in the console
 * paths read. Linux names it with a leading underscore.
 */
/* setup: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SETUP */
#define REX3_SETUP_OFFSET                            0x30u /* established */

/*
 * Linux declares a word here named stepz. Single source; role unknown beyond
 * the name.
 */
/* stepz: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member _stepz */
#define REX3_STEPZ_OFFSET                            0x34u /* inferred */

/*
 * Linux declares it, next to LSPATSAVE; the name reads as restoring the stipple
 * state. Single source; role inferred from the name only.
 */
/* lsrestore: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member _lsrestore */
#define REX3_LSRESTORE_OFFSET                        0x38u /* inferred */

/*
 * Linux declares it next to LSRESTORE; the name reads as saving the stipple
 * state. Single source; role inferred from the name only.
 */
/* lssave: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member _lssave */
#define REX3_LSSAVE_OFFSET                           0x3cu /* inferred */

/*
 * Current x start of the primitive, integer and fraction combined. NetBSD's
 * board probe writes 0x12345678 to XSTARTI and expects this register to read
 * the low 16 bits of that shifted left by PROBE_XSTART_SHIFT. A qtest can
 * discriminate: write 0x12345678 to XSTARTI and expect 0x02b3c000 from XSTART.
 */
/* xstart: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_XSTART, member _xstart; NetBSD sgimips Newport driver board probe */
#define REX3_XSTART_OFFSET                           0x100u /* established */

/*
 * Current y start, counterpart of XSTART. Single source (the name pairs it with
 * XSTART).
 */
/* ystart: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member _ystart */
#define REX3_YSTART_OFFSET                           0x104u /* inferred */

/*
 * Current x end point. Single source.
 */
/* xend: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member _xend */
#define REX3_XEND_OFFSET                             0x108u /* inferred */

/*
 * Current y end point. Single source.
 */
/* yend: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member _yend */
#define REX3_YEND_OFFSET                             0x10cu /* inferred */

/*
 * Copy of the integer x start for block addressing, from the Linux comment (a
 * copy of xstart for block mode). Single source.
 */
/* xsave: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member xsave */
#define REX3_XSAVE_OFFSET                            0x110u /* inferred */

/*
 * Signed x and y offset applied for relative operations such as a screen copy
 * (Linux comment: an offset from xstart, ystart). NetBSD packs x in bits 31:16
 * and y in bits 15:0 and, for a copy, stores the destination minus the source.
 */
/* xymove: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_XYMOVE */
#define REX3_XYMOVE_OFFSET                           0x114u /* established */
#define REX3_XYMOVE_X_SHIFT                          16 /* established */
#define REX3_XYMOVE_X_MASK                           0xffffu
#define REX3_XYMOVE_X_INPLACE (REX3_XYMOVE_X_MASK << REX3_XYMOVE_X_SHIFT)
#define REX3_XYMOVE_Y_SHIFT                          0 /* inferred */
#define REX3_XYMOVE_Y_MASK                           0xffffu
#define REX3_XYMOVE_Y_INPLACE (REX3_XYMOVE_Y_MASK << REX3_XYMOVE_Y_SHIFT)

/*
 * Bresenham line decision term (name only). Single source.
 */
/* bresd: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member bresd */
#define REX3_BRESD_OFFSET                            0x118u /* inferred */

/*
 * Bresenham line term S1 (name only). Single source.
 */
/* bress1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member bress1 */
#define REX3_BRESS1_OFFSET                           0x11cu /* inferred */

/*
 * Bresenham octant and first increment. The host-pixel image put clears it
 * before storing pixel words (devices/rex3/host-pixels.md).
 */
/* bresoctinc1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member bresoctinc1; the offset also matches the host-pixel
 * reading in devices/rex3/host-pixels.md */
#define REX3_BRESOCTINC1_OFFSET                      0x120u /* established */

/*
 * Bresenham rounding mode and second increment (name only). Single source.
 */
/* bresrndinc2: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member bresrndinc2 */
#define REX3_BRESRNDINC2_OFFSET                      0x124u /* inferred */

/*
 * Bresenham error term E1 (name only). Single source.
 */
/* brese1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member brese1 */
#define REX3_BRESE1_OFFSET                           0x128u /* inferred */

/*
 * Bresenham term S2 (name only). Single source.
 */
/* bress2: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member bress2 */
#define REX3_BRESS2_OFFSET                           0x12cu /* inferred */

/*
 * Anti-aliased line weight table entry (name only). Single source.
 */
/* aweight0: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member aweight0 */
#define REX3_AWEIGHT0_OFFSET                         0x130u /* inferred */

/*
 * Anti-aliased line weight table entry (name only). Single source.
 */
/* aweight1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member aweight1 */
#define REX3_AWEIGHT1_OFFSET                         0x134u /* inferred */

/*
 * Start x as a float-format value (Linux types it as a float or word union).
 * Single source.
 */
/* xstartf: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member xstartf */
#define REX3_XSTARTF_OFFSET                          0x138u /* inferred */

/*
 * Start y, same layout as XSTARTF. Single source.
 */
/* ystartf: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member ystartf */
#define REX3_YSTARTF_OFFSET                          0x13cu /* inferred */

/*
 * End x, same layout as XSTARTF. Single source.
 */
/* xendf: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member xendf */
#define REX3_XENDF_OFFSET                            0x140u /* inferred */

/*
 * End y, same layout as XSTARTF. Single source.
 */
/* yendf: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member yendf */
#define REX3_YENDF_OFFSET                            0x144u /* inferred */

/*
 * Start x as an integer. NetBSD's board probe writes 0x12345678 here and reads
 * XSTART; see that register.
 */
/* xstarti: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_XSTARTI; NetBSD sgimips Newport driver board probe */
#define REX3_XSTARTI_OFFSET                          0x148u /* established */

/*
 * A second end-x word Linux declares (named xendf1). Single source; MAME's
 * model reads this offset as a copy of the XENDF word, which is a model, not
 * evidence.
 */
/* xendf1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member xendf1 */
#define REX3_XENDF1_OFFSET                           0x14cu /* inferred */

/*
 * Start x and y as one packed integer word: x in bits 31:16, y in bits 15:0
 * (NetBSD packs x << 16 | y; devices/rex3/host-pixels.md records the image put
 * writing it this way).
 */
/* xystarti: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_XYSTARTI */
#define REX3_XYSTARTI_OFFSET                         0x150u /* established */
#define REX3_XYSTARTI_X_SHIFT                        16 /* established */
#define REX3_XYSTARTI_X_MASK                         0xffffu
#define REX3_XYSTARTI_X_INPLACE (REX3_XYSTARTI_X_MASK << REX3_XYSTARTI_X_SHIFT)
#define REX3_XYSTARTI_Y_SHIFT                        0 /* established */
#define REX3_XYSTARTI_Y_MASK                         0xffffu
#define REX3_XYSTARTI_Y_INPLACE (REX3_XYSTARTI_Y_MASK << REX3_XYSTARTI_Y_SHIFT)

/*
 * End x and y as one packed integer word, packed as XYSTARTI.
 */
/* xyendi: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_XYENDI */
#define REX3_XYENDI_OFFSET                           0x154u /* established */
#define REX3_XYENDI_X_SHIFT                          16 /* established */
#define REX3_XYENDI_X_MASK                           0xffffu
#define REX3_XYENDI_X_INPLACE (REX3_XYENDI_X_MASK << REX3_XYENDI_X_SHIFT)
#define REX3_XYENDI_Y_SHIFT                          0 /* established */
#define REX3_XYENDI_Y_MASK                           0xffffu
#define REX3_XYENDI_Y_INPLACE (REX3_XYENDI_Y_MASK << REX3_XYENDI_Y_SHIFT)

/*
 * Start and end x as integers in one word (name only). Single source.
 */
/* xstartendi: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member xstartendi */
#define REX3_XSTARTENDI_OFFSET                       0x158u /* inferred */

/*
 * Red (or colour-index) colour, full state. Named and placed by Linux alone,
 * whose comment calls the group iterators with full state for a context switch.
 * Single source; the shading arithmetic is not read.
 */
/* colorred: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member colorred */
#define REX3_COLORRED_OFFSET                         0x200u /* inferred */

/*
 * Alpha colour, full state. Named and placed by Linux alone, whose comment
 * calls the group iterators with full state for a context switch. Single
 * source; the shading arithmetic is not read.
 */
/* coloralpha: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member coloralpha */
#define REX3_COLORALPHA_OFFSET                       0x204u /* inferred */

/*
 * Green colour, full state. Named and placed by Linux alone, whose comment
 * calls the group iterators with full state for a context switch. Single
 * source; the shading arithmetic is not read.
 */
/* colorgrn: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member colorgrn */
#define REX3_COLORGRN_OFFSET                         0x208u /* inferred */

/*
 * Blue colour, full state. Named and placed by Linux alone, whose comment calls
 * the group iterators with full state for a context switch. Single source; the
 * shading arithmetic is not read.
 */
/* colorblue: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member colorblue */
#define REX3_COLORBLUE_OFFSET                        0x20cu /* inferred */

/*
 * Red (or colour-index) slope per pixel. Named and placed by Linux alone, whose
 * comment calls the group iterators with full state for a context switch.
 * Single source; the shading arithmetic is not read.
 */
/* slopered: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member slopered */
#define REX3_SLOPERED_OFFSET                         0x210u /* inferred */

/*
 * Alpha slope per pixel. Named and placed by Linux alone, whose comment calls
 * the group iterators with full state for a context switch. Single source; the
 * shading arithmetic is not read.
 */
/* slopealpha: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member slopealpha */
#define REX3_SLOPEALPHA_OFFSET                       0x214u /* inferred */

/*
 * Green slope per pixel. Named and placed by Linux alone, whose comment calls
 * the group iterators with full state for a context switch. Single source; the
 * shading arithmetic is not read.
 */
/* slopegrn: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member slopegrn */
#define REX3_SLOPEGRN_OFFSET                         0x218u /* inferred */

/*
 * Blue slope per pixel. Named and placed by Linux alone, whose comment calls
 * the group iterators with full state for a context switch. Single source; the
 * shading arithmetic is not read.
 */
/* slopeblue: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member slopeblue */
#define REX3_SLOPEBLUE_OFFSET                        0x21cu /* inferred */

/*
 * Plane write mask. NetBSD stores 0xffffffff for a fill and 0xff when drawing
 * 8-bit glyphs.
 */
/* wrmask: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_WRMASK */
#define REX3_WRMASK_OFFSET                           0x220u /* established */

/*
 * Packed integer colour. NetBSD stores the glyph foreground colour index here.
 */
/* colori: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_COLORI */
#define REX3_COLORI_OFFSET                           0x224u /* established */

/*
 * Linux declares a colour word here named colorx. Single source; role unknown
 * beyond the name.
 */
/* colorx: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member colorx */
#define REX3_COLORX_OFFSET                           0x228u /* inferred */

/*
 * Linux declares a second red slope word here. Single source; role unknown
 * beyond the name.
 */
/* slopered1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member slopered1 */
#define REX3_SLOPERED1_OFFSET                        0x22cu /* inferred */

/*
 * Host data port, most significant word (devices/rex3/host-pixels.md for the
 * packing at each depth and the GO alias used for pixel stores).
 */
/* hostrw0: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_HOSTRW0 */
#define REX3_HOSTRW0_OFFSET                          0x230u /* established */

/*
 * Host data port, least significant word; used only for 64-bit transfers
 * (devices/rex3/host-pixels.md).
 */
/* hostrw1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_HOSTRW1 */
#define REX3_HOSTRW1_OFFSET                          0x234u /* established */

/*
 * Display control bus mode: the data width, the slave address and register
 * select, the acknowledge type and the chip-select timing for the next DCBDATA
 * transfer. The two headers define the same bit positions and names.
 * devices/rex3/byte-lanes.md records how the data bytes travel.
 */
/* dcbmode: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_DCBMODE */
#define REX3_DCBMODE_OFFSET                          0x238u /* established */
#define REX3_DCBMODE_SWAPENDIAN_SHIFT                28 /* established */
#define REX3_DCBMODE_SWAPENDIAN_MASK                 0x1u
#define REX3_DCBMODE_SWAPENDIAN_INPLACE (REX3_DCBMODE_SWAPENDIAN_MASK << REX3_DCBMODE_SWAPENDIAN_SHIFT)
#define REX3_DCBMODE_CSSETUP_SHIFT                   23 /* established */
#define REX3_DCBMODE_CSSETUP_MASK                    0x1fu
#define REX3_DCBMODE_CSSETUP_INPLACE (REX3_DCBMODE_CSSETUP_MASK << REX3_DCBMODE_CSSETUP_SHIFT)
#define REX3_DCBMODE_CSHOLD_SHIFT                    18 /* established */
#define REX3_DCBMODE_CSHOLD_MASK                     0x1fu
#define REX3_DCBMODE_CSHOLD_INPLACE (REX3_DCBMODE_CSHOLD_MASK << REX3_DCBMODE_CSHOLD_SHIFT)
#define REX3_DCBMODE_CSWIDTH_SHIFT                   13 /* established */
#define REX3_DCBMODE_CSWIDTH_MASK                    0x1fu
#define REX3_DCBMODE_CSWIDTH_INPLACE (REX3_DCBMODE_CSWIDTH_MASK << REX3_DCBMODE_CSWIDTH_SHIFT)
#define REX3_DCBMODE_ENASYNCACK_SHIFT                12 /* established */
#define REX3_DCBMODE_ENASYNCACK_MASK                 0x1u
#define REX3_DCBMODE_ENASYNCACK_INPLACE (REX3_DCBMODE_ENASYNCACK_MASK << REX3_DCBMODE_ENASYNCACK_SHIFT)
#define REX3_DCBMODE_ENSYNCACK_SHIFT                 11 /* established */
#define REX3_DCBMODE_ENSYNCACK_MASK                  0x1u
#define REX3_DCBMODE_ENSYNCACK_INPLACE (REX3_DCBMODE_ENSYNCACK_MASK << REX3_DCBMODE_ENSYNCACK_SHIFT)
#define REX3_DCBMODE_DCBADDR_SHIFT                   7 /* established */
#define REX3_DCBMODE_DCBADDR_MASK                    0xfu
#define REX3_DCBMODE_DCBADDR_INPLACE (REX3_DCBMODE_DCBADDR_MASK << REX3_DCBMODE_DCBADDR_SHIFT)
#define REX3_DCBMODE_DCBCRS_SHIFT                    4 /* established */
#define REX3_DCBMODE_DCBCRS_MASK                     0x7u
#define REX3_DCBMODE_DCBCRS_INPLACE (REX3_DCBMODE_DCBCRS_MASK << REX3_DCBMODE_DCBCRS_SHIFT)
#define REX3_DCBMODE_ENCRSINC_SHIFT                  3 /* established */
#define REX3_DCBMODE_ENCRSINC_MASK                   0x1u
#define REX3_DCBMODE_ENCRSINC_INPLACE (REX3_DCBMODE_ENCRSINC_MASK << REX3_DCBMODE_ENCRSINC_SHIFT)
#define REX3_DCBMODE_ENDATAPACK_SHIFT                2 /* established */
#define REX3_DCBMODE_ENDATAPACK_MASK                 0x1u
#define REX3_DCBMODE_ENDATAPACK_INPLACE (REX3_DCBMODE_ENDATAPACK_MASK << REX3_DCBMODE_ENDATAPACK_SHIFT)
#define REX3_DCBMODE_DATAWIDTH_SHIFT                 0 /* established */
#define REX3_DCBMODE_DATAWIDTH_MASK                  0x3u
#define REX3_DCBMODE_DATAWIDTH_INPLACE (REX3_DCBMODE_DATAWIDTH_MASK << REX3_DCBMODE_DATAWIDTH_SHIFT)

/*
 * Display bus data, most significant word. Linux accesses it as a word, as
 * halfword 1 at +2 and as byte 3 at +3 depending on DATAWIDTH; NetBSD packs the
 * first byte in bits 31:24 (devices/rex3/byte-lanes.md).
 */
/* dcbdata0: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_DCBDATA0 */
#define REX3_DCBDATA0_OFFSET                         0x240u /* established */

/*
 * Display bus data, least significant word.
 */
/* dcbdata1: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_DCBDATA1 */
#define REX3_DCBDATA1_OFFSET                         0x244u /* established */

/*
 * Screen mask 1 x extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask1x: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK1X */
#define REX3_SMASK1X_OFFSET                          0x1300u /* established */

/*
 * Screen mask 1 y extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask1y: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK1Y */
#define REX3_SMASK1Y_OFFSET                          0x1304u /* established */

/*
 * Screen mask 2 x extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask2x: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK2X */
#define REX3_SMASK2X_OFFSET                          0x1308u /* established */

/*
 * Screen mask 2 y extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask2y: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK2Y */
#define REX3_SMASK2Y_OFFSET                          0x130cu /* established */

/*
 * Screen mask 3 x extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask3x: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK3X */
#define REX3_SMASK3X_OFFSET                          0x1310u /* established */

/*
 * Screen mask 3 y extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask3y: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK3Y */
#define REX3_SMASK3Y_OFFSET                          0x1314u /* established */

/*
 * Screen mask 4 x extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask4x: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK4X */
#define REX3_SMASK4X_OFFSET                          0x1318u /* established */

/*
 * Screen mask 4 y extent, a minimum and a maximum packed in one word (NetBSD's
 * comment: min and max, 16.16). Enabled through CLIPMODE.
 */
/* smask4y: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_SMASK4Y */
#define REX3_SMASK4Y_OFFSET                          0x131cu /* established */

/*
 * Top-of-screen scanline. NetBSD's console init stores 0x3ff here with a
 * comment that it does not know why; the meaning is read from the name only.
 */
/* topscan: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_TOPSCAN; NetBSD sgimips Newport driver writes 0x3ff */
#define REX3_TOPSCAN_OFFSET                          0x1320u /* established */

/*
 * Window origin offset, x in bits 31:16 and y in bits 15:0 (inferred from
 * NetBSD's console init, which stores 4096 in both halves). Linux declares it
 * unnamed in role.
 */
/* xywin: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_XYWIN; NetBSD sgimips Newport driver writes (4096 << 16) | 4096 */
#define REX3_XYWIN_OFFSET                            0x1324u /* established */
#define REX3_XYWIN_X_SHIFT                           16 /* inferred */
#define REX3_XYWIN_X_MASK                            0xffffu
#define REX3_XYWIN_X_INPLACE (REX3_XYWIN_X_MASK << REX3_XYWIN_X_SHIFT)
#define REX3_XYWIN_Y_SHIFT                           0 /* inferred */
#define REX3_XYWIN_Y_MASK                            0xffffu
#define REX3_XYWIN_Y_INPLACE (REX3_XYWIN_Y_MASK << REX3_XYWIN_Y_SHIFT)

/*
 * Clipping mode: one enable per screen mask (0 to 4) in bits 4:0 and four
 * window-id match enables in bits 12:9. NetBSD stores a value at init that sets
 * exactly the four match enables. Bits 8:5 are unnamed in both headers.
 */
/* clipmode: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* */
#define REX3_CLIPMODE_OFFSET                         0x1328u /* established */
#define REX3_CLIPMODE_CIDMATCH3_SHIFT                12 /* established */
#define REX3_CLIPMODE_CIDMATCH3_MASK                 0x1u
#define REX3_CLIPMODE_CIDMATCH3_INPLACE (REX3_CLIPMODE_CIDMATCH3_MASK << REX3_CLIPMODE_CIDMATCH3_SHIFT)
#define REX3_CLIPMODE_CIDMATCH2_SHIFT                11 /* established */
#define REX3_CLIPMODE_CIDMATCH2_MASK                 0x1u
#define REX3_CLIPMODE_CIDMATCH2_INPLACE (REX3_CLIPMODE_CIDMATCH2_MASK << REX3_CLIPMODE_CIDMATCH2_SHIFT)
#define REX3_CLIPMODE_CIDMATCH1_SHIFT                10 /* established */
#define REX3_CLIPMODE_CIDMATCH1_MASK                 0x1u
#define REX3_CLIPMODE_CIDMATCH1_INPLACE (REX3_CLIPMODE_CIDMATCH1_MASK << REX3_CLIPMODE_CIDMATCH1_SHIFT)
#define REX3_CLIPMODE_CIDMATCH0_SHIFT                9 /* established */
#define REX3_CLIPMODE_CIDMATCH0_MASK                 0x1u
#define REX3_CLIPMODE_CIDMATCH0_INPLACE (REX3_CLIPMODE_CIDMATCH0_MASK << REX3_CLIPMODE_CIDMATCH0_SHIFT)
#define REX3_CLIPMODE_SMASK4_SHIFT                   4 /* established */
#define REX3_CLIPMODE_SMASK4_MASK                    0x1u
#define REX3_CLIPMODE_SMASK4_INPLACE (REX3_CLIPMODE_SMASK4_MASK << REX3_CLIPMODE_SMASK4_SHIFT)
#define REX3_CLIPMODE_SMASK3_SHIFT                   3 /* established */
#define REX3_CLIPMODE_SMASK3_MASK                    0x1u
#define REX3_CLIPMODE_SMASK3_INPLACE (REX3_CLIPMODE_SMASK3_MASK << REX3_CLIPMODE_SMASK3_SHIFT)
#define REX3_CLIPMODE_SMASK2_SHIFT                   2 /* established */
#define REX3_CLIPMODE_SMASK2_MASK                    0x1u
#define REX3_CLIPMODE_SMASK2_INPLACE (REX3_CLIPMODE_SMASK2_MASK << REX3_CLIPMODE_SMASK2_SHIFT)
#define REX3_CLIPMODE_SMASK1_SHIFT                   1 /* established */
#define REX3_CLIPMODE_SMASK1_MASK                    0x1u
#define REX3_CLIPMODE_SMASK1_INPLACE (REX3_CLIPMODE_SMASK1_MASK << REX3_CLIPMODE_SMASK1_SHIFT)
#define REX3_CLIPMODE_SMASK0_SHIFT                   0 /* established */
#define REX3_CLIPMODE_SMASK0_MASK                    0x1u
#define REX3_CLIPMODE_SMASK0_INPLACE (REX3_CLIPMODE_SMASK0_MASK << REX3_CLIPMODE_SMASK0_SHIFT)

/*
 * NetBSD names this word a stall register, matching STALL0. Role inferred from
 * the name; neither driver writes it.
 */
/* stall1: rw32, reset unknown; NetBSD sgimips Newport register header
 * REX3_REG_STALL1; Linux Newport framebuffer header leaves the word undeclared
 */
#define REX3_STALL1_OFFSET                           0x132cu /* inferred */

/*
 * Configuration register. NetBSD names the offset; the bit groups are Linux's
 * alone, and no reading of any of them exists, so every field is inferred as a
 * position only and its role is unknown. The register grade is inferred for the
 * same reason.
 */
/* config: rw32, reset unknown; NetBSD sgimips Newport register header
 * REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct
 * newport_cregs and NPORT_CFG_* (bit layout) */
#define REX3_CONFIG_OFFSET                           0x1330u /* inferred */
#define REX3_CONFIG_FBTYP_SHIFT                      20 /* inferred */
#define REX3_CONFIG_FBTYP_MASK                       0x1u
#define REX3_CONFIG_FBTYP_INPLACE (REX3_CONFIG_FBTYP_MASK << REX3_CONFIG_FBTYP_SHIFT)
#define REX3_CONFIG_VR_SHIFT                         17 /* inferred */
#define REX3_CONFIG_VR_MASK                          0x7u
#define REX3_CONFIG_VR_INPLACE (REX3_CONFIG_VR_MASK << REX3_CONFIG_VR_SHIFT)
#define REX3_CONFIG_TO_SHIFT                         14 /* inferred */
#define REX3_CONFIG_TO_MASK                          0x7u
#define REX3_CONFIG_TO_INPLACE (REX3_CONFIG_TO_MASK << REX3_CONFIG_TO_SHIFT)
#define REX3_CONFIG_GFAINT_SHIFT                     13 /* inferred */
#define REX3_CONFIG_GFAINT_MASK                      0x1u
#define REX3_CONFIG_GFAINT_INPLACE (REX3_CONFIG_GFAINT_MASK << REX3_CONFIG_GFAINT_SHIFT)
#define REX3_CONFIG_GD_SHIFT                         8 /* inferred */
#define REX3_CONFIG_GD_MASK                          0x1fu
#define REX3_CONFIG_GD_INPLACE (REX3_CONFIG_GD_MASK << REX3_CONFIG_GD_SHIFT)
#define REX3_CONFIG_BFAINT_SHIFT                     7 /* inferred */
#define REX3_CONFIG_BFAINT_MASK                      0x1u
#define REX3_CONFIG_BFAINT_INPLACE (REX3_CONFIG_BFAINT_MASK << REX3_CONFIG_BFAINT_SHIFT)
#define REX3_CONFIG_BD_SHIFT                         3 /* inferred */
#define REX3_CONFIG_BD_MASK                          0xfu
#define REX3_CONFIG_BD_INPLACE (REX3_CONFIG_BD_MASK << REX3_CONFIG_BD_SHIFT)
#define REX3_CONFIG_ERCVR_SHIFT                      2 /* inferred */
#define REX3_CONFIG_ERCVR_MASK                       0x1u
#define REX3_CONFIG_ERCVR_INPLACE (REX3_CONFIG_ERCVR_MASK << REX3_CONFIG_ERCVR_SHIFT)
#define REX3_CONFIG_BWIDTH_SHIFT                     1 /* inferred */
#define REX3_CONFIG_BWIDTH_MASK                      0x1u
#define REX3_CONFIG_BWIDTH_INPLACE (REX3_CONFIG_BWIDTH_MASK << REX3_CONFIG_BWIDTH_SHIFT)
#define REX3_CONFIG_G32MD_SHIFT                      0 /* inferred */
#define REX3_CONFIG_G32MD_MASK                       0x1u
#define REX3_CONFIG_G32MD_INPLACE (REX3_CONFIG_G32MD_MASK << REX3_CONFIG_G32MD_SHIFT)

/*
 * Status. Drivers only read it, polling the busy bits and the FIFO levels
 * before sending more work. NetBSD and Linux agree on the busy bits and on the
 * graphics FIFO level mask; they differ by one bit on the back-end FIFO level.
 */
/* status: r32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header
 * REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* */
#define REX3_STATUS_OFFSET                           0x1338u /* established */
#define REX3_STATUS_GFIRQ_SHIFT                      20 /* inferred */
#define REX3_STATUS_GFIRQ_MASK                       0x1u
#define REX3_STATUS_GFIRQ_INPLACE (REX3_STATUS_GFIRQ_MASK << REX3_STATUS_GFIRQ_SHIFT)
#define REX3_STATUS_BFIRQ_SHIFT                      19 /* inferred */
#define REX3_STATUS_BFIRQ_MASK                       0x1u
#define REX3_STATUS_BFIRQ_INPLACE (REX3_STATUS_BFIRQ_MASK << REX3_STATUS_BFIRQ_SHIFT)
#define REX3_STATUS_BLEVEL_SHIFT                     13 /* inferred */
#define REX3_STATUS_BLEVEL_MASK                      0x1fu
#define REX3_STATUS_BLEVEL_INPLACE (REX3_STATUS_BLEVEL_MASK << REX3_STATUS_BLEVEL_SHIFT)
#define REX3_STATUS_GLEVEL_SHIFT                     7 /* established */
#define REX3_STATUS_GLEVEL_MASK                      0x3fu
#define REX3_STATUS_GLEVEL_INPLACE (REX3_STATUS_GLEVEL_MASK << REX3_STATUS_GLEVEL_SHIFT)
#define REX3_STATUS_VIDINT_SHIFT                     6 /* inferred */
#define REX3_STATUS_VIDINT_MASK                      0x1u
#define REX3_STATUS_VIDINT_INPLACE (REX3_STATUS_VIDINT_MASK << REX3_STATUS_VIDINT_SHIFT)
#define REX3_STATUS_VRINT_SHIFT                      5 /* inferred */
#define REX3_STATUS_VRINT_MASK                       0x1u
#define REX3_STATUS_VRINT_INPLACE (REX3_STATUS_VRINT_MASK << REX3_STATUS_VRINT_SHIFT)
#define REX3_STATUS_BBUSY_SHIFT                      4 /* established */
#define REX3_STATUS_BBUSY_MASK                       0x1u
#define REX3_STATUS_BBUSY_INPLACE (REX3_STATUS_BBUSY_MASK << REX3_STATUS_BBUSY_SHIFT)
#define REX3_STATUS_GBUSY_SHIFT                      3 /* established */
#define REX3_STATUS_GBUSY_MASK                       0x1u
#define REX3_STATUS_GBUSY_INPLACE (REX3_STATUS_GBUSY_MASK << REX3_STATUS_GBUSY_SHIFT)
#define REX3_STATUS_VERS_SHIFT                       0 /* established */
#define REX3_STATUS_VERS_MASK                        0x7u
#define REX3_STATUS_VERS_INPLACE (REX3_STATUS_VERS_MASK << REX3_STATUS_VERS_SHIFT)

/*
 * Linux declares a second status word here. Single source; no reading of its
 * bits. MAME's model returns the status word for it, which is a model, not
 * evidence.
 */
/* ustatus: r32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member ustatus */
#define REX3_USTATUS_OFFSET                          0x133cu /* inferred */

/*
 * Linux declares a display-bus reset word here. Single source; no driver writes
 * it. Role inferred from the name only.
 */
/* dcbreset: rw32, reset unknown; Linux Newport framebuffer header (struct
 * newport_rexregs or newport_cregs; offset from the declared layout, checked
 * with offsetof), member dcbreset */
#define REX3_DCBRESET_OFFSET                         0x1340u /* inferred */

#define REX3_BASE_FROM_BOARD                         0xf0000u /* established */
#define REX3_GO_OFFSET                               0x800u /* established */
#define REX3_PROBE_XSTART_SHIFT                      0xbu /* established */

#endif /* REX3_GEN_H */
