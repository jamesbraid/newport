<!-- keep -->
# Open questions

Questions the binaries and sources read so far do not yet answer. No hardware is available, so each one is answered from software or published material.

Each entry gives the owning file, the routes already tried and the next route to try. When a question is answered, move the answer into the owning header or chapter and delete the entry.

## LG1 (Entry graphics board)

### REX1 pixel-memory probe outcomes

Bits 21, 16 and 1 of the probe commands and `AUX1` bit 8 are named and decoded (inferred) on the [REX1 page](../devices/rex1/README.md#the-pixel-memory-probe-commands): COLORAUX, COLORCOMP and COLORCOMPGT in the shipped header, so the second write is a one-sided colour compare. Open: which compare sense outcomes 0 (REX revision A) and 1 (revision B) are, and what they mean for the board. Routes tried: kernel, both PROMs and the `ide` board-info copy (same routine); no object reads info byte
0x29 afterwards; the `ide` VRAM test uses only the fill, point and glyph commands; the X server module (IRIX 5.3 and 6.5) never issues bit 16 and reads only the other board-info fields. Next: `gfxinfo` output on a real machine, if a transcript exists in a public archive.

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

### Shaded drawing: the chip's dither, colour range and unexplained flags

Owning files: [shaded drawing](../devices/rex1/shaded-drawing.md), [GL context state](../devices/rex1/gl-context-state.md) and [true lines](../devices/rex1/true-lines.md). What is open, each of it a hardware behaviour the IRIX 6.2 GL expects but whose arithmetic no shipped software contains:

- The dither: matrix, size and amplitude (the library's rounding offset of 15.0 and its colour scales of 226, 226 and 255 are the only hints), and whether dither adds, compares or saturates.
- What a colour accumulator does outside 0 to 255 (the library stores values from below zero to above 511 and never clamps).
- The effect of command bit 25 (`LRQPOLY`, set on every triangle row), of `SHADECONTINUE` (the reading "continue the colour between 32-pixel pieces" is a name-based inference) and of `INITFRAC`.
- The roles of `AUX1` bits 1:0 (`FRACTION`) and 9 (`DITHERRANGE`), which every GL context sets and the X server never does, and of `AWEIGHT`, which the GL writes once and nothing reads.
- Which nibble is buffer 0 (the software fixes only the pairing with mode-word bit 1), how the `CIDMATCH` nibbles of `AUX2` act, and the stipple bit order of the GL's line stipple.

Routes tried: every `__glRex*` routine for the span, triangle-row, point, line, clear and copy paths in the 6.2 `libGLcore.so` of the IP20LG1MC arch, the constants of the 6.2 `libgl.so`, the ide diagnostics' REX, VRAM and pattern tests and `minigl.c` (source tree), the 6.2 `lg1.a` context code, `lg1mc.so` for the command words, and the public Linux Newport header by name (the file body was not retrievable). Next: the IRIS GL (`libgl.so`) polygon and line code for the same board, which was not read beyond its constants; the 5.3 and 6.5 builds of the same library if the media hold one for this board; published Newport (REX3) documentation, used only for names unless the register layouts are shown to match.

### XYMOVE in the PROM copy routine

The X server's copy routine settles the sign for the X server (source minus destination, in stored coordinates; [REX1](../devices/rex1/registers.md)). The PROM routine at 0xbfc2d9f8 stores the differences of its two coordinate pairs in an order that matches only if its second pair is the source, and no caller was found in the 4.0.5D console code. Routes tried: table-entry callers in 0xbfc2f000-0xbfc41000. Next: other firmware callers of the draw table, the 4.0.5G console.

### X server and kernel: the colour source, the logic-operation nibble and what `AUX2` bits 11:0 do

The X server fills with command 0x329 and takes colour, mask and operation from `XSTATE`; the kernel and PROM fill with 0x30000329 and take the colour from `COLORREDI`; the X server's glyph path fills a background with 0x30000329 using only `XSTATE`. The one consistent reading is that `XSTATE` bits 7:0 and `COLORREDI` are the same state, but the effect of a non-zero nibble in both places (the PutImage path sets both) and of `XSTATE` bit 29 in the copy words is not read. 0x328 and 0xf11 are settled as not being commands: the line code ORs 0x328 and 0x121 into a word holding the operation and DRAW, and ORs 0xf11 into `AUX2` ([board page review](../platforms/lg1/README.md#review-2026-11-23-of-this-section)); whether `AUX2` bits 11:0 do what the shipped header's names for them say (screen mask enables and polarity, CID match nibbles), are not read. The slope registers' arithmetic (`MINORSLOPE`, the colour slopes, `XSAVE`, `XYMOVE`) is now read for the IRIX 6.2 GL on [true lines](../devices/rex1/true-lines.md) and [shaded drawing](../devices/rex1/shaded-drawing.md); the X server's own sloped loops are not. Routes tried: the X server's draw routines (5.3 and 6.5). Next: read the sloped-segment loops of `rexLineSS`, `rexSolidZeroSeg` and `rexFillTriangle` in full.

### Per-window colour map and buffer: how the VC1 turns its tables into pixels

The X server loads window-id line and frame tables into the VC1 SRAM and writes a mode word per id into the display-mode window ([board page](../platforms/lg1/README.md#x-server-the-colour-map-vc1-and-cursor)); the table formats, the mode-word bank field and the per-DID banks are now on [display IDs and the mode table](../devices/vc1/did-xmap.md) and [colour-map banks](../devices/bt479/banks.md). Still unknown: what the chip does with mode-word bits 0, 9:8 and 14:12 and the odd half of the table, whether the index offset adds or replaces, how pop-up pixels reach bank 3, and whether the second plane group is ever displayed (value 3 is named `CIDPLANES` in the shipped header). Also unknown: whether VC1 register 0x80 is a data latch (the retrace handler needs it to behave as one) and what generates the retrace pulse. The pixel DMA's GIO address (the CPU physical address of `RWAUX1` GO) and mode word (0x50 or 0x52, written to `dma_mode` by `MCdma`) are decoded on the board page review. Routes tried: every kernel and X server user; the `ide` VC1 test strings. Next: the Express VC1 headers under the exposure note above.
