# Colour-map banks on the Entry board (Bt479 variant)

How IRIX 5.3 loads and reads the colour map's four banks, what lives in each, and what a model has to keep. The access protocol
for a single palette entry is on the [colour map page](README.md); which bank a pixel is displayed through is decided by the VC1 and is
on [VC1: display IDs and the mode table](../vc1/did-xmap.md).

Grades and tags follow [AGENTS.md](../../AGENTS.md) and the note on the [display ID page](../vc1/did-xmap.md): **[binary]** is read in a
shipped object with function and address, **[hdr]** is a name or value from the shipped `sys/lg1hw.h`, **[inferred]** gives its basis.
Kernel addresses are byte offsets into the named member of the IRIX 5.3 `IP20boot/lg1.a`; X server addresses are virtual
addresses in the 5.3 `lg1mc.so`. **No Bt479 data sheet is held** (Library searched by part name and by "Brooktree"; nothing under
`docs/library/cache`), and the public OpenBSD `grtwo.c` and `grtworeg.h` use the Bt479 only on the Express board through a different
interface. So every statement about what the part does internally is **unknown**; what follows is what software writes and expects back.

## The access bank

- **Established.** To address bank n the program writes selector 0 with 0x82, then selector 6 with `(n << 4) | 0x0f`, then selector
  0 with the first palette index and streams red, green, blue bytes through selector 1 (the index advances after every third byte).
  Banks 0 to 3 give selector-6 bytes 0x0f, 0x1f, 0x2f, 0x3f. Read from `rexSetColor` (0x5e31951c, bank 0 only), `rexStoreNormalColors`
  (0x5e306eb8, `(bank << 4) | 0x0f` with the bank taken from the hardware-map table), `rexStorePupColors` (0x5e306588, bank 3), the
  cursor colour routine at 0x5e308640 (bank 3), X `bt479Init` (0x5e31b308, all four banks in turn and a final 0x0f), and the kernel's
  `light_read_bt_colormaps` (`light.o` +0x16bc, reads bank n by `(n << 4) | 0x0f`, then selector 0 = 0x82 again, then selector 3 = 0
  and 768 bytes from selector 1, for n = 0 to 3). The kernel's own `initBt479` (`light_init.o` +0x25c) uses 0x00, 0x10, 0x20, 0x30
  (no low nibble) and clears banks 1 to 3 to zero.
- **Established** (X `bt479Init`, whole store sequence traced): after the 128-address clear loop the X server writes address 0x82 with
  selector-6 byte 0x0f, address 0x84 with two selector-6 bytes 0x00, 0x00, the pixel mask 0xff through selector 2, then the four banks
  in turn, ending with 0x82 / 0x0f. The kernel's `initBt479` writes 0x82 followed by four consecutive selector-6 bytes (0x00,
  `(monitor argument << 3) | 2`, 0x00, 0x00). **Inferred**: addresses 0x82 to 0x85 are four control registers, each selector-6 write
  stores into the one the address register names and then advances the address, so the server's second write (0x84) leaves the
  monitor-dependent byte at 0x83 alone. The model must therefore treat a selector-6 write as "control register at address register",
  not as "set bank" unconditionally.
- **Inferred** that bits 5:4 of control register 0x82 pick the bank that selectors 0, 1 and 3 reach (the access bank): the readback
  routine depends on it, and the X server restores 0x0f (bank 0) after every temporary use. **Inferred** that it is not the bank
  being displayed: the server loads banks 1 to 3 while windows that use bank 0 are on screen, and no write order can keep both
  correct if one global field chose both. The low nibble 0x0f (kernel: 0x00): role **unknown**.
- On the LSI LUT1 variant (board revision 2 and up) the same bank sits in selector 6 bits 7:6 with no 0x82 step: rexStoreNormalColors
  (0x5e3070a4) ORs `bank << 6` into the low nibble it read back, and the cursor colour routine ORs 0xc0.

Model rule: keep `bank[4][256][3]`; remember the access bank from selector-6 writes made while the address register is 0x82 (bits 5:4),
and select it for palette writes, reads and the read address until the next such write. Reset it to 0.

## Where each bank is used

All **established** from the X server functions named, except where marked.

| Bank | Index range written | Written by | What it is |
|---|---|---|---|
| 0 | 0 to 255 (8-bit visual: the loop count is 1 shifted left by the visual's plane count, 256) | `rexInstallNormalMap`, `rexStoreNormalColors`, `rexSetColor`, `bt479Init` | default coloured map; hardware maps 0 and 3 |
| 1 | 0 to 255 | `rexStoreNormalColors` | hardware map 1 |
| 2 | 0 to 255 | `rexStoreNormalColors` | hardware map 2 |
| 3 | 0x10 up: 16 pop-up colours (pixel + 0x10) | `rexStorePupColors` (0x5e306588, address `pixel + 16`, bank 3) | pop-up and overlay colours, hardware map 4 |
| 3 | 0x21, 0x22, 0x23 | cursor colour routine (0x5e308640) | hardware cursor colours, see [cursor](../vc1/cursor.md) |
| 3 | pixel + 0x30 and pixel + 0x40 | `rexStoreNormalColors`, hardware maps 5 and 6 (table byte 0x33 and 0x43) | two further bank 3 maps |

The hardware-map byte table is on the [display ID page](../vc1/did-xmap.md#initial-entries). A count of 34 entries in bank 3 and of 255 in banks
0 to 2, seen in an emulator trace, is not what the loops read here give: the 8-bit install loop runs 1 << nplanes = 256 times, and the bank-3
writers address 0x10 to 0x1f, 0x21 to 0x23 and, for hardware maps 5 and 6, 0x30 or 0x40 plus the pixel. **Unknown** whether one entry is
skipped or the trace drops the last write; logging the address register at the start of each run of selector-1 writes would show it.

Index: the store routines write `pixel + offset`, with `offset` the high nibble of the hardware-map byte (0 for hardware maps 0 to 4,
0x30 or 0x40 for maps 5 and 6), and the pop-up routine adds a fixed 0x10 (hardware map 4, whose initial mode word 0x030d carries
offset 0). So a model that indexes the palette by pixel alone is wrong for those windows. Applying the mode word's bits 7:4 (display
ID page) fixes maps 5 and 6. For the pop-up map it is **unknown** whether the pixel is 4 bits wide with the 0x10 supplied by the chip
or by a plane group (`AUX2` bits 31:29 = 2 is the overlay plane group [hdr]), or whether the hardware adds a fixed 0x10 for bit-0 mode
words.

## Why a bank-0-only model looks wrong

- The default X colour map is hardware map 0, bank 0; the 4Sight reserved colours and the grey ramp are loaded into hardware maps 1
  and 2 (banks 1 and 2). A model that shows bank 0 for every window shows the grey ramp's pixel values through bank 0's coloured entries:
  blue and cyan tones. **Inferred** (no run was read; this is the consequence of the tables above).
- Black root and blank icons are the same cause: pixels in a window whose map is in bank 1, 2 or 3 index entries that bank 0 either
  does not hold or holds as black (the kernel writes zeros to banks 1 to 3 before the server loads them). **Inferred.**
- Writing the banks correctly (the access-bank rule above) and displaying them through the per-window mode word are two fixes; the
  first alone makes `light_read_bt_colormaps` return the right bytes and changes nothing on screen.

## qtest hooks

- Write 0x82 to selector 0, 0x1f to selector 6, index 5 to selector 0 and bytes 1, 2, 3 to selector 1; then 0x82, 0x0f, and
  index 5 with three bytes 9, 9, 9. Read back bank 1 (0x82, 0x1f, selector 3 = 5, three reads) and bank 0: 1, 2, 3 and 9, 9, 9.
- A selector-6 write with the address register at 0x84 must not change the access bank.
- After reset the access bank is 0 and the pixel read mask (selector 2) is whatever the program writes; no shipped code reads it.

## Open

- The Bt479's own bank/window mechanism (data sheet needed): whether the part has four palettes natively, how many bank pins it has,
  and what control register bits 3:0 do.
- How pop-up pixels reach bank 3 entries 0x10 and up (above).
