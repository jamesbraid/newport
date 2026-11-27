# Newport: the Indy and Indigo2 graphics board, 8-bit against 24-bit

The Newport board in the Indy (IP24) and the Indigo2 (IP22): a REX3 raster engine, a VC2 video controller, two XMAP9 mode mappers,
two CMAP colour maps, a Bt445 DAC and VRAM, in an 8-bit-plane build and a 24-bit-plane build. This page covers how software finds
the depth and what a 24-bit board changes for software against an 8-bit one. It is the board-level account; chip detail is on
[REX3](../../devices/rex3/README.md) and [XMAP9](../../devices/xmap9/README.md). The Indigo's Entry board is a different design: see
[LG1](../lg1/README.md).

Grades follow [AGENTS.md](../../AGENTS.md). Review 2026-11-27. Sources: the IRIX 6.5.7 source tree's PROM library
(`stand/arcs/lib/libsk/graphics/NEWPORT/ng1_init.c`) and ide diagnostics (`stand/arcs/ide/fforward/graphics/NEWPORT/`), read for
the functions named; the IRIX 6.5 base media IP22 kernel archive `ng1.a` (all six members, `newport_init.o` read for the XMAP9 and depth code) and the X server
module `usr/lib/X11/dyDDX/ng1.so`, from the same disc as the hashes in [irix-files.md](../../references/irix-files.md); the REX3,
XMAP9 and RO1 specifications; the Linux v7.2-rc7 and NetBSD Newport drivers. Nothing was run on a board. The colour-map
specification is not held and the Bt445 specification is an image-only scan that was not read, so statements about those two rest on
software.

## Names

- **Established** (PROM source): the console component identifier is `SGI-Indy 24-bit` or `SGI-Indy 8-bit` on an Indy, chosen by
  the detected plane count, and `SGI-XL` on an Indigo2 whatever the plane count. The monitor id is read from the second colour map.
- The shipped `hinv` carries the format `Indy %d-bit`; how it names an Indigo2 board was not read. The names XL8 and XL24 appear in
  no string, manual page or release note searched under the IRIX 6.5 base media (a text search of `hinv`, the catman pages and the
  release notes); they are owner and dealer usage, not software names. Whether a board sold as XL24 is the PROM's 24-bit board on
  every machine is **unknown**.

## How software finds the depth

**Established** (PROM source `Ng1InitInfo`, `getfbdepth`, `ng1_install`, read in full; the kernel's `fbdepth` and the NetBSD and
Linux probes match):

| Machine | Rule |
|---|---|
| Indy (the PROM's non-Indigo2 branch) | Read colour map 0's revision register (display-bus address 2, register 6, one byte). Bits 2:0 are the colour-map revision, **bits 6:4 the board revision**, and **bit 7, when the board revision is above 1, means an 8-bit board**; otherwise 24. A board revision of 0 or 1 does not carry the bit, so the depth is found by the write-and-read test below. A second Newport board (index 1) adds 8 to the revision. |
| Indigo2 | The board revision comes from a different source in the machine, and the depth is always found by the write-and-read test. |
| Both, when the revision does not say | Write the 12-bit packed pixel pair `0xabc`, `0xdef` as one `HOSTRW0` word with a 12-bit draw depth, a packed 12-bit host format, a write mask of 0xfff, then read it back through the same port and mask with `0x0fff0fff`; if both 12-bit values survive the board is 24-bit, otherwise 8-bit. |

NetBSD and Linux read colour map 0 only, as the Indy rule (`(boardrev > 1) && (reg & 0x80)` is 8 bits); neither runs the probe.
The shipped kernel has a variable `forced_depth` that overrides the result with 8 or 24 before anything else (**established**, the
first lines of `fbdepth`); who sets it was not looked for.

The XMAP9 configuration is then written with the 8-bit-system bit to match. The PROM's `Ng1XmapInit` calls a helper with 0x01
(24-bit) or 0x05 (8-bit); the helper's body is not in the source tree. The kernel's `initXMAP9` (read in full) stores the same
values as one byte at `DCBDATA0`+3 to each chip: chip 0 with bit 1 clear (the even-pixel chip) and chip 1 with bit 1 set, pop-up on
in both, so 0x01 and 0x03 on a 24-bit board and 0x05 and 0x07 on an 8-bit one, then cursor MSB 0xe7, pop-up MSB 0, a wait for an empty
mode FIFO and mode entry 0. With a flat panel attached the PROM source writes the 8-bit-system, pop-up, Express-video, video-option
bits and RGB map 1 whatever the depth (0xd5 by the specification's bit positions; the macro values are in a header not in the
tree); the kernel ORs 0xd0 into the byte (so 0xd1 or 0xd5 by depth) when a per-board flag is set. **Established** for what is written. **Inferred** (the code path was read in the
disassembly, the function was not read end to end) for the flag's origin: `newportInitInfo` sets the flag to 1 when a non-zero byte in the board's info record (the flat-panel probe's
result: 0 when the panel I2C bus does not answer, 130 or 131 for the two panel types it knows, 255 when it answers but gives no
panel id) coexists with a first word of the chosen video-timing record that has bit 9 set, and to 0 otherwise; `initXMAP9` tests
it. **Inferred** also: that the bit 9 timing flag marks a flat-panel timing, and so that this is the kernel's counterpart of the PROM's
panel case; the 0xd5 value for the PROM is **inferred** from the specification's bit positions.

## What changes between an 8-bit and a 24-bit board

| Item | 8-bit board | 24-bit board | Grade and source |
|---|---|---|---|
| Frame buffer planes | 8 pixel, 2 pop-up (shared with aux), 2 CID | 24 pixel, 8 aux (overlay, underlay, or 4 and 4), 2 pop-up, 2 CID | **established**, REX3 specification feature list and XMAP9 specification |
| Reorganiser chips | one (**inferred**) | three (one per 8 pixel planes) | RO1 specification: "every 8 bit planes require one RO1"; three is **established**, one for the 8-bit board is the same rule applied |
| Frame-buffer bits the XMAP9 reads | pixel bits 7:0 | pixel bits 23:0, aux and pop-up separate | **established**, XMAP9 specification table 2a |
| XMAP9 configuration, bit 2 | 1 | 0 | **established** |
| Pixel sizes in the mode table | 4-bit and 8-bit colour index and RGB, double-buffered 4+4 | adds 12-bit colour index and RGB (double-buffered), 24-bit RGB, RGBA forms, overlay and underlay planes | **established**, specification tables 3d and 3f; the ide diagnostics refuse the 24-bit-only visuals on an 8-bit board |
| Overlay and underlay | none while pop-up is on (the PROM and kernel leave it on) | 8-bit overlay, underlay, or 4+4, through mode-table aux fields | **established** |
| REX3 write mask | `WRMASK` 0xff; the specification says the low bits serve an 8-bit system | 0xffffff, or 0xffff00 for overlay, 0xfff or 0xfff000 for a 12-bit buffer | **established** |
| REX3 depths used | draw depth 8 and host depth 8; RGB mode there is 3-3-2 | draw depth 24 and host depth 32 for true colour (host pixel in bits 23:0, red least significant); 12-bit modes | **established** for the diagnostics' choices, **source** `ng1visuals.c`; REX3 drawing in other depth pairs is not described here |
| PROM clear at start | pop-up planes, then the frame buffer at depth 8 | pop-up planes, then the **overlay planes** (mask 0xffff00), then the frame buffer at depth 24 | **established**, `Ng1RegisterInit`; the PROM console then runs at 8-bit colour index on both (it reprograms draw mode 1 to 8/8 afterwards) |
| XMAP9 mode table at start | all 32 entries are 8-bit colour index (0x400) on both | same | **established**, `Ng1XmapInit` |
| Colour map | 8K entries on both; colour index uses 256-entry maps selected by the mode entry's MSB field | same, plus RGB ramps used by 24-bit and 12-bit RGB modes | **established** from the XMAP9 specification; internals **unknown** (no specification held) |
| VC2 setup | no depth dependence found | same | **inferred**: the PROM's `Ng1VC2Init` was not read in full; a search of the whole file shows the depth field is read only in the detection, XMAP9, clear and naming code |
| Bt445 setup | no depth dependence found | same: the PROM programs a 25-bit pixel (24 colour bits and a bypass bit) | **inferred**, same method; the RAMDAC specification was not read |
| Console / X server depths offered | `rex3Depths8`: depth 1 none, 2 one visual, 4 two, 8 three | `rex3Depths24`: 1 none, 2 one, 4 two, 8 four, 12 three, 24 two | **established** that the tables hold these counts (IRIX 6.5 base and 6.5.30 `ng1.so` are identical); reading each entry as a depth and a visual count is **inferred**; which visual each is was not decoded (the ID arrays are filled at run time) |
| X server pixmap formats | one table for both: depths 1, 2, 4, 8, 12, 24 at 1, 8, 8, 8, 16, 32 bits per pixel, 32-bit scanline pad | same | **established** that `rex3Formats` holds these six byte triples; reading them as X pixmap formats is **inferred** |

How the X server loads the 24-bit colour ramp: `rex3Install24Map` in `ng1.so` takes the X colormap, builds three 256-byte
channel tables and 256 packed words (red in bits 7:0, then green, then blue in 23:16) from a DirectColor colormap, and hands them to
the kernel in one request; for a TrueColor colormap it makes a different kernel request with no table. **Inferred**: the function
was read in full, but the colormap class codes and the kernel request meaning are reasoned. It shows the 24-bit path loads a ramp
that applies to each channel separately, in line with the XMAP9's three ramp regions.

## What a driver has to do differently on an XL24

All derived from the rows above; none tested.

- Detect the depth by the rule for the machine, or take it from the firmware's configuration data; do not assume 24.
- Set XMAP9 configuration bit 2 to match and leave pop-up on unless the 8-bit system's two aux bits are wanted.
- Program the mode-table entry a window's display ID selects: 24-bit RGB is size 3 with an RGB ramp, 8-bit colour index is size 1
  with an MSB field; 24-bit modes are only valid on a 24-bit board.
- For 24-bit RGB, load the chosen ramp (NetBSD loads an identity ramp at colour-map addresses 0x1f00 to 0x1fff for ramp 2) before
  displaying; draw with draw depth 24 and a write mask of 0xffffff, and move pixels as 32-bit host words with host depth 32.
- Clear the overlay planes (mask 0xffff00, overlay plane mode) as well as the frame buffer, as the PROM does.
- Byte-lane handling for the host depth-32 and display-bus writes on a little-endian CPU is
  [unknown](../../devices/rex3/byte-lanes.md#the-little-endian-question).

## Open

Entered in [questions](../../questions/README.md#rex3-and-newport-from-a-little-endian-cpu): the board-revision source on the
Indigo2, what bit 9 of the timing record means (it gates the kernel's 0xd0), the visual list the X server builds per depth, the colour map
and Bt445 contents (no specification), and whether any 24-bit board reports revision 2 or higher with bit 7 clear.
