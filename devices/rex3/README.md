# REX3 raster engine (Indy and Indigo2 Newport graphics)

REX3 is the drawing chip of the Newport graphics board in the Indy (IP24) and the Indigo2 (IP22). It draws into the frame buffer,
passes host pixel data through the `HOSTRW0` and `HOSTRW1` ports, and reaches the video controller, colour maps and DAC through a
display control bus (`DCBMODE`, `DCBDATA0`, `DCBDATA1`). This directory is a stub: the register map has not been written. What exists
is the part a software author needs first, how the host reaches the chip, and the way the Newport board changes between its 8-bit
and 24-bit builds.

Grades follow [AGENTS.md](../../AGENTS.md).

| Page | Covers |
|---|---|
| [byte-lanes.md](byte-lanes.md) | Which bytes of a word the chip takes for register, display-bus and pixel-port writes, what the Indy and Indigo2 memory controller does to them, and what a little-endian CPU must do |
| [../xmap9/README.md](../xmap9/README.md) | The XMAP9 mode and overlay mapper: configuration register, mode table, pixel formats |
| [../../platforms/newport/README.md](../../platforms/newport/README.md) | The board: how software finds the frame-buffer depth, and what an XL24 changes against an XL8 |

LG1's REX1 is a different chip; see [REX1](../rex1/README.md) and the lineage notes in the [top README](../../README.md#rex1-and-rex3).
