# REX3 host pixels: HOSTRW packing and the X server's image paths

How host pixel data is packed into the `HOSTRW0` and `HOSTRW1` ports at each depth, what `RWPACKED` changes, and how the IRIX X server
uses the packed format for image puts and gets. Scope: REX3 on the Indy and Indigo2, big-endian CPU. The little-endian question is on
[byte lanes](byte-lanes.md#the-little-endian-question) and is not answered here.

Grades follow [AGENTS.md](../../AGENTS.md). Review 2026-11-27. Sources: the REX3 Specification, revision 1.0, 13 August 1993 (sections
3.1.1.1, 3.1.1.2 and 3.10; the packing table on page 79 is a figure, read from a 400 dpi rendering), the IRIX 6.5 base media `ng1.so`
(`rex3DrawImage`, `rex3DrawImage12`, `rex3DrawImage24`, `rex3ReadImage`, `rex3ReadImage12`, `rex3ReadImage24`) and the IRIX 6.5.7 ide
diagnostics already cited on the byte-lane page. Nothing was run.

## Registers

**Established** (specification, `DRAWMODE1` at 0x0000, `DRAWMODE0` at 0x0004, `HOSTRW0` at 0x230, `HOSTRW1` at 0x234; the same offsets
at +0x800 are the GO alias that also starts the primitive):

| Field | Where | Meaning |
|---|---|---|
| `RWPACKED` | `DRAWMODE1` bit 7 | pack several pixels in one `HOSTRW` word (clear: one pixel per word) |
| `HOSTDEPTH` | `DRAWMODE1` bits 9:8 | host pixel depth: 0 is 4 bits (1-2-1 BGR, or 4-bit colour index), 1 is 8 bits (3-3-2 BGR or colour index), 2 is 12 bits (4-4-4 BGR or colour index), 3 is 32 bits (8-8-8-8 ABGR) |
| `RWDOUBLE` | `DRAWMODE1` bit 10 | use both `HOSTRW0` and `HOSTRW1` as one 64-bit transfer |
| `SWAPENDIAN` | `DRAWMODE1` bit 11 | reverse the bytes of 16-bit and 32-bit packed data |
| `DRAWDEPTH` | `DRAWMODE1` bits 4:3 | depth of the frame-buffer planes drawn: 0 is 4, 1 is 8, 2 is 12, 3 is 24 bits |
| `COLORHOST`, `ALPHAHOST` | `DRAWMODE0` bits 6, 7 | take colour (alpha) from `HOSTRW` instead of the shading hardware; required for writes |
| `PREFETCH` | `DRAWMODE1` bit 26 | read-ahead for pixel programmed-I/O reads (must be 0 for pixel DMA reads) |

The data layout inside a field: "each value resides in a field of 8, 16 or 32 bits as programmed by `HOSTDEPTH`; the leftmost field is
the first one to be used; each value is right-aligned within the field and zero-filled". Colour components are ordered red least
significant, then green, then blue (or alpha) most significant. Reads return undefined values for start-byte masked locations and for
unused trailing fields. **Established** (specification section 3.10).

## Packing per depth

**Established** as the published figure ("big endian format illustrated"; the figure has no little-endian counterpart). The
`RWDOUBLE` clear rows occupy `GIO_DATA(31:0)`. The specification names `HOSTRW0` the most significant word and `HOSTRW1` the least
significant, yet says a 32-bit access uses only `HOSTRW0`, and does not say how the two statements fit; this page takes the 32-bit rows as
the word a program reads and writes at `HOSTRW0` (**inferred**, and the X server does exactly that). Bit positions below are within that word. The figure
is an 8-cell strip with one shaded region per case; the cells are bytes, so within a byte a half-cell shading is a nibble.

32-bit transfer (`RWDOUBLE` 0), `HOSTRW0` bits:

| `HOSTDEPTH` | `RWPACKED` clear: one pixel | `RWPACKED` set |
|---|---|---|
| 0 (4-bit) | bits 27:24 (low nibble of the top byte) | four pixels, one per byte, each in the low nibble of its byte: 27:24, 19:16, 11:8, 3:0; first pixel in the top byte |
| 1 (8-bit) | bits 31:24 | four pixels, bytes 31:24, 23:16, 15:8, 7:0, first pixel in the top byte |
| 2 (12-bit) | bits 27:16 | two pixels, each in a 16-bit field with the 12 bits right-aligned: 27:16 then 11:0, first in the upper halfword |
| 3 (32-bit) | bits 31:0 | the same: one 32-bit pixel (A in 31:24, B 23:16, G 15:8, R 7:0) |

64-bit transfer (`RWDOUBLE` 1): the unpacked pixel sits in `HOSTRW0` (the high word) at the same positions as above (4-bit in 59:56, 8-bit
in 63:56, 12-bit in 59:48, 32-bit filling 63:32), and `HOSTRW1` is not used. With `RWPACKED` set the same packing fills the whole 64
bits: eight 4-bit pixels (one per byte, low nibble), eight 8-bit pixels, four 12-bit pixels in 16-bit fields, or two 32-bit pixels
(`HOSTRW0` first, then `HOSTRW1`).

So four pixels fit in a word at 4 and 8 bits, two at 12 bits and one at 32 bits. A packed 4-bit pixel does not share a byte with its
neighbour: the 4-bit case uses 8-bit fields. An earlier version of the byte-lane page said a packed 4-bit word held eight pixels in
nibbles; the figure and the field rule above contradict that, and the page is corrected.

Evidence the drivers agree, **established** as expectations: the ide diagnostics and the PROM's depth probe use the unpacked
positions (8-bit in 31:24, 12-bit in 27:16), and the probe writes two 12-bit pixels as one word `0xabc << 16 | 0xdef` and reads back
`0x0abc0def` ([board page](../../platforms/newport/README.md#how-software-finds-the-depth)), which is the packed 12-bit layout.

## How the X server uses it

**Established** for what is written (disassembly of `ng1.so` from the 6.5 base media: `rex3DrawImage` at 0x5e897ccc, `rex3DrawImage12`
at 0x5e9545b8, `rex3DrawImage24` at 0x5e8de534, `rex3ReadImage` at 0x5e8dc554, `rex3ReadImage12` at 0x5e953ca0, `rex3ReadImage24` at
0x5e954d44).

- All six routines OR `RWPACKED` (0x80) into the `DRAWMODE1` value, on top of a base word at offset 20 of a per-format record (reached
  through a table at offset 0x84 of the screen record) and a logical-operation nibble shifted to bits 31:28. `HOSTDEPTH` and `DRAWDEPTH` come from that base word, so no
  X server path was seen to set the host depth directly. Which base word each visual gets was **not traced**; that the 24-bit routines use
  `HOSTDEPTH` 3 and the 12-bit routines `HOSTDEPTH` 2 is **inferred** from their data movement below.
- Image put: `DRAWMODE0` is **0x46** (opcode DRAW, `ADRMODE` block, `COLORHOST`). The routine writes `XYSTARTI` (0x150) and `XYENDI` (0x154) as
  packed X and Y, loads `WRMASK` (0x220), writes 0 to 0x120 (`BRESOCTINC1`), then stores pixel words to `HOSTRW0` at the GO alias **0xa30**.
  One store per word, one primitive per store.
- 24-bit put: each source word (one 32-bit pixel, 4 bytes per pixel in the server's pixmap) is copied unchanged to 0xa30, four words
  at a time. So the server's 24-bit pixels are already in the host layout above (red in the low byte). **Established** for the copy;
  the pixel byte order of the server's memory follows from the layout and is **inferred**.
- 12-bit put: the source rows are 16 bits per pixel; words are rebuilt with 16-bit shifts and masks so that the first pixel of a row lands
  in the upper halfword however the row starts, matching the packed 12-bit layout.
- 8-bit put: source bytes are re-aligned into words with variable shifts chosen from the low two bits of the start address, four pixels
  to a word, first pixel in the top byte.
- Image get (`rex3ReadImage`, `ReadImage12`, `ReadImage24`), small transfers: `DRAWMODE0` is **0x45** (opcode READ, block, `COLORHOST`) and
  `DRAWMODE1` also has `PREFETCH` (0x04000000) set. The routine writes a dummy word, 0xdeadbeef, to the `HOSTRW0` GO alias first; the
  specification's setup rule is a write to GO to prefetch, then reads of `HOSTRW` with GO. Large reads use `DRAWMODE0` 0x145 (adds
  `STOPONX`) with `PREFETCH` clear, which is the specification's rule for pixel DMA reads, and go to the kernel.
- Size split: every routine compares a byte count (width times height times 1, 2 or 4 bytes a pixel for the 8-, 12- and 24-bit routines).
  Puts of 16384 bytes or more (16384, 8192 or 4096 pixels) and gets of 7000 bytes or more (7000, 3500 or 1750 pixels) go through kernel
  request 21002, which the kernel handles in `Ng1PixelDma` (a 32-byte argument). Smaller transfers are the programmed-I/O stores above.
  **Established** for the thresholds as code.

## Open

- **Which base word each visual uses.** The per-visual `DRAWMODE1` base (and so `HOSTDEPTH`) was not traced in `rex3Init` and the visual
  setup. Would settle it: decode where the per-format records (offset 20, reached through the screen record's table at 0x84) are filled, or the X server's 24-bit visual setup,
  and compare with the diagnostics' table on the [XMAP9 page](../xmap9/README.md#the-visuals-the-irix-diagnostics-program).
- **64-bit host transfers.** No shipped software was seen using `RWDOUBLE` from the CPU (the kernel and X server use only word stores
  and the DMA path is not decoded here). Which register a half lands in on a little-endian 64-bit store is on the byte-lane page.
- **`SWAPENDIAN` on the host port.** Used by the ide DMA test only; no X server path sets it.
