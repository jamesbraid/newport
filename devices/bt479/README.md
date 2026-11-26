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
| 2 | pixel read mask, written 0xff (`initBt479` writes it before the palette; `lg1_mapcolor` after) | `initBt479`, `lg1_mapcolor` |
| 3 | read address; a write of 0 before a palette read | `light_read_bt_colormaps` |
| 6 | command: written after an index of 0x82 on selector 0 | below |

Index 4 and 5 are never used with the colour map by shipped code. Index 7 is not used at all.

## Bank select (Bt479 variant)

Established as a sequence, role inferred. To change which of four 256-entry banks selectors 0 and 1 address, software writes
selector 0 with the value 0x82, then selector 6 with a bank value, then returns to selector 0 with the palette index.
`initBt479` writes the bank values 0x00 (the real palette), 0x10, 0x20 and 0x30 (each followed by 256 entries of zero); the
mapcolor routine writes 0x0f; the readback routine writes (bank << 4) | 0x0f for banks 0 to 3. The low nibble and what the two
values (0x0f against 0x00) do: **unknown**. The PROM's colour-set routine (0xbfc2d4e8) writes 0x0f on the Bt479 path, as `lg1_mapcolor` does; 0x3f is the mask `lg2_mapcolor` applies on the LUT1 path. On the LUT1 path the PROM writes (monitor flag | 2) to selector 6.

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

The four banks, which program loads which, and the bank-select rule the model needs are on [Colour-map banks](banks.md).

## Power-on read-back test (PROM 4.0.5G, `0xbfc07660`)

The 4.0.5G PROM fills one colour-map bank with a byte and reads it back, as the last part of its Entry-board power-on test; the 4.0.5D image has no such code (no "Bt479 power on test failed" or "Error reading from" text). **Established** from the routine at `0xbfc07660`, read in full in the 4.0.5G image (070-8116-005), and from the loop that calls it at `0xbfc063ec` to `0xbfc06408`. The call order, what skips it and how a failure is reported are on the [REX1 page](../rex1/README.md#the-405g-power-on-test-code-reading-established-binary-405d-has-none).

- **Calls.** One call per pattern, map number 0, pattern 0x55 and then 0xaa (the loop adds 0x55 until it reaches 0xff). The routine returns the number of mismatched bytes, and the caller adds them up.
- **Control value.** It reads the board revision and monitor-type bytes that the probe stored in the PROM's board record. Revision below 2 (this page's Bt479): `CONFIGSEL` 0 and 0x82 to `RWDAC` and its GO alias, then the control value `(map << 4) | 0xf`, which is 0x0f for map 0. Revision 2 and up: no 0x82 step, and the control value is `(map << 6) | sync | 2` with `sync` = 1 unless the monitor type is 6.
- **Write.** `CONFIGSEL` 6: control value to `RWDAC` and the GO alias. `CONFIGSEL` 0: 0 to both (palette address 0). `CONFIGSEL` 1, then 256 times three SET and GO store pairs of the pattern byte (red, green and blue of one entry), so all 256 entries of the selected bank hold the pattern in all three channels.
- **Read-back.** Revision below 2: the 0x82 step again. `CONFIGSEL` 6: the same control value. `CONFIGSEL` 3: 0 to both (read address 0). `CONFIGSEL` 1, one GO read whose value is dropped (the `light_read_bt_colormaps` pattern), then 256 times a SET read and a GO read three times over. Only the GO read of each pair is kept: the SET read lands in the same byte and is overwritten. The 768 kept bytes are compared with the pattern as whole bytes (all 8 bits); each mismatch logs "Error reading from (red|green|blue) DAC address ..." at level 2 and counts one (not printed during the power-on dispatch, see the [call order](../rex1/README.md#the-405g-power-on-test-code-reading-established-binary-405d-has-none)).
- **What a model returns to pass.** Every one of the 768 GO reads must return the pattern byte written to the bank the control value selected (bank 0 for both writes and reads), so an 8-bit-wide palette store with the three-byte auto-increment of the write address, and a read address that starts at 0 after a write of 0 to `CONFIGSEL` 3. The SET reads are never compared. Because every entry holds the same byte, the test cannot tell addresses, the read pipeline's one-byte offset or an extra address step on a SET read apart: a model that is off by one entry still passes. It does fail a store narrower than 8 bits (0x55 and 0xaa are complementary) and a palette read that returns anything but the stored data.
- **State left behind.** Bank 0 holds 0xaa in every entry and the control byte is the value above; the test restores nothing, and the PROM's later colour set-up is what reloads the palette (**inferred**: the colour routines load tables and no code was seen reading the test's leftovers).

The ide diagnostic's full colour-map test (`btdactest` in `stand/arcs/ide/fforward/graphics/LIGHT/btdac.c`, **[source]**) runs the data bytes 0, 0x55 and 0xaa over maps 0 to 3; the PROM runs map 0 with 0x55 and 0xaa only.

## qtest hooks

A register-contract test for a model can check: after `CONFIGSEL` 0 <- n, three writes to selector 1 and `CONFIGSEL` 3 <- n
with three reads from selector 1, the same bytes come back (inferred: this is what `light_read_bt_colormaps` assumes); the
GO alias must not change a read value that was latched by the previous GO read (unknown, not tested by software).

## What NetBSD does

For the Bt479 NetBSD's `light.c` does not program the colour map at all; it relies on the PROM's tables and only changes the
VC1 SYS_CTL byte and fills the screen. A model that matches NetBSD therefore needs only `RWVC1`; the colour map matters for
the PROM console's visible colours and IRIX.
