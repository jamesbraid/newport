<!-- keep -->
# Open questions

Questions the binaries and sources read so far do not yet answer. No hardware is available, so each one is answered from software or published material.

Each entry gives the owning file, the routes already tried and the next route to try. When a question is answered, move the answer into the owning header or chapter and delete the entry.

## LG1 (Entry graphics board)

### REX1 command bits 21 and 16, and bits 27:24

`lightInitInfo` issues 0x30200021, 0x30210021 and 0x30200023. What the extra bits do is unknown. Routes tried: the kernel and PROM
use only. Next: the ide VRAM test (`lg1_vram`) and the `lg1_rexregs` code, which probably exercise them.

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

### Which console geometry the LG1 PROM console uses

The font records, glyph format and 9 pixel font 0 are in the [LG1 board page](../platforms/lg1/README.md#review-2026-11-23). Not traced: whether the 1024 by 768 console runs the
80 by 36 window with 9 by 17 cells (window setup 0xbfc2f864, variant 18178) or the 18179 variant that the 4.0.5D data word at 0xbfc42e20 selects through variant 18181. Next: trace
the callers of 0xbfc31978 and the use of the window fields at object offset 0x58 to 0x78 in the repaint loop 0xbfc30154.

### The X server's LG1 path

Not located in the files held. Next: a Library search for the IRIX 6.5 X server and `lg1` direct-draw libraries.
