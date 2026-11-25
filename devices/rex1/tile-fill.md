# REX1 tile fill: command 0x00200121

How the X server fills a rectangle with a four-pixel-wide tile, and what the chip has to do with the one data word per row. Register
layout and the other commands are on the [REX1 page](README.md) and the [register list](registers.md); the board context is the
[LG1 page](../../platforms/lg1/README.md).

Grades follow [AGENTS.md](../../AGENTS.md). **[binary]** is read in a shipped object, with address; **[hdr]** is a name from the
shipped header `sys/lg1hw.h` (IRIX 4.0.5F, revision 1.27, public mirror; names and values only); **[source]** is the IRIX source tree,
cited by path; **[inferred]** says what it rests on. The addresses are virtual addresses in the IRIX 5.3 `usr/lib/X11/dyDDX/lg1mc.so`
(checksum in [irix-files.md](../../references/irix-files.md)). `rexTileRects` was read from its first instruction to the end of its
four-pixel path; the later paths were read as far as their register stores. Nothing was run.

## The command word

0x00200121 is `COLORAUX | QUADMODE | STOPONX | DRAW` (**[hdr]** names, established as names; the effects are inferred):

| Bit | Value | Header name | Reading |
|---|---|---|---|
| 0 | 0x1 | DRAW (opcode 1) | draw |
| 5 | 0x20 | QUADMODE | four pixels per data word |
| 8 | 0x100 | STOPONX | the run ends at `XENDI`, inclusive |
| 21 | 0x200000 | COLORAUX | the pixel word comes from `RWAUX1`, not from the colour registers |
| 31:28 | 0 | logic operation | empty; the X server supplies it through `XSTATE` bits 27:24 |

Not set: BLOCK (3, so no second row), XYCONTINUE (7, so the run starts at `XSTARTI`/`YSTARTI` and not where the last command
stopped), STOPONY (9), ENZPATTERN (10) and every line, shade, dither and opaque flag. It is the solid-span command 0x121 (`CMD_SPAN`)
plus COLORAUX: **one horizontal run on one row per execution**. The kernel never issues it: a pair scan of the five `lg1.a` members
for a `lui 0x20` / `ori 0x121` pair found none (**inferred**; not a full read of those objects). In 6.5's `lg1mc.so` the same
constant is built at two places (0x5f0eff60 and 0x5f18f3a8).

## The register sequence

`rexTileRects` (`lg1mc.so` 0x5e312008, called with the rectangle list, a count, the tile row data and its byte stride, the tile
width and height, the tile origin, the raster operation, the plane mask and the screen record). **[binary]**

When the tile width is exactly 4 pixels it draws with the hardware, as below. Any other width (the code compares the width with 4
at 0x5e31207c) is cut into chunks and handed to a per-screen function pointer that is not the tile command (0x5e31232c onward;
the pointer is loaded at 0x5e312078 through the board record, and the chunk calls pass the operation, mask and screen), so **only
four-pixel tiles reach this command**. The pointer's target was not identified; the chunk loops are consistent with image writes
from host memory, so larger tiles are **inferred** to be drawn as ordinary images.

Setup, once per call (0x5e31209c to 0x5e312158):

1. `AUX1` (0x4) = 0x28, or 0x2c, but only when a flag in the screen record (bit 31 of its word at +0x18) is set and the board
   record's copy of the board-info +0x2c word is 1 (0x28) or -1 (0x2c). Otherwise `AUX1` is not written here. In the header's names
   0x28 is DOUBLEBUF and DBLDST1 and 0x2c adds DBLDST0 (**[hdr]**; role **inferred**: draw into a double-buffered destination). When
   the word is 1 the plane mask is also shifted right by 4 (a four-plane buffer); for -1 it is not.
2. `COMMAND` (0x0) = 0x00200121.
3. `XSTATE` (0x8) = (plane mask & 0xff) << 16 | (operation << 24) | 0x10000000: plane mask in bits 23:16, the X raster operation (0
   to 15, replace is 3) in bits 27:24, and **bit 28 set**, the header's XSTATE_COLORAUX (the state copy of command bit 21; **inferred**).
   The colour field (7:0) is 0 and unused.
4. `AUX2` (0x47a8) = group << 29, group from the window's record (1, the pixel planes, for an ordinary window; see
   [plane groups](../../platforms/lg1/desktop-and-overlays.md#plane-groups)).

Per rectangle (the record is x1, y1, x2, y2 as halfwords, x2 and y2 exclusive; 0x5e31217c to 0x5e3122fc):

5. `XSTARTI` (0xc) = x1, `XENDI` (0x84) = x2 - 1. **Stored once for the rectangle.**
6. For each row y1 to y2 - 1: `YSTARTI` (0x1c) = y, then **one 32-bit store of the tile word at `RWAUX1` GO (0x870)**, which runs the
   command. `YENDI` is never written on this path.
7. After the last rectangle `AUX1` (0x4) = 0.

The tile word for each row is built in software (0x5e312228 to 0x5e3122d0): the row `(y1 + row - origin y) mod tile height` of the tile data
is read as a big-endian 32-bit word (an unaligned read is assembled from two words with masks), then rotated **left by
`(x1 - origin x) mod 4` bytes** with the modulus taken non-negative. The rotation moves tile pixel `(x1 - ox) mod 4` into the top byte.

## What that says about the hardware

- **Repeat.** Software stores one word per row however wide the rectangle is (a full-width desktop fill is one word per row for 1024
  pixels). So the engine applies the same four pixels over the whole run from `XSTARTI` to `XENDI`: pixel `k` of the run (x =
  `XSTARTI` + k) takes byte `k mod 4` of the word, byte 0 being bits 31:24. **Inferred** (nothing else would make the output right);
  the byte order is the same first-pixel-in-the-high-byte rule as PutImage and the pixel-memory probe.
- **Phase.** Relative to `XSTARTI`, not to the absolute x: the rotation amount depends on the rectangle's left edge, and with an
  absolute phase it would depend on the origin alone. **Inferred**; a model that keys the byte on `x & 3` shifts every tile whose
  left edge is not a multiple of 4.
- **Row step.** None in hardware. The engine does not advance y after a run and does not consume `XSTARTI` or `XENDI`: the next row
  is `YSTARTI` plus another word store, with the x registers as they were. A model that moves `XSTART` to `XENDI` + 1 after a run
  must reload it from `XSTARTI` when the next command is not XYCONTINUE. **Inferred** from the store pattern.
- **Plane mask.** The mask is `XSTATE` bits 23:16 (replace 0xff shifted down by 4 on a double-buffered board). `RWMASK` is not
  written on this path, nor anywhere else by the X server; it is the 0xff left by the board-info routine in the PROM and the kernel,
  so it neither blanks the fill nor masks any plane. The ide graphics shell's write-mask command loads `RWMASK`
  (`stand/arcs/ide/fforward/graphics/LIGHT/minigl.c`, **[source]**), which is why the low byte is read as the pixel write mask.
  Applying it as a write mask is harmless for every shipped sequence; resetting it to 0 and applying it is not.
- **Logic operation.** The command's own nibble is 0, which is clear (`REX_LO_ZERO`) if it were used. The operation therefore has
  to come from `XSTATE` 27:24 whenever the command nibble is 0 (as for 0x329, 0x80329 and the other X commands); a non-zero command nibble (PutImage,
  the kernel's 0x30000329) is used as it stands. **Inferred.**
- **Colour.** None of `COLORREDI` and `XSTATE` 7:0 takes part: every pixel comes from the data word. A model that fills the span
  with a colour register or with the first byte alone draws solid colour where a 4-pixel pattern is meant.

## What a model should do and how to test it

For the command 0x00200121 at `COMMAND` and a store at `RWAUX1` GO (0x870): draw one row, `YSTARTI`, from `XSTARTI` through
`XENDI` inclusive; pixel k = byte `k mod 4` of the word counting from the most significant byte; combine with the destination by
the operation in `XSTATE` 27:24, limited to the planes in `XSTATE` 23:16, in the plane group `AUX2` 31:29; leave all coordinate
registers unchanged. Discriminating checks:

- `XSTARTI` 1, `XENDI` 9, `YSTARTI` 2, `XSTATE` 0x13ff0000, `AUX2` 0x20000000, store 0x0a0b0c0d at 0x870: row 2 holds, from x = 1,
  0a 0b 0c 0d 0a 0b 0c 0d 0a, and no other pixel changes.
- Then `YSTARTI` 3 and store 0x01020304: row 3 holds 01 02 03 04 01 02 03 04 01 from x = 1 (the x registers were not reloaded).
- The same with `XSTATE` 0x11ff0000 (operation 1, AND) over a destination of ff: the pixels become the data bytes; with `XSTATE`
  0x110f0000 only the low four planes of each pixel change.

## Open

- Which board-info word and screen flag select `AUX1` 0x28 or 0x2c, and what DOUBLEBUF with a destination bit does on a board that
  is not double buffered (the model may ignore `AUX1` and write the displayed buffer).
- Whether the hardware repeats at the data word or at quad alignment when `XSTARTI` is not a multiple of 4 (the software never
  relies on quad alignment here, which is why the phase is read as relative to `XSTARTI`).
- Whether the operation really comes from `XSTATE` only when the command nibble is 0, or `XSTATE` is merged with the command
  in another way; all shipped commands are consistent with either.
