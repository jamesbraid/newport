<!-- keep -->
# Open questions

Questions the binaries and sources read so far do not yet answer. No hardware is available, so each one is answered from software or published material.

Each entry gives the owning file, the routes already tried and the next route to try. When a question is answered, move the answer into the owning header or chapter and delete the entry.

## LG1 (Entry graphics board)

### REX1 registers named only by the ide test

Owning file: `devices/rex1/registers.toml`. The offsets of XSTARTF, XENDF, YSTARTF, YSTART, YENDF, XSAVE, MINORSLOPE, COLORRED
to COLORBLUE, SLOPERED to SLOPEBLUE, LSPATTERN, LSMODE, AWEIGHT, RWAUX2 and SMASK2 to SMASK4 are inferred from the ide REX register
test's name order and from the offsets that code confirms for their neighbours. Routes tried: the IRIX kernel graphics objects (`lg1.a`),
the PROM, NetBSD `light.c`. Next route: disassemble the ide REX register test (the `ide` IP20 binary, the function that calls the
register-test helper once per name; the helper's first two arguments are the offsets) in Ghidra and read the offset arguments
directly. The helper (at 0x853d670 in the ide image) takes two register addresses, the name and a mask among its arguments; the argument roles were read by a quick register trace, not in full.

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

### The PROM console geometry and font

Where the PROM stores its font and how it derives rows and columns on the LG1 (the drawing routine's bitmap pointer arguments).
Next: read the console text caller of 0xbfc2d684 (4.0.5D) for the font table address.

### The X server's LG1 path

Not located in the files held. Next: a Library search for the IRIX 6.5 X server and `lg1` direct-draw libraries.
