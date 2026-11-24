<!-- keep -->
# Open questions

Questions the binaries and sources read so far do not yet answer. No hardware is available, so each one is answered from software or published material.

Each entry gives the owning file, the routes already tried and the next route to try. When a question is answered, move the answer into the owning header or chapter and delete the entry.

## LG1 (Entry graphics board)

### REX1 command bit 16, AUX1 bit 8 and the pixel-memory probe outcomes

Bits 21 and 1 of the probe commands are decoded (inferred) on the [REX1 page](../devices/rex1/README.md#the-pixel-memory-probe-commands). Open: what bit 16 of 0x30210021 and `AUX1` bit 8
select so that one pixel pair of four is replaced, and what outcomes 0 and 1 mean for the board. Routes tried: kernel, both PROMs and the `ide` board-info copy (same routine); no object reads info byte
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

### XYMOVE in the PROM copy routine

The X server's copy routine settles the sign for the X server (source minus destination, in stored coordinates; [REX1](../devices/rex1/registers.md)). The PROM routine at 0xbfc2d9f8 stores the differences of its two coordinate pairs in an order that matches only if its second pair is the source, and no caller was found in the 4.0.5D console code. Routes tried: table-entry callers in 0xbfc2f000-0xbfc41000. Next: other firmware callers of the draw table, the 4.0.5G console.

### X server and kernel: the colour source, the logic-operation nibble and the draw-less commands

The X server fills with command 0x329 and takes colour, mask and operation from `XSTATE`; the kernel and PROM fill with 0x30000329 and take the colour from `COLORREDI`; the X server's glyph path fills a background with 0x30000329 using only `XSTATE`. The one consistent reading is that `XSTATE` bits 7:0 and `COLORREDI` are the same state, but the effect of a non-zero nibble in both places (the PutImage path sets both) and of `XSTATE` bit 29 in the copy words is not read. The line commands 0x328 and 0xf11 and the slope registers' arithmetic (`MINORSLOPE`, `XSAVE`) were located, not read. Routes tried: the X server's draw routines (5.3 and 6.5). Next: read `rexLineSS`, `rexSolidZeroSeg` and `rexFillTriangle` in full.

### Per-window colour map and buffer: how the VC1 turns its tables into pixels

The X server loads window-id line and frame tables into the VC1 SRAM and writes a mode word per id into the display-mode window ([board page](../platforms/lg1/README.md#x-server-the-colour-map-vc1-and-cursor)); how the chip uses them to pick the colour-map bank and buffer per pixel, the entry format, and whether the second plane group is ever displayed are unknown. Also unknown: whether VC1 register 0x80 is a data latch (the retrace handler needs it to behave as one), what generates the retrace pulse, and the GIO address and mode of the pixel DMA (`Lg1PixelDma` passes mode 0x50 or 0x52 to `MCdma`). Routes tried: every kernel and X server user; the `ide` VC1 test strings. Next: `vdma.o` `MCdma` in the IP20 `io.a` for the mode word, and the Express VC1 headers under the exposure note above.
