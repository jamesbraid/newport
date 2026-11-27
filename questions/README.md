<!-- keep -->
# Open questions

Questions the binaries and sources read so far do not yet answer. No hardware is available, so each one is answered from software or published material.

Each entry gives the owning file, the routes already tried and the next route to try. When a question is answered, move the answer into the owning header or chapter and delete the entry.

## LG1 (Entry graphics board)

### REX1 pixel-memory probe outcomes

Bits 21, 16 and 1 of the probe commands and `AUX1` bit 8 are named and decoded (inferred) on the [REX1 page](../devices/rex1/README.md#the-pixel-memory-probe-commands): COLORAUX, COLORCOMP and COLORCOMPGT in the shipped header, so the second write is a one-sided colour compare. Open: which compare sense outcomes 0 (REX revision A) and 1 (revision B) are, and what they mean for the board. Routes tried: kernel, both PROMs and the `ide` board-info copy (same routine); no object reads info byte
0x29 afterwards; the `ide` VRAM test uses only the fill, point and glyph commands; the X server module (IRIX 5.3 and 6.5) never issues bit 16 and reads only the other board-info fields. Next: `gfxinfo` output on a real machine, if a transcript exists in a public archive.

### LSMODE repeat of 0

The X server's stippled fills (spans and rectangles) store 0 in both repeat bytes of `LSMODE` and need one pixel per pattern bit; the IRIX 6.2 OpenGL library stores a line-stipple factor of 256 as 0 and needs 256 ([LSMODE](../devices/rex1/true-lines.md#lsmode-length-and-repeat)). Both cannot hold for one counter. The byte roles are now read as 7:0 live counter and 15:8 reload factor (inferred, from the published REX3 specification's LSMODE and the writers; [LSADVLAST](../devices/rex1/true-lines.md#lsadvlast-command-bit-12) is inferred the same way and leaves no open question). The reading that fits every writer is a repeat honoured in line draws only, with 0 meaning 256 there; it differs from "0 means 1" only for a line drawn with both bytes 0, which is a GL factor of 256. Routes tried: every `LSMODE` writer in the 5.3 and 6.2 `lg1mc.so` and the 6.2 `libGLcore.so` and `libgl.so` (none writes unequal bytes), the ide `rex.c` register test (patterns with equal bytes only), the wide-line code (it issues the stipple-save opcode and rewrites both bytes alike), the kernel context save, the 4.0.5G PROM (no writer), the REX3 specification (factor 1 to 255; repeat for lines only), the Linux and NetBSD Newport headers (names only), the ide Newport sources (a length-only write with repeat 0, never read back). Next: the 6.5 X server module for a write with unequal bytes; a published description of the REX1 stipple unit, if one exists; published output from a real Entry board of a stippled OpenGL line with a repeat factor of 256.

### CONFIGMODE bit 31, bits 22:21, and the FIFO interrupt condition

`initRex` and the pixel DMA path store 0x807fe000; `lightPcxSwap` saves bit 31 inverted. The X server stores 0xc0180000 | (level << 13) and 0x80180000 | (level << 13) (levels 7 to 31), so bits 17:13 are a level and bits 20:19 are constant ([REX1 register list](../devices/rex1/registers.md)); what bit 31 does, what bits 22:21 do (the kernel sets them, the server does not), and which count crosses the level to raise the interrupt on GIO line 0 are not settled. Routes tried: every kernel and X server user. Next: the ide `lg1_*` tests and any GIO specification section on the FIFO.

### VC1 table entry format and register fields

Owning file: `devices/vc1/README.md` and `devices/vc1/timing-tables.md`. No VC1 data sheet is held. Routes tried: the Library by
name, the kernel and PROM tables, the shipped diagnostics' strings. Next: the Express VC1 headers in the public techomancer
`gr2` repository (reading counts as Express-family exposure), the LSI Logic VC1 data sheet if it can be found by part number
`L1A6654`.

### REX1 chip part number and colour-map part on a revision below 2 board

Only photographs exist (Library `photos/`): the REX part number is not legible. Next: a higher-resolution photograph of an LG1
board, or the board's parts list if SGI published one.

### Shaded drawing: SHADECONTINUE and INITFRAC

Owning files: [shaded drawing](../devices/rex1/shaded-drawing.md), [GL context state](../devices/rex1/gl-context-state.md) and [true lines](../devices/rex1/true-lines.md). What is open is a hardware behaviour the IRIX 6.2 GL expects but whose arithmetic no shipped software contains (the dither, command bit 25, the `AUX1` fraction and range bits, `AWEIGHT`, the physical buffer nibbles and how the screen masks combine are settled as unknown on the owning pages, the dither in its own entry below; out-of-range colours have an inferred sibling reading there; the outside polarity is a software expectation there):

- The effect of `SHADECONTINUE` (the reading "continue the colour between 32-pixel pieces" is a name-based inference) and of `INITFRAC`.

Routes tried: every `__glRex*` routine for the span, triangle-row, point, line, clear and copy paths in the 6.2 `libGLcore.so` of the IP20LG1MC arch, the constants of the 6.2 `libgl.so`, the ide diagnostics' REX, VRAM and pattern tests and `minigl.c` (source tree), the 6.2 `lg1.a` context code, `lg1mc.so` for the command words, and the public Linux Newport header by name (the file body was not retrievable). Next: the IRIS GL (`libgl.so`) polygon and line code for the same board, which was read only for its command words and context set-up (2026-11-25); the 5.3 and 6.5 builds of the same library if the media hold one for this board; published Newport (REX3) documentation, used only for names unless the register layouts are shown to match.

### REX1 dither: matrix, phase, amplitude, and the `AUX1` fraction and range bits

Owning file: [shaded drawing](../devices/rex1/shaded-drawing.md#2-colour-to-pixel-truncation-or-dither). Known: the chip dithers in hardware when command bit 15 is set (header name, the GL's use, and a 1991 remark by an SGI employee that REX dithers 24-bit colour into the colour map); the position dependence is inferred, and so is the absence of a visible wrap on a carry. Weakly inferred: the matrix is the REX3 4 by 4 Bayer matrix, from lineage (shared register shapes, command-bit names and order) against known differences (REX3 scales and rounds in hardware, REX1's GL does both itself). Open: whether that is REX1's matrix, whether its phase is window-relative or screen-absolute, the compare rule, the amplitude, which fraction bits feed it, and what `FRACTION1:0` and `DITHERRANGE` control (REX3 has no counterpart). Routes tried: the REX3 specification (sections 3.8.2, 3.8.3, 5.4.3.2, the DRAWMODE tables), NetBSD, OpenBSD and Linux Newport headers (names only), MAME's Entry-board model (no drawing dither), the `ide` LG1 sources, both PROMs, the 5.3, 6.2 and 6.5 kernels, X server modules and `Xsgi`, the 6.2 and 6.5 OpenGL and IRIS GL libraries of the Entry arch (the generic software table is the same matrix; the Entry board never reaches it), the Library's Usenet archive (one 1991 remark, no table), the Indigo owner's guide (no dither text). Next: a published framebuffer dump or high-magnification screenshot of a dithered flat or ramp fill from an Indigo Entry board, if one exists in a public archive.

### XYMOVE in the PROM copy routine

The X server's copy routine settles the sign for the X server (source minus destination, in stored coordinates; [REX1](../devices/rex1/registers.md)). The PROM routine at 0xbfc2d9f8 stores the differences of its two coordinate pairs in an order that matches only if its second pair is the source, and no caller was found in the 4.0.5D console code. Routes tried: table-entry callers in 0xbfc2f000-0xbfc41000. Next: other firmware callers of the draw table, the 4.0.5G console.

### X server and kernel: the colour source, the logic-operation nibble and what `AUX2` bits 11:0 do

The X server fills with command 0x329 and takes colour, mask and operation from `XSTATE`; the kernel and PROM fill with 0x30000329 and take the colour from `COLORREDI`; the X server's glyph path fills a background with 0x30000329 using only `XSTATE`. The one consistent reading is that `XSTATE` bits 7:0 and `COLORREDI` are the same state, but the effect of a non-zero nibble in both places (the PutImage path sets both) and of `XSTATE` bit 29 in the copy words is not read. 0x328 and 0xf11 are settled as not being commands: the line code ORs 0x328 and 0x121 into a word holding the operation and DRAW, and ORs 0xf11 into `AUX2` ([board page review](../platforms/lg1/README.md#review-2026-11-23-of-this-section)); whether `AUX2` bits 11:0 do what the shipped header's names for them say (screen mask enables and polarity, CID match nibbles), are not read. The slope registers' arithmetic (`MINORSLOPE`, the colour slopes, `XSAVE`, `XYMOVE`) is now read for the IRIX 6.2 GL on [true lines](../devices/rex1/true-lines.md) and [shaded drawing](../devices/rex1/shaded-drawing.md); the X server's own sloped loops are not. Routes tried: the X server's draw routines (5.3 and 6.5). Next: read the sloped-segment loops of `rexLineSS`, `rexSolidZeroSeg` and `rexFillTriangle` in full.

### Per-window colour map and buffer: how the VC1 turns its tables into pixels

The X server loads window-id line and frame tables into the VC1 SRAM and writes a mode word per id into the display-mode window ([board page](../platforms/lg1/README.md#x-server-the-colour-map-vc1-and-cursor)); the table formats, the mode-word bank field and the per-DID banks are now on [display IDs and the mode table](../devices/vc1/did-xmap.md) and [colour-map banks](../devices/bt479/banks.md). Still unknown: what the chip does with mode-word bits 0, 9:8 and 14:12 and the odd half of the table, whether the index offset adds or replaces, how pop-up pixels reach bank 3, and whether the second plane group is ever displayed (value 3 is named `CIDPLANES` in the shipped header). Also unknown: whether VC1 register 0x80 is a data latch (the retrace handler needs it to behave as one) and what generates the retrace pulse. The pixel DMA's GIO address (the CPU physical address of `RWAUX1` GO) and mode word (0x50 or 0x52, written to `dma_mode` by `MCdma`) are decoded on the board page review. Routes tried: every kernel and X server user; the `ide` VC1 test strings. Next: the Express VC1 headers under the exposure note above.

## REX3 and Newport from a little-endian CPU

### Which bytes REX3 takes from a store on a little-endian CPU

Owning file: [REX3 byte lanes](../devices/rex3/byte-lanes.md). Open: for `DCBDATA0` writes of more than one byte, for packed `HOSTRW0`
pixels of 12 bits or fewer and for unpacked 8-bit pixels, which of three rules REX3 follows when the CPU is little-endian (address
order with the endian bit honoured, fixed big-endian lanes, or a byte reversal in the chip); the page tabulates what a driver stores
under each. Also open: that the MC sets the byte-count cycle's little-endian bit from its CPU bit for a programmed-I/O access, and that
the MC and multiplexer specifications describe the Indy and Indigo2 parts. Routes tried: the REX3, GIO64, MC and multiplexer
specifications in full text; the IRIX 6.5.7 Newport sources (no endian branch); the 6.5 IP22 kernel's `DCBDATA0` and `HOSTRW0`
access sizes (big-endian only); Linux and NetBSD (big-endian only); the Library's Usenet and mailing-list archives by keyword.
Not tried: the OpenBSD and MAME Newport code (not in the Library; big-endian machines, so unlikely to help); the REX3 specification's page images beyond
page 79; the Newport hardware header and the helper-macro headers the PROM library uses (not in the source tree or media; if an Indy PROM or `ide` image carries them as debug information they would show whether the little-endian build changes the byte-member names); the 6.5.22 IP22 kernel (not in the local media). Next: a published description of REX3's GIO pad logic or a
run of any little-endian CPU against a real REX3, if a transcript exists in a public archive.

### Newport 24-bit board: remaining gaps

Owning file: [Newport board](../platforms/newport/README.md). Open: where an Indigo2 gets its board revision (the PROM keeps a
per-slot version from another source); the visual
each entry of the X server's per-depth tables names (the arrays are filled at run time in `rex3Init`); the contents of the colour map
and Bt445 (no colour-map specification is held, and `erikarn-bt445_ramdac.pdf` is an image-only scan that has not been read); whether
a board with revision 2 or higher can report 24 planes with bit 7 set. Routes tried: the PROM source, the IP22 kernel's
`newport_init.o`, the `ng1.so` data tables and `rex3Install24Map`, the Library by part name. Next: decompile `rex3Init` and
`rex3Probe` in `ng1.so` for the visual arrays; read the Bt445 scan page by page from images; the IRIX ide Newport sources for the
Indigo2 version source (`lg3_version`).

## VC2 cursor

### Cursor X origin on each board revision

Owning file: [VC2](../devices/vc2/README.md#where-the-constant-29-comes-from). IRIX adds 29 to X and 31 to Y; Linux uses 29, and 21 on board
revision 3. The PROM library's timing tables put the cursor-position channel 18 state-run units (36 pixels) ahead of the visible line for
boards below revision 3 and 14 units for revision 3, an 8-pixel difference that matches Linux. Open: whether the IRIX kernel's own timing
tables (it has no revision term in its position routine) use the 14-unit lead on revision 3, and the exact relation between the lead and
the origin (the specification asks for a lead of 20 units and gives an origin of 31 pixels). Routes tried: the VC2 and XMAP9
specifications, `newportPositionCursor`, `initVC2`, `ng1_init.c` and every table in `np_timing.h`, Linux and NetBSD. Next: decode the
kernel's tables in `newport_init.o` (`ng1_video_timing` records) for the position-channel lead per revision.

### What the VC2 does with an out-of-range cursor position

Owning file: [VC2](../devices/vc2/README.md#open). The specification's maximum for X is 2047 in the text and 4095 in the register table
(Y 2047). IRIX sends `x - hotx + 29` with no clamp and masks it to 16 bits, so a pointer at x = 0 with a large hot spot gives a wrapped
value. Routes tried: the specification in full text, the kernel routine, the ide `ng1vc2cursor` command (writes raw values). Next: any
published note on the VC2 cursor counter; otherwise unknown with no shipped software depending on it.

### 64 x 64 x 1 cursor and crosshair colour codes

Owning file: [VC2](../devices/vc2/README.md#open). The specification does not say which two-bit cursor code a set pixel of the one-plane
64 x 64 glyph produces, or which code the crosshair drives (its block diagram feeds the crosshair to input "01"). Only the ide command
`ng1vc2cursormode` selects either. Routes tried: the specification (text and the cursor-generation figure), the PROM library, the ide
sources, the kernel and X server (neither sets the 64 x 64 bit; the X server sets the crosshair bit). Next: the image-only parts of the
specification at higher resolution; any published screenshot of the crosshair.

### X server glyph buffer rows and the third cursor colour

Owning file: [VC2](../devices/vc2/README.md#glyph-format). `rex3DisplayCursor` fills at most 32 rows from the cursor bitmaps; whether the
rest of its 256-byte buffer is cleared first, and what sets the flag byte in the extra colour record that selects the three-colour
glyph, were not read. Routes tried: `rex3DisplayCursor`, `rex3InstallCursor`. Next: decode the cursor realize routine (`nfbRealizeCursor`)
that allocates the buffer.

### Colour-map command register values 7 and 3

Owning file: [VC2](../devices/vc2/README.md#colour-map-access). Cursor and ramp loads store 7 to colour-map register CRS 3 before and 3
after; the PROM source comments tie 7 to disabling composite blanking during a load and 3 to half-full FIFO trip. No colour-map
specification is held. Routes tried: the PROM source and image, the kernel, the X server, Linux and NetBSD (neither writes the register for
cursor colours). Next: the colour-map specification, if it can be found by part number in the Library.

## REX3 host pixels

### Which host depth the X server sets for each visual

Owning file: [REX3 host pixels](../devices/rex3/host-pixels.md#open). All six image routines OR `RWPACKED` into a per-visual `DRAWMODE1`
base word at offset 20 of a per-format record found through a table in the screen record; the records are filled elsewhere. Routes tried: the six routines, `rex3Init`, the visual setup
by string and constant search. Next: decode the code that fills those records (the 24-bit visual setup).
