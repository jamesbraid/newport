<!-- keep -->
# Open questions

Questions the binaries and sources read so far do not yet answer. No hardware is available, so each one is answered from software or published material.

Each entry gives the owning file, the routes already tried and the next route to try. When a question is answered, move the answer into the owning header or chapter and delete the entry.

## LG1 (Entry graphics board)

### REX1 command bit 16, AUX1 bit 8 and the pixel-memory probe outcomes

Bits 21 and 1 of the probe commands are decoded (inferred) on the [REX1 page](../devices/rex1/README.md#the-pixel-memory-probe-commands). Open: what bit 16 of 0x30210021 and `AUX1` bit 8
select so that one pixel pair of four is replaced, and what outcomes 0 and 1 mean for the board. Routes tried: kernel, both PROMs and the `ide` board-info copy (same routine); no object reads info byte
0x29 afterwards; the `ide` VRAM test uses only the fill, point and glyph commands. Next: the X server and `gfxinfo` readers of the board-info call, if held.

### CONFIGMODE bits 31 and 22:13, and the FIFO interrupt source

`initRex` and the pixel DMA path store 0x807fe000; `lightPcxSwap` saves bit 31 inverted. Route tried: all kernel users. Next: the
ide `lg1_*` tests and any GIO specification section on the FIFO.

### VC1 table entry format and register fields

Owning file: `devices/vc1/README.md` and `devices/vc1/timing-tables.md`. No VC1 data sheet is held. Routes tried: the Library by
name, the kernel and PROM tables, the shipped diagnostics' strings. Next: the Express VC1 headers in the public techomancer
`gr2` repository (reading counts as Express-family exposure), the LSI Logic VC1 data sheet if it can be found by part number
`L1A6654`.

### REX1 chip part number and colour-map part on a revision below 2 board

Only photographs exist (Library `photos/`): the REX part number is not legible. Next: a higher-resolution photograph of an LG1
board, or the board's parts list if SGI published one.

### The X server's LG1 path

Not located in the files held. Next: a Library search for the IRIX 6.5 X server and `lg1` direct-draw libraries.

### REX1 copy: sign of `XYMOVE`

NetBSD stores source minus destination (top-down rows). The PROM copy routine at 0xbfc2d9f8 stores the differences of its two coordinate pairs (third minus first for x, fourth minus second for y) and draws the rectangle at the second pair, and no caller was found in
the 4.0.5D console code (the repaint loop redraws instead of scrolling). Routes tried: table-entry callers in 0xbfc2f000-0xbfc41000. Next: other firmware callers of the draw table, the 4.0.5G console.
