<!-- generated from devices/rex3/registers.toml by defs-gen - do not edit, change the source -->
<!-- SPDX-License-Identifier: BSD-3-Clause -->
<!-- defs-gen 5 -->
<!-- input sha256 7ba54c6ee573d96e32054fc5d3a0227ba4f16cf9fe67a4c195d8202f1ea7dea4 -->

# REX3 raster engine (Indy and Indigo2 graphics)

Register file of the REX3 chip. Offsets are bytes from the REX3 base, which is 0xf0000 from the board base the public drivers map. Every register is 32 bits wide. The draw registers can be written at their own offset (the value is stored) or at the same offset plus GO_OFFSET (the value is stored and the primitive the latched draw mode describes is started); the configuration registers further up the map have the same pair, the same distance apart. Names and offsets are the ones the public Linux and NetBSD Newport headers declare, which agree where both define a register. Where only Linux declares a register the grade is inferred and the entry says so, unless a reading already in this repository confirms the offset. The drivers show what software writes and expects, not what the chip does with it: a role given from a name alone is marked inferred in the entry. Reset values are not given: no source states one. Nothing was measured on a board.

Unit `rex3`, macro prefix `REX3`.
Default source: Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header.

Every item has a grade: established, inferred or unknown. A grade says how the item was derived from its source; it does not claim the item was measured on silicon.

## Registers

| Register | Offset | Access | Width | Count | Space | Reset | Grade | Source |
|---|---|---|---|---|---|---|---|---|
| `drawmode1` | 0x0 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |
| `drawmode0` | 0x4 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |
| `lsmode` | 0x8 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_LSMODE |
| `lspattern` | 0xc | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_LSPATTERN |
| `lspatsave` | 0x10 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_LSPATSAVE |
| `zpattern` | 0x14 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_ZPATTERN |
| `colorback` | 0x18 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_COLORBACK |
| `colorvram` | 0x1c | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_COLORVRAM |
| `alpharef` | 0x20 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_ALPHAREF |
| `stall0` | 0x24 | rw | 32 |  |  | unknown | inferred | NetBSD sgimips Newport register header REX3_REG_STALL0; Linux Newport framebuffer header leaves the word undeclared |
| `smask0x` | 0x28 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK0X |
| `smask0y` | 0x2c | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK0Y |
| `setup` | 0x30 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SETUP |
| `stepz` | 0x34 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member _stepz |
| `lsrestore` | 0x38 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member _lsrestore |
| `lssave` | 0x3c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member _lssave |
| `xstart` | 0x100 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XSTART, member _xstart; NetBSD sgimips Newport driver board probe |
| `ystart` | 0x104 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member _ystart |
| `xend` | 0x108 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member _xend |
| `yend` | 0x10c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member _yend |
| `xsave` | 0x110 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member xsave |
| `xymove` | 0x114 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYMOVE |
| `bresd` | 0x118 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member bresd |
| `bress1` | 0x11c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member bress1 |
| `bresoctinc1` | 0x120 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member bresoctinc1; the offset also matches the host-pixel reading in devices/rex3/host-pixels.md |
| `bresrndinc2` | 0x124 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member bresrndinc2 |
| `brese1` | 0x128 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member brese1 |
| `bress2` | 0x12c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member bress2 |
| `aweight0` | 0x130 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member aweight0 |
| `aweight1` | 0x134 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member aweight1 |
| `xstartf` | 0x138 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member xstartf |
| `ystartf` | 0x13c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member ystartf |
| `xendf` | 0x140 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member xendf |
| `yendf` | 0x144 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member yendf |
| `xstarti` | 0x148 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XSTARTI; NetBSD sgimips Newport driver board probe |
| `xendf1` | 0x14c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member xendf1 |
| `xystarti` | 0x150 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYSTARTI |
| `xyendi` | 0x154 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYENDI |
| `xstartendi` | 0x158 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member xstartendi |
| `colorred` | 0x200 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member colorred |
| `coloralpha` | 0x204 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member coloralpha |
| `colorgrn` | 0x208 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member colorgrn |
| `colorblue` | 0x20c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member colorblue |
| `slopered` | 0x210 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member slopered |
| `slopealpha` | 0x214 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member slopealpha |
| `slopegrn` | 0x218 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member slopegrn |
| `slopeblue` | 0x21c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member slopeblue |
| `wrmask` | 0x220 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_WRMASK |
| `colori` | 0x224 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_COLORI |
| `colorx` | 0x228 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member colorx |
| `slopered1` | 0x22c | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member slopered1 |
| `hostrw0` | 0x230 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_HOSTRW0 |
| `hostrw1` | 0x234 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_HOSTRW1 |
| `dcbmode` | 0x238 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE |
| `dcbdata0` | 0x240 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBDATA0 |
| `dcbdata1` | 0x244 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBDATA1 |
| `smask1x` | 0x1300 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK1X |
| `smask1y` | 0x1304 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK1Y |
| `smask2x` | 0x1308 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK2X |
| `smask2y` | 0x130c | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK2Y |
| `smask3x` | 0x1310 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK3X |
| `smask3y` | 0x1314 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK3Y |
| `smask4x` | 0x1318 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK4X |
| `smask4y` | 0x131c | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_SMASK4Y |
| `topscan` | 0x1320 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_TOPSCAN; NetBSD sgimips Newport driver writes 0x3ff |
| `xywin` | 0x1324 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYWIN; NetBSD sgimips Newport driver writes (4096 << 16) \| 4096 |
| `clipmode` | 0x1328 | rw | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |
| `stall1` | 0x132c | rw | 32 |  |  | unknown | inferred | NetBSD sgimips Newport register header REX3_REG_STALL1; Linux Newport framebuffer header leaves the word undeclared |
| `config` | 0x1330 | rw | 32 |  |  | unknown | inferred | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |
| `status` | 0x1338 | r | 32 |  |  | unknown | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* |
| `ustatus` | 0x133c | r | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member ustatus |
| `dcbreset` | 0x1340 | rw | 32 |  |  | unknown | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs; offset from the declared layout, checked with offsetof), member dcbreset |

### Register `drawmode1`

Draw mode word 1: the plane group and depth a draw writes, the host-port packing (RWPACKED, HOSTDEPTH, RWDOUBLE, SWAPENDIAN, written up in devices/rex3/host-pixels.md), the compare, dither, blend and logic-operation state. Every bit and value here is named at the same position in both headers (two value names differ, noted on the enums); what a bit does is graded per field, and only the host-port fields have a reading beyond the name.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31:28 | `logicop` | established | logicop (zero=0, and=1, andr=2, src=3, andi=4, dst=5, xor=6, or=7, nor=8, xnor=9, ndst=10, orr=11, nsrc=12, ori=13, nand=14, one=15) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 27 | `blendalpha` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Alpha blend. |
| 26 | `prefetch` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Read-ahead for programmed-I/O pixel reads, see devices/rex3/host-pixels.md. |
| 25 | `backblend` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Back blend enable. |
| 24:22 | `dfactor` | established | dfactor (zero=0, one=1, sc=2, msc=3, sa=4, msa=5) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 21:19 | `sfactor` | established | sfactor (zero=0, one=1, dc=2, mdc=3, sa=4, msa=5) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 18 | `blend` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Blend enable. |
| 17 | `fastclear` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Fast clear. NetBSD's rectangle fill sets it and loads COLORVRAM with the colour. |
| 16 | `dither` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Dither enable. |
| 15 | `rgbmode` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 14 | `compare_gt` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 13 | `compare_eq` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 12 | `compare_lt` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Compare enables LT, EQ and GT, one bit each. NetBSD sets all three in every draw it issues. |
| 11 | `swapendian` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 10 | `rwdouble` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 9:8 | `hostdepth` | established | hostdepth (h4=0, h8=1, h12=2, h32=3) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 7 | `rwpacked` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 6 | `yflip` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Named in both headers; no reading of its effect. |
| 5 | `dblsrc` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 | Named DSRC by Linux and DBLSRC by NetBSD. |
| 4:3 | `drawdepth` | established | depth (d4=0, d8=1, d12=2, d24=3) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |
| 2:0 | `planes` | established | planes (none=0, rgb=1, rgba=2, olay=4, pup=5, cid=6) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE1 |  |

### Register `drawmode0`

Draw mode word 0, the command register: the opcode, the addressing mode and the per-primitive option bits. NetBSD's console code draws with opcode draw in block mode and copies with scr2scr; the host-pixel paths are in devices/rex3/host-pixels.md. Bit positions and names are the same in both headers, except that only Linux names addressing modes 5 and 6. What each option bit does is not read beyond its name, except where the field says otherwise.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 23 | `ystride` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 22 | `endptfilter` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 21 | `ciclamp` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 20 | `xyoffset` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 19 | `lronly` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 18 | `shade` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 17 | `lsopaque` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 | As ZPOPAQUE for the line stipple; named only. |
| 16 | `zpopaque` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 | NetBSD's glyph drawing sets it together with COLORBACK; read as pattern zeros painting COLORBACK instead of leaving the pixel (inferred). |
| 15 | `length32` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 14 | `lsadvlast` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 13 | `enlspattern` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 | Use the line stipple (LSMODE and LSPATTERN). |
| 12 | `enzpattern` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 | Use ZPATTERN as a per-pixel enable; NetBSD's glyph drawing sets it and writes the pattern at its GO alias. |
| 11 | `skiplast` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 10 | `skipfirst` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 9 | `stopony` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 8 | `stoponx` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 7 | `alphahost` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 | As COLORHOST, for alpha. |
| 6 | `colorhost` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 | Take colour from the host port instead of the shading hardware; a host pixel write sets it (devices/rex3/host-pixels.md). |
| 5 | `dosetup` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 4:2 | `adrmode` | established | adrmode (span=0, block=1, iline=2, fline=3, aline=4, tline=5, bline=6) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |
| 1:0 | `opcode` | established | opcode (noop=0, read=1, draw=2, scr2scr=3) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DRAWMODE0 |  |

### Register `lsmode`

Line-stipple mode word. Its field layout is in neither header, so none is given here.

### Register `lspattern`

Line-stipple pattern word.

### Register `lspatsave`

Backup copy of the stipple pattern, named save by Linux's comment (a backup of the pattern).

### Register `zpattern`

Per-pixel pattern word; NetBSD's glyph path writes it at the GO alias once per row, with the row's glyph bits.

### Register `colorback`

Background colour. NetBSD stores the glyph background colour index here.

### Register `colorvram`

Clear colour for the fast VRAM clear (Linux comment); NetBSD's rectangle fill writes the colour here with FASTCLEAR set.

### Register `alpharef`

Reference alpha value for the alpha-function compare (Linux comment).

### Register `stall0`

NetBSD names this word a stall register and its comment says a write waits until the engine is idle. Linux declares only a pad here. Role inferred from NetBSD's name and comment; neither driver writes it.

### Register `smask0x`

Screen mask 0, x extent: a minimum and a maximum packed in one word (NetBSD's comment says min and max, 16.16). Which half is which is not read.

### Register `smask0y`

Screen mask 0, y extent, packed as SMASK0X.

### Register `setup`

Setup trigger. Both headers declare it; neither drives it in the console paths read. Linux names it with a leading underscore.

### Register `stepz`

Linux declares a word here named stepz. Single source; role unknown beyond the name.

### Register `lsrestore`

Linux declares it, next to LSPATSAVE; the name reads as restoring the stipple state. Single source; role inferred from the name only.

### Register `lssave`

Linux declares it next to LSRESTORE; the name reads as saving the stipple state. Single source; role inferred from the name only.

### Register `xstart`

Current x start of the primitive, integer and fraction combined. NetBSD's board probe writes 0x12345678 to XSTARTI and expects this register to read the low 16 bits of that shifted left by PROBE_XSTART_SHIFT. A qtest can discriminate: write 0x12345678 to XSTARTI and expect 0x02b3c000 from XSTART.

### Register `ystart`

Current y start, counterpart of XSTART. Single source (the name pairs it with XSTART).

### Register `xend`

Current x end point. Single source.

### Register `yend`

Current y end point. Single source.

### Register `xsave`

Copy of the integer x start for block addressing, from the Linux comment (a copy of xstart for block mode). Single source.

### Register `xymove`

Signed x and y offset applied for relative operations such as a screen copy (Linux comment: an offset from xstart, ystart). NetBSD packs x in bits 31:16 and y in bits 15:0 and, for a copy, stores the destination minus the source.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31:16 | `x` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYMOVE | Packed x offset (NetBSD REX3_XYMOVE_XSHIFT is 16). |
| 15:0 | `y` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYMOVE | Y half, inferred as the low half of the packed word. |

### Register `bresd`

Bresenham line decision term (name only). Single source.

### Register `bress1`

Bresenham line term S1 (name only). Single source.

### Register `bresoctinc1`

Bresenham octant and first increment. The host-pixel image put clears it before storing pixel words (devices/rex3/host-pixels.md).

### Register `bresrndinc2`

Bresenham rounding mode and second increment (name only). Single source.

### Register `brese1`

Bresenham error term E1 (name only). Single source.

### Register `bress2`

Bresenham term S2 (name only). Single source.

### Register `aweight0`

Anti-aliased line weight table entry (name only). Single source.

### Register `aweight1`

Anti-aliased line weight table entry (name only). Single source.

### Register `xstartf`

Start x as a float-format value (Linux types it as a float or word union). Single source.

### Register `ystartf`

Start y, same layout as XSTARTF. Single source.

### Register `xendf`

End x, same layout as XSTARTF. Single source.

### Register `yendf`

End y, same layout as XSTARTF. Single source.

### Register `xstarti`

Start x as an integer. NetBSD's board probe writes 0x12345678 here and reads XSTART; see that register.

### Register `xendf1`

A second end-x word Linux declares (named xendf1). Single source; MAME's model reads this offset as a copy of the XENDF word, which is a model, not evidence.

### Register `xystarti`

Start x and y as one packed integer word: x in bits 31:16, y in bits 15:0 (NetBSD packs x << 16 | y; devices/rex3/host-pixels.md records the image put writing it this way).

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31:16 | `x` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYSTARTI |  |
| 15:0 | `y` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYSTARTI |  |

### Register `xyendi`

End x and y as one packed integer word, packed as XYSTARTI.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31:16 | `x` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYENDI |  |
| 15:0 | `y` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYENDI |  |

### Register `xstartendi`

Start and end x as integers in one word (name only). Single source.

### Register `colorred`

Red (or colour-index) colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `coloralpha`

Alpha colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `colorgrn`

Green colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `colorblue`

Blue colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `slopered`

Red (or colour-index) slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `slopealpha`

Alpha slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `slopegrn`

Green slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `slopeblue`

Blue slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; the shading arithmetic is not read.

### Register `wrmask`

Plane write mask. NetBSD stores 0xffffffff for a fill and 0xff when drawing 8-bit glyphs.

### Register `colori`

Packed integer colour. NetBSD stores the glyph foreground colour index here.

### Register `colorx`

Linux declares a colour word here named colorx. Single source; role unknown beyond the name.

### Register `slopered1`

Linux declares a second red slope word here. Single source; role unknown beyond the name.

### Register `hostrw0`

Host data port, most significant word (devices/rex3/host-pixels.md for the packing at each depth and the GO alias used for pixel stores).

### Register `hostrw1`

Host data port, least significant word; used only for 64-bit transfers (devices/rex3/host-pixels.md).

### Register `dcbmode`

Display control bus mode: the data width, the slave address and register select, the acknowledge type and the chip-select timing for the next DCBDATA transfer. The two headers define the same bit positions and names. devices/rex3/byte-lanes.md records how the data bytes travel.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 28 | `swapendian` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE | Byte-order reversal of packed display-bus data (devices/rex3/byte-lanes.md). |
| 27:23 | `cssetup` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE | Chip-select setup time. |
| 22:18 | `cshold` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE | Chip-select hold time. |
| 17:13 | `cswidth` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE | Chip-select pulse width in display-bus clocks, packed as the Linux DCB_CYCLES macro does. |
| 12 | `enasyncack` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE |  |
| 11 | `ensyncack` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE |  |
| 10:7 | `dcbaddr` | established | dcbaddr (vc2=0, cmap_all=1, cmap0=2, cmap1=3, xmap_all=4, xmap0=5, xmap1=6, ramdac=7, video_cc1=8, video_ab1=9, lg3_bdvers0=10, ics1562=11, reserved=15) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE |  |
| 6:4 | `dcbcrs` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE | Control register select within the slave chip; the meaning depends on the slave addressed, see the per-chip pages. |
| 3 | `encrsinc` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE | Increment the control-register select after each display-bus transfer (Linux comment). |
| 2 | `endatapack` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE | Send all four bytes of the DCBDATA word instead of DATAWIDTH of them (Linux comment). |
| 1:0 | `datawidth` | established | dcbwidth (w4=0, w1=1, w2=2, w3=3) | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_DCBMODE |  |

### Register `dcbdata0`

Display bus data, most significant word. Linux accesses it as a word, as halfword 1 at +2 and as byte 3 at +3 depending on DATAWIDTH; NetBSD packs the first byte in bits 31:24 (devices/rex3/byte-lanes.md).

### Register `dcbdata1`

Display bus data, least significant word.

### Register `smask1x`

Screen mask 1 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `smask1y`

Screen mask 1 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `smask2x`

Screen mask 2 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `smask2y`

Screen mask 2 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `smask3x`

Screen mask 3 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `smask3y`

Screen mask 3 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `smask4x`

Screen mask 4 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `smask4y`

Screen mask 4 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE.

### Register `topscan`

Top-of-screen scanline. NetBSD's console init stores 0x3ff here with a comment that it does not know why; the meaning is read from the name only.

### Register `xywin`

Window origin offset, x in bits 31:16 and y in bits 15:0 (inferred from NetBSD's console init, which stores 4096 in both halves). Linux declares it unnamed in role.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31:16 | `x` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYWIN; NetBSD sgimips Newport driver writes (4096 << 16) \| 4096 |  |
| 15:0 | `y` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_XYWIN; NetBSD sgimips Newport driver writes (4096 << 16) \| 4096 |  |

### Register `clipmode`

Clipping mode: one enable per screen mask (0 to 4) in bits 4:0 and four window-id match enables in bits 12:9. NetBSD stores a value at init that sets exactly the four match enables. Bits 8:5 are unnamed in both headers.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 12 | `cidmatch3` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 11 | `cidmatch2` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 10 | `cidmatch1` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 9 | `cidmatch0` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 4 | `smask4` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 3 | `smask3` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 2 | `smask2` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 1 | `smask1` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |
| 0 | `smask0` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_CLIPMODE, REX3_CLIPMODE_*; Linux NPORT_CMODE_* |  |

### Register `stall1`

NetBSD names this word a stall register, matching STALL0. Role inferred from the name; neither driver writes it.

### Register `config`

Configuration register. NetBSD names the offset; the bit groups are Linux's alone, and no reading of any of them exists, so every field is inferred as a position only and its role is unknown. The register grade is inferred for the same reason.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 20 | `fbtyp` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 19:17 | `vr` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 16:14 | `to` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 13 | `gfaint` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 12:8 | `gd` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) | Linux names GD0 to GD4 for bits 8 to 12 but its group mask GDMSK also covers bit 7; the five named bits are taken here. |
| 7 | `bfaint` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 6:3 | `bd` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 2 | `ercvr` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 1 | `bwidth` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |
| 0 | `g32md` | inferred |  | NetBSD sgimips Newport register header REX3_REG_CONFIG (name and offset); Linux Newport framebuffer header struct newport_cregs and NPORT_CFG_* (bit layout) |  |

### Register `status`

Status. Drivers only read it, polling the busy bits and the FIFO levels before sending more work. NetBSD and Linux agree on the busy bits and on the graphics FIFO level mask; they differ by one bit on the back-end FIFO level.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 20 | `gfirq` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Linux names it GFIRQ; no reading. |
| 19 | `bfirq` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Linux names it BFIRQ; no reading. |
| 17:13 | `blevel` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Back-end FIFO level. NetBSD's mask covers bits 17:13; Linux's covers 18:13, so bit 18 is left out here and its owner is unknown. |
| 12:7 | `glevel` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Graphics FIFO level, six bits; NetBSD's wait for an empty FIFO tests it. |
| 6 | `vidint` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Video interrupt flag (Linux names it VIDINT). |
| 5 | `vrint` | inferred |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Vertical retrace interrupt flag (Linux names it VRINT). |
| 4 | `bbusy` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Back-end (display bus) busy; both drivers poll it before display-bus transfers, and devices/vc2/README.md records the kernel doing the same. |
| 3 | `gbusy` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Graphics engine busy; NetBSD's wait loop polls it. |
| 2:0 | `vers` | established |  | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header REX3_REG_STATUS, REX3_STATUS_*; Linux NPORT_STAT_* | Three bits named VERS by Linux; read as a revision number (inferred from the name). |

### Register `ustatus`

Linux declares a second status word here. Single source; no reading of its bits. MAME's model returns the status word for it, which is a model, not evidence.

### Register `dcbreset`

Linux declares a display-bus reset word here. Single source; no driver writes it. Role inferred from the name only.

## Enums

### Enum `adrmode`

Addressing mode. NetBSD defines span to aline; Linux also names the last two, which no second source confirms.

| Label | Value | Grade | Source |
|---|---|---|---|
| `span` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `block` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `iline` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `fline` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `aline` | 4 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `tline` | 5 | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `bline` | 6 | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `dcbaddr`

Display-bus slave address. Values 0 to 9 are in both headers (NetBSD names 7 the DAC, Linux Bt445). Values 10, 11 and 15 are in Linux alone, where they select the LG3 board-version and clock chips and a reserved slot.

| Label | Value | Grade | Source |
|---|---|---|---|
| `vc2` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `cmap_all` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `cmap0` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `cmap1` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `xmap_all` | 4 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `xmap0` | 5 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `xmap1` | 6 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `ramdac` | 7 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `video_cc1` | 8 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `video_ab1` | 9 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `lg3_bdvers0` | 10 | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `ics1562` | 11 | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `reserved` | 15 | inferred | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `dcbwidth`

Number of bytes of a DCBDATA word that go over the display bus, as Linux's W4, W1, W2 and W3 name the values 0 to 3 (devices/rex3/byte-lanes.md).

| Label | Value | Grade | Source |
|---|---|---|---|
| `w4` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `w1` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `w2` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `w3` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `depth`

Frame-buffer plane depth in bits, as the headers name the values DD4, DD8, DD12 and DD24.

| Label | Value | Grade | Source |
|---|---|---|---|
| `d4` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `d8` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `d12` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `d24` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `dfactor`

Blend destination factor (zero, one, source colour, its complement, source alpha, its complement). Values 6 and 7 are not named.

| Label | Value | Grade | Source |
|---|---|---|---|
| `zero` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `one` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `sc` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `msc` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `sa` | 4 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `msa` | 5 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `hostdepth`

Host pixel depth in bits. Linux names value 3 HD32 and NetBSD HD24; devices/rex3/host-pixels.md grades the packing, which has an 8-8-8-8 word.

| Label | Value | Grade | Source |
|---|---|---|---|
| `h4` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `h8` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `h12` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `h32` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `logicop`

Logic operation applied between the new and the old pixel, in the order and with the names both headers give. The value names which operation; value 3, replace, is what NetBSD's console fill and glyph code use. The operand roles follow the names and are inferred.

| Label | Value | Grade | Source |
|---|---|---|---|
| `zero` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `and` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `andr` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `src` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `andi` | 4 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `dst` | 5 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `xor` | 6 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `or` | 7 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `nor` | 8 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `xnor` | 9 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `ndst` | 10 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `orr` | 11 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `nsrc` | 12 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `ori` | 13 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `nand` | 14 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `one` | 15 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `opcode`

Primitive opcode, as both headers name it.

| Label | Value | Grade | Source |
|---|---|---|---|
| `noop` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `read` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `draw` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `scr2scr` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `planes`

Which plane group a draw writes, as named in the public headers. NetBSD names value 1 both RGB and CI (colour index in the same plane group); value 3 and 7 are not named by either header.

| Label | Value | Grade | Source |
|---|---|---|---|
| `none` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `rgb` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `rgba` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `olay` | 4 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `pup` | 5 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `cid` | 6 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

### Enum `sfactor`

Blend source factor, named as the headers name them (zero, one, destination colour, its complement, source alpha, its complement). Values 6 and 7 are not named.

| Label | Value | Grade | Source |
|---|---|---|---|
| `zero` | 0 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `one` | 1 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `dc` | 2 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `mdc` | 3 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `sa` | 4 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |
| `msa` | 5 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header |

## Constants

| Constant | Value | Grade | Source | Description |
|---|---|---|---|---|
| `BASE_FROM_BOARD` | 0xf0000 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header | Offset of the first REX3 register from the board base, NEWPORT_REX3_OFFSET in NetBSD. Linux maps the same register file at the matching place in the Indy and Indigo2 GIO window. |
| `GO_OFFSET` | 0x800 | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header | Distance from a register's plain address to its GO alias. NetBSD writes the primitive's last register at its address plus this value; Linux declares the two copies of the register block exactly this far apart (checked with offsetof), for the draw registers and again for the configuration registers. |
| `PROBE_XSTART_SHIFT` | 0xb | established | Linux Newport framebuffer header (struct newport_rexregs or newport_cregs) and NetBSD sgimips Newport register header | NetBSD's board probe writes 0x12345678 to XSTARTI and accepts the board when XSTART reads back the low 16 bits shifted left by this much. It follows that the integer start lives from bit 11 upward in XSTART. |

## Test vectors

A vector is a value recorded from a source. An example only shows the layout.

| Target | Value | Kind | Decoded |
|---|---|---|---|
| `dcbmode` | 0x84100b | vector | datawidth=3, encrsinc=1, dcbcrs=0, dcbaddr=0, enasyncack=1, cshold=1, cssetup=1 |
| `clipmode` | 0x1e00 | vector | cidmatch0=1, cidmatch1=1, cidmatch2=1, cidmatch3=1, smask0=0 |
