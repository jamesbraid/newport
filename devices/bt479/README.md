# Colour map on the Indigo Entry graphics board: Bt479 (board revision below 2) and LUT1 (revision 2 and up)

The 8-bit-index to RGB lookup that feeds the video output on the Entry board. Software reaches it only through the REX1 chip's
`RWDAC` port, with the register index in `CONFIGSEL` (see [REX1](../rex1/README.md#the-off-chip-ports)). Two variants exist,
told apart by the board revision byte the REX1 `WCLOCK` port reports (bits 2:0): below 2 the driver treats the part as a
Brooktree Bt479 (the shipped diagnostics print "Bt479 element ..."), 2 and above as the LSI Logic LUT1 (which the kernel
calls `lg2` in its tables; NetBSD calls the second board "LG2" and says the REX is the same chip family).

Grades follow [AGENTS.md](../../AGENTS.md). Sources: `lg1.a` members `light_init.o` (`initBt479`, `initLUT1`), `light_tp.o`
(`lg1_mapcolor`, `lg2_mapcolor`), `light.o` (`light_read_bt_colormaps`, `light_read_lut_colormaps`, `lightReadDisplay`), the
IP20 PROM 4.0.5D function at 0xbfc100e0 (and the helper it calls near 0xbfc0fb84), and the NetBSD sgimips `light.c` (public
driver). A photograph of an LG1 board shows a Brooktree-marked package ("Bt", observed) and, separately, a package marked
`L1A6651 LUT1 REV A` (observed): both appear on the board that the photo shows; which of the two a revision-below-2 board
actually populates is not settled by the photograph, so the board-revision rule above is the software's, not a hardware
fact (**inferred**). No Bt479 datasheet is held in the Library (searched `docs/library/cache` by name); register roles below
are derived from the access patterns only.

## Port protocol

**Established.** Every transfer picks a register index in `CONFIGSEL` and stores the byte in `RWDAC` and then in its GO alias; reads
read the GO alias. The indices the shipped code uses:

| `CONFIGSEL` | Role (Bt479 variant) | Evidence |
|---|---|---|
| 0 | palette address, written before a run of palette bytes | `initBt479`, `lg1_mapcolor`: the index then three bytes through selector 1 |
| 1 | palette data: three consecutive bytes (red, green, blue) per entry; the address advances after the third | `initBt479` loops 256 times writing three bytes |
| 2 | pixel read mask, written 0xff once colours are loaded | `initBt479`, `lg1_mapcolor` |
| 3 | read address; a write of 0 before a palette read | `light_read_bt_colormaps` |
| 6 | command: written after an index of 0x82 on selector 0 | below |

Index 4 and 5 are never used with the colour map by shipped code. Index 7 is not used at all.

## Bank select (Bt479 variant)

Established as a sequence, role inferred. To change which of four 256-entry banks selectors 0 and 1 address, software writes
selector 0 with the value 0x82, then selector 6 with a bank value, then returns to selector 0 with the palette index.
`initBt479` writes the bank values 0x00 (the real palette), 0x10, 0x20 and 0x30 (each followed by 256 entries of zero); the
mapcolor routine writes 0x0f; the readback routine writes (bank << 4) | 0x0f for banks 0 to 3. The low nibble and what the two
values (0x0f against 0x00) do: **unknown**. The PROM's colour-set routine writes 0x3f for the Bt479 variant.

At the end of `initBt479` the first loop writes selector 0 = i then selector 6 = 0 for i in 0 to 0x7f (clears 128 registers
at those addresses; role **unknown**), then a command word written three times in a row to selector 6 after selecting address
0x82: 0x00, then (monitor argument << 3) | 2, where the argument is 1 unless the monitor type (bits 5:3 of the `WCLOCK`
read) is 6, then 0x00 twice. Which command bits do what: **unknown**.

The default palette is 256 entries of red, green, blue bytes taken from three consecutive 256-byte arrays in the driver's data
(red, then green, then blue at +0x100 and +0x200), with the entries on a repeating grayscale/colour-cube pattern; `initBt479`
and `initLUT1` both load it. The table is not reproduced here (the PROM carries its own, loaded by its colour routines).

## LUT1 variant (revision 2 and up)

Established as a sequence, role inferred. `initLUT1` selects index 6, stores one byte (2 if the monitor type is 6, otherwise 3)
through the GO alias only (this variant accepts the byte there without a prior SET store), then index 0 = 0, index 1 and writes
256 x 3 bytes. `lg2_mapcolor` reads index 6, masks it with 0x3f (clearing the top two bits, the bank), writes it back, sets the
index through selector 0, writes red, green, blue through selector 1 and 0xff to selector 2. `light_read_lut_colormaps` selects
bank n by writing (n << 6) | monitor flag | 2 to selector 6, then selector 3 = 0, then reads 0x300 bytes from selector 1.
So in this variant selector 6 bits 7:6 pick the bank and bit 1 is always set when reading; the roles of bit 0 and bit 1
beyond that: **unknown**.

## qtest hooks

A register-contract test for a model can check: after `CONFIGSEL` 0 <- n, three writes to selector 1 and `CONFIGSEL` 3 <- n
with three reads from selector 1, the same bytes come back (inferred: this is what `light_read_bt_colormaps` assumes); the
GO alias must not change a read value that was latched by the previous GO read (unknown, not tested by software).

## What NetBSD does

For the Bt479 NetBSD's `light.c` does not program the colour map at all; it relies on the PROM's tables and only changes the
VC1 SYS_CTL byte and fills the screen. A model that matches NetBSD therefore needs only `RWVC1`; the colour map matters for
the PROM console's visible colours and IRIX.
