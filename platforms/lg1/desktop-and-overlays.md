# LG1: how desktop icons are drawn, and what the overlay planes and colour-map bank 3 hold

What the IRIX 5.3 desktop and X server send to the Entry board for icons, what the three plane groups are, which colour-map entries
the X server writes into bank 3, and where the PROM logo colour lives. Command words are on the [REX1 page](../../devices/rex1/README.md),
the four-pixel tile is on [tile fill](../../devices/rex1/tile-fill.md), the display-ID tables are on
[VC1: display IDs](../../devices/vc1/did-xmap.md) and the palette on [colour-map banks](../../devices/bt479/banks.md).

Grades follow [AGENTS.md](../../AGENTS.md). **[binary]** is read in a shipped object, with address (X server addresses are 5.3
`lg1mc.so` virtual addresses); **[hdr]** is a name from the shipped header `sys/lg1hw.h` (IRIX 4.0.5F, revision 1.27); **[source]**
is the IRIX source tree, cited by path and written in our own words; **[inferred]** says what it rests on. Nothing was run, so
"which command a given icon produced" is not observed.

## Desktop icons

**What draws them [binary, established as imports; use inferred].** The IRIX 5.3 desktop (`/usr/sbin/desktop`, file-manager
icons) links `libdesktopFileicon.so`, which imports plain Xlib and nothing from the GL libraries: `XFillPolygon`, `XFillArc`,
`XFillRectangle`, `XDrawLine`, `XDrawLines`, `XDrawArc`, `XDrawPoints`, `XCopyArea`, `XCreatePixmap`, `XCreateImage`,
`XSetStipple`, `XSetFillStyle`, and a private colour map (`XCreateColormap`, `XAllocColor`, `XInstallColormap`, `XQueryColors`) with
its own visual selection (`fiChooseVisual`, a property named `_SGI_ICONS_VISUALS`). The icon art itself is a vector description
(`usr/lib/filetype/system/iconlib/*.fti`, for example `Xlogo.fti`: colour changes and polygons given as vertex lists), not a bitmap.
So the icons are **filled polygons with a private colour map**, plus stipple shading and small point and line work, not `PutImage`
pictures. 4Dwm's own icon boxes are the other source (its resources use `iconDecoration: label image`, bitmap and pixmap images
set by clients); those arrive as bitmap copies and image puts (**inferred**).

**Command sequences, by X request [binary, from the [board page](README.md#x-server-the-drawing-commands-it-issues)].**

| X request | Server function (`lg1mc.so`) | Command and data |
|---|---|---|
| `XFillPolygon`, `XFillArc`, solid (the `.fti` shapes) | `rexFillPolygon`, `rexFillTriangle`, `rexSolidSpans`, `rexSolidFillSpans` | plain 0x121 per horizontal span (empty logic-operation nibble; `XSTARTI`, `XENDI`, then `YSTARTI` or a GO store); colour, mask and operation (bits 27:24) from `XSTATE`; no BLOCK |
| `XFillRectangle`, background and window fills | `rexDrawSolidRects` (0x5e30ed40) | 0x329 at SET, `XSTATE` = colour, mask << 16, operation << 24; the GO store on `YENDI` draws |
| `XDrawLine`, `XDrawLines`, `XDrawArc`, `XDrawPoints` | `rexLineSS`, `rexSegmentSS`, `rexPolyPoint`, `rexDrawPoints` | horizontal runs `(op << 28) \| 0x121`, vertical runs `(op << 28) \| 0x329`, sloped segments command `(op << 28) \| 1` stepped by GO stores to `XSTARTI`/`YSTARTI`; `AUX2` = group << 29 \| 0xf11 around the batch |
| `XSetFillStyle(FillStippled)` with `XSetStipple` | `rexStippledFS`, `rexStippledFillRects` | 0x921 spans with `LSMODE` and `LSPATTERN` |
| `XSetFillStyle(FillTiled)`, 4-pixel-wide tile | `rexTileRects` (0x5e312008) | 0x200121, one `RWAUX1` GO word per row ([tile fill](../../devices/rex1/tile-fill.md)) |
| `XCopyArea` from a pixmap, `XPutImage` | `rexDrawImage` (0x5e30f3d8) | 0x2000a9 \| op << 28, `XSTATE` = mask << 16, words at `RWAUX1` GO, four pixels per word, first pixel in the high byte; 16384 pixels or more go through the MC pixel DMA |
| `XCopyPlane`, bitmaps, glyphs | `rexDrawMonoImage`, `rexImageGlyphBltTE8` | 0x5b9, 0x5b1, 0x5a9, 0x5a1 (opaque adds 0x800000), `ZPATTERN` GO per row |

An icon therefore reaches the board mostly as **0x121 spans and 0x329 rectangles**, with 0x921 for stippled shading and 0x2000a9 for
pixmap copies. Which of them a given icon uses depends on the `.fti` file and cannot be read from the library's imports; the model
run's command log would say. Planes and window: every one of these writes `AUX2` = group << 29 with the group of the window's visual
(group 1, the pixel planes, for a normal window), draws in the window's own 8-bit colour indices, and relies on the window's display ID
and the colour-map bank in its mode word to turn the indices into colours ([bank rule](../../devices/vc1/did-xmap.md#what-a-model-must-do)).
The private colour map means the icon pixels are **not in bank 0**: the server loads each installed map into one of its hardware
banks (`rexInstallNormalMap`, `rexStoreNormalColors`), so a model that shows every window through bank 0 shows icon pixels through
entries bank 0 holds as zero (black) or as the wrong colour. **Inferred**; the discriminating check is the DID of the icon window
and the bank its mode word names at the time the icon is drawn.

## Plane groups

`AUX2` bits 31:29 are one three-bit code (**[hdr]**): 0 none, 1 pixel planes, 2 overlay planes, 3 CID planes (an earlier version of
the board page read them as independent bits; corrected with this page). **Established** as names; **[binary]** for the uses:

| Code | Who writes it | What it does |
|---|---|---|
| 1 (0x20000000) | `initRex`, PROM, every ordinary draw, `rexInitHW` second clear | the 8-bit displayed pixel planes |
| 2 (0x40000000) | kernel `rexClear` first clear; X `rexClearOverlays` (0x5e30e574) | clears rectangles to colour 0 (command 0x329, `XSTATE` 0x03ff0000); overlay and pop-up window pixels (**inferred** from the name and from the bank-3 windows below) |
| 3 (0x60000000) | `rexInitHW` first clear; `rexDrawCID` (0x5e30e454) | fills rectangles with a value that the code limits to 0 to 3 (`XSTATE` 0x03ff0000 plus the value); the ide CID test writes and reads back only 0 to 3 (`stand/arcs/ide/fforward/graphics/LIGHT/cid.c`, **[source]**), so this is a two-bit plane |

The window-id planes are what the `AUX2` low bits use: **[hdr]** names bits 3:0 screen mask 0 to 3 enable, bits 7:4 their polarity
and bits 23:8 four 4-bit CID match fields, so 0xf11 (written around the X server's line, point and span batches) reads as screen mask 0
on, inside polarity and CID match 1 equal to 0xf (**inferred**; no shipped code states the effect). A model that keeps one plane per
group and writes only the group the code names covers every shipped sequence.

## DIDs 6 to 8 and bank 3

**What the tables say [binary, established].** `vc1Init` loads the mode words 0x030d, 0x033d and 0x034d for display IDs 6, 7 and 8
(and 0x0304, 0x0308 for 4 and 5); the byte table of hardware colour maps maps entries 4, 5 and 6 to the same bank and offsets
(bank 3 with index offset 0x00, 0x30 and 0x40; [DID tables](../../devices/vc1/did-xmap.md#initial-entries)). The mode word's bit 0 is set only for
these three. So **DIDs 6, 7 and 8 select colour-map bank 3** and an index offset of 0, 0x30 or 0x40.

**Which plane group they show: not stated by anything read.** The server publishes overlay visuals through the standard
`SERVER_OVERLAY_VISUALS` property, with `FRAME_BUFFER_LAYER` and `TRANSPARENT_PIXEL` (strings at 0x5e2cefc8 and following; the property
writer at 0x5e2d3888), and clears group 2 for them, so overlay and pop-up windows keep their pixels in the overlay planes
(**inferred**) and the bit-0 mode words are what route those planes to bank 3 (**inferred**; no shipped code reads the chip's
choice). Whether overlay pixel 0 is transparent, and how the planes are combined with the pixel planes, is **unknown**.

**What the X server writes into bank 3 [binary, established].** Bank 3 is addressed with the access-bank byte 0x3f (Bt479 path) or
`bank << 6` in the colour-map command (LUT1 path). Only these entries are ever written:

| Entries | Writer | Content |
|---|---|---|
| 0x10 to 0x1f | `rexStorePupColors` (0x5e306588), at index + 0x10, 16-bit components shifted down to 8 bits | the pop-up colour map (hardware map 3, display ID index 32; hardware map 4 is the 4-plane maps' bank 3 at offset 0, DID 6): whatever clients store into it |
| pixel + 0x30, pixel + 0x40 | `rexStoreNormalColors` for hardware maps 5 and 6 | overlay-visual colour maps (DIDs 7 and 8) |
| 0x21, 0x22, 0x23 | the cursor colour routine (0x5e308640) | cursor colours; VC1 register 0x26 (cursor mode) selects the map |
| 1, 2 | the PROM's board library (`Lg1SetCursorColor`, `stand/arcs/lib/libsk/graphics/LIGHT/lg1_init.c`, **[source]**) | red and white; it sets cursor mode 0xc000 |

Everything else in bank 3 stays at the zero `bt479Init` wrote (banks 0, 2 and 3 are cleared; bank 1 is the grey ramp), so **an
overlay or pop-up pixel that selects a bank-3 entry nobody stored reads black, not magenta**. The tools that load them are the X
server (the table above, on client requests) and the cursor code; no other shipped program was found that writes bank 3.

**The IRIS logo colour [source, established; no tie to bank 3].** The PROM's graphical logo is not an overlay entry. Its colours are
palette entries 48 to 50 of the normal bank (`stand/arcs/include/style.h`, `stand/arcs/lib/libsk/graphics/htport.c` at the colour
setup, `stand/arcs/lib/libsc/gui/background.c`): index 49 for the logo is loaded as (0x4b, 0x00, 0x83), a violet; index 50 for its
shadow as (0x5f, 0x5f, 0x92); index 48 for the company name as yellow (0xff, 0xff, 0x00). The PROM's colour-map function selects bank 0 on the Bt479 path
(it writes control byte 0x0f at address 0x82 first; `stand/arcs/lib/libsk/graphics/LIGHT/lg1_tp.c`). None of the PROM logo colours is magenta (0xff, 0x00, 0xff). The one magenta
found is GL colour index 5 of the default colour-index map in the ide diagnostics
(`stand/arcs/ide/fforward/graphics/LIGHT/maps.h`), which is the usual GL colour 5. If the model draws magenta where the logo should be violet, check that the write
to index 49 (`CONTROL` 0x0f, `WRITE_ADDR` 49, three bytes through `PALETTE_RAM`) reaches bank 0 and that the screen is not being read
through another bank. The program that draws the "IRIS" logo on the login screen was not identified (`xdm`'s resources name only a
greeting; the 5.3 `clogin` was not read), so its colour index and bank are **unknown**.

## The login window's checkerboard (IRIX 6.2)

On the emulated Entry running IRIX 6.2 the user list of the login window is a one-pixel checkerboard of (219, 219, 170) and (219, 219, 255) where the Express shows flat grey (217, 217, 217) (a run observation on the model, not a hardware capture). Neither the X server's software nor the REX1 and VC1 hardware makes that pattern; the login client does.

- **Who draws it [binary].** The login program is `clogin` (`usr/Cadmin/bin/clogin`, subsystem `sysadmdesktop.sw.clients` on the 6.2 media; the run's process list shows `clogin` beside `Xsgi` and `xdm`). It defines `ordered_dither_uchar`, `dont_dither_uchar` and `dont_dither_uchar_fast`, `XAllocColorCubeAndAdditionalColors` and `imageIcon::GetXPixmap` and `DrawX`, whose last parameters are a dither mode and a colour cube; it imports `XCreatePixmap`, `XCreateImage` and `XPutImage`, and it takes the icon panel's `renderBackground` and `setBackgroundColor` from `libdesktopIcon.so`. Its strings include the resource names `ditherBackground` and `installColormap`. The user list is the icon panel. **Established** for the routines and resource names; **inferred** that the panel background goes through `ordered_dither_uchar` (the call from `renderBackground` was not traced).
- **The colours fit the 8-bit cube.** Red and green 219 are level 6 of the 3-bit fields (6 * 255 / 7 = 218.6) and blue 170 and 255 are levels 2 and 3 of the 2-bit field (0, 85, 170, 255), the cube the 8-bit TrueColor visual presents. The grey 217 asks for red and green level 6 and a blue 55 percent of the way from level 2 to level 3, which an ordered dither renders as alternate pixels of the two blue levels.
- **The server and the board do not issue it.** The X server's draw functions use only the colour-index forms (an empty logic-operation nibble, the colour from `XSTATE`, `RGBMODECMD` and `DITHER`, bits 14 and 15, never set: [REX1 page](../../devices/rex1/README.md), and an immediate scan of `lg1mc.so` found no command word with either bit), and the core server has no dither code (its only dither strings belong to the video extension). A colour the server hands out is one pixel value, never a pattern. **Established** for the scan; the full `lg1mc.so` was not read for every immediate.
- **The Express shows flat grey** because its visual is 24-bit, where the client has no cube to dither to and the same code takes the `dont_dither` path (**inferred** from the two routine names and the observation).

So the checkerboard is correct output arriving as pixel data (a `PutImage` or a stipple fill) and is not a rendering bug in the board model. The model has nothing to add for it.

## Open

- Which plane group and bank a given icon, logo or pop-up pixel used in the failing run: the command log and the VC1 mode table at
  the time would say.
- What the chip does with mode-word bit 0 and the overlay planes (see [DID tables](../../devices/vc1/did-xmap.md#open)).
- The `.fti` interpreter was not read; its use of stipple and pixmap copies is **inferred** from imports only.
