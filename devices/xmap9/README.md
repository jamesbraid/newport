# XMAP9 mode and overlay mapper (Newport graphics)

The pair of chips on the Newport board that sit between the frame buffer and the colour maps. For every pixel they pick what is
shown (cursor, pop-up, overlay, video, pixel or underlay), read the window's display mode from a 32-entry mode table indexed by the
display ID the VC2 supplies, and turn the frame buffer's bit-interleaved pixel into either a 24-bit RGB value or a 13-bit
colour-map index. One XMAP9 handles the even pixels and one the odd, each at half the pixel clock.

Grades follow [AGENTS.md](../../AGENTS.md). Sources: the XMAP9 Specification, revision 2.1, 29 October 1993 (Library
`library/cache/graphics/indy/erikarn-sgi_indy_xmap9.pdf`, read in full as text; the bit-interleave tables were read from the
extracted text, not from page images), the PROM source's Newport files, the IRIX 6.5 IP22 kernel's `newport_init.o` (function
`initXMAP9`, read in full), the ide diagnostics' visual table, and the public Linux and NetBSD drivers. Where this page says a
field name from the ide table is a given XMAP9 field, that is **inferred** from the name and the specification's bit positions: the
header that gives the macro values (`sys/xmap9.h`) is not in the source tree. Board-level depth handling is on the Newport board page.

## Registers

**Established** (specification; the two public drivers and the PROM use the same CRS numbers). Reached over REX3's display bus at
`DCBADDR` 4 (both chips; write only), 5 (chip 0) and 6 (chip 1), with the register in `DCBCRS`:

| CRS | Access | Register |
|---|---|---|
| 0 | read-write, 8 bits | Configuration. Bit 7 video option on, bit 6 Express (not Starter) video, bits 5:4 RGB map for video, bit 3 slow display-bus timing, **bit 2 8-bit system (0 is a 24-bit system)**, bit 1 odd-pixel chip, bit 0 pop-up planes on. Zero after reset; the chip never changes it |
| 1 | read, 3 bits | Revision, counting from 0 |
| 2 | read, 3 bits | Mode FIFO entries free, as a Gray code: 0 full, 1 one free, 3 two free, 2 three (empty). May be off by one; the chip has one more entry than it reports |
| 3 | read-write, 8 bits | Cursor colour-map MSB: bits 12:5 of the colour-map address of the cursor's four entries |
| 4 | read-write, 8 bits | Pop-up colour-map MSB, same form |
| 5 | write 32 bits, read 8 | Mode table: a write is the entry number (5 bits) in the first byte, then the three bytes of the 24-bit entry, most significant first, as one four-byte transfer; reads are one byte at a time through CRS 7 |
| 7 | read-write, 8 bits | Mode table address, for reads: bit 7 read-port select, bits 6:2 entry, bits 1:0 byte (0 is bits 23:16, 1 bits 15:8, 2 bits 7:0) |

Mode writes go through a FIFO and take effect in blanking; a read right after a write may return stale data for about ten pixel
clocks, so the host writes another entry or talks to another chip first.

**Established** (PROM source and the IRIX kernel, both read): the even chip is written with the odd-pixel bit clear and the odd chip
with it set; the cursor MSB is 0xE7 and the pop-up MSB 0; the display-bus protocol is retimed by the pixel clock (below 60 MHz the
slowest timings, 60 to 119 a middle set, 120 and up the fast ones).

## Mode table

32 entries, 24 bits each (**established**, specification; written as the four-byte transfer above). Field names are the
specification's:

| Bits | Field | Meaning |
|---|---|---|
| 23:19 | Aux MSB colour-map | Top five address bits for overlay and underlay colours (always colour index) |
| 18:16 | Aux pixel mode | 0 off, 1 full underlay, 2 full overlay, 6 double-buffered overlay, 7 overlay and underlay together |
| 15 | Alpha enable | Express video: alpha with 12-bit RGB or double-buffered 8-bit RGB |
| 14 | Video dither bypass | |
| 13:12 | Video mode | 0 off, 1 overlay, 2 underlay, 3 replace pixel |
| 11:10 | Pixel size | 0 4 bits, 1 8 bits, 2 12 bits, 3 24 bits (not for colour index) |
| 9:8 | Pixel mode | 0 colour index, 1 to 3 RGB with colour-map ramp 0, 1 or 2 |
| 7:3 | MSB colour-map | Top five bits of the colour-map address in colour-index modes |
| 2 | Gamma bypass | Skip the DAC's gamma correction for these pixels |
| 1 | Overlay buffer select | |
| 0 | Buffer select | Which half of a double-buffered 4-bit or 12-bit pixel is shown |

Modes that exist (**established**, specification table 3f). Colour index: 4-bit and 12-bit, each with buffer 0 or 1, and 8-bit.
RGB: 4-bit and 12-bit, each with buffer 0 or 1, 8-bit, and 24-bit. For the video option: 8-bit RGB with 4-bit alpha (buffer 0 or
1) and 12-bit RGB with 8-bit alpha. The 24-bit size and every 12-bit mode exist only in a 24-bit system (specification table 3d);
an 8-bit system's frame buffer supplies only bits 7:0 of the pixel (`Pix_In` bits 23:8 are ignored, table 2a) and so only the 4-bit,
8-bit and double-buffered 4+4 forms. The IRIX diagnostics refuse their 24-bit-only visuals on a board that reports fewer planes
([visual table](#the-visuals-the-irix-diagnostics-program), below).

What the PROM and kernel write: **established** that the PROM source writes entry *i* = `XM9_PIXSIZE_8` (8-bit colour index,
bits 11:10 = 1, so 0x400) for all 32 entries in both depths; the kernel's `initXMAP9` writes one entry, number 0, the same value,
and leaves the rest to the X server.

### Colour-map addresses the chip produces

**Established** (specification tables 3g, 3h, 3j to 3l; the specification says all XMAP9 output goes through the colour map, there
is no bypass):

- Colour index, 13-bit address: 8-bit is the mode entry's MSB field in bits 12:8 and the pixel in 7:0; 4-bit is the MSB field in 12:8,
  zeros in 7:4 and the pixel in 3:0 (buffer 1 uses pixel bits 7:4); 12-bit is MSB bit 4 in bit 12 and the pixel in 11:0 (buffer 1 uses
  pixel bits 23:12). The upper 11 bits of the 24-bit output are ignored by the colour map in colour-index mode, so the map is 8K entries.
- RGB: all 24 bits are sent, tagged 01, 10 or 11 for ramp 0, 1 or 2; the tag pins read "11101", "11110" and "11111" followed by an
  8-bit address, which places the three ramps at colour-map addresses 0x1D00, 0x1E00 and 0x1F00 (**inferred** reading; how the colour
  map applies the 8-bit address to R, G and B is in the colour-map specification, which is not held, so it is **unknown**). NetBSD
  writes an identity ramp at `0x1f00 + i` and uses ramp 2 for its 24-bit mode: **established** as that driver's expectation.
- 8-bit RGB (3-3-2) and 4-bit RGB expand by replicating bits so full-scale input gives full-scale output (table 3h).
- Cursor: colour-map address `(CRS3 << 5) | cursor bits`; with the PROM's 0xE7 that is 0x1CE0 to 0x1CE3 (**inferred**, formula from
  the specification and constant from the PROM). Pop-up: `(CRS4 << 5) | pop-up bits`, 0x0000 to 0x0003 with the PROM's 0.

## Aux planes, pop-up and the 8-bit system

**Established** (specification tables 3e, 3i): a 24-bit system has 8 aux bits (overlay, underlay, or 4 and 4) and 2 separate pop-up
bits. An 8-bit system has two bits only, which are the pop-up bits and the aux bits at once. With pop-up on (configuration bit 0) an
8-bit system has no overlay or underlay: every Aux pixel mode is ignored. With pop-up off its two bits drive the "2-bit" overlay
and underlay modes (and the 1-bit double-buffered forms). A 24-bit system with pop-up off ignores the pop-up inputs. The mode is
chip-wide, not per window. The PROM and kernel turn pop-up on in both depths.

## The visuals the IRIX diagnostics program

**Source** (IRIX 6.5.7 `stand/arcs/ide/fforward/graphics/NEWPORT/ng1visuals.c`, read in full; `ng1_setvisual` refuses a
24-bit-only visual when the board reports other than 24 planes). Fields read as above (**inferred** reading of the macro names:
`X9_8BIT` pixel size 1, `X9_RGB0` pixel mode 1, `X9_CMAP(n)` MSB colour-map, `X9_AMAP(n)` aux MSB, `X9_OLAY` aux mode 2, `X9_BB` buffer
select 1). `DRAWMODE1` depths are the diagnostics' choice of `DRAWDEPTH` / `HOSTDEPTH`.

| Visual | Needs 24 | Draw / host depth | `WRMASK` | Entry | Pixel size, mode |
|---|---|---|---|---|---|
| ci8 | no | 8 / 8 | 0xff | 0 | 8-bit, CI, map 0 |
| ci12 | yes | 12 / 12 | 0xfff | 1 | 12-bit, CI |
| rgba20 | yes | 12 / 32, RGBA planes | 0xfff | 2 | 12-bit, RGB ramp 1 |
| ovl8 | yes | 8 / 8, overlay planes | 0xffff00 | 3 | 8-bit, overlay, aux MSB 16 |
| rgb8 | no | 8 / 8, RGB mode | 0xff | 4 | 8-bit, RGB ramp 1 |
| rgb24 | yes | 24 / 32, RGB mode | 0xffffff | 5 | 24-bit, RGB ramp 0 |
| rgb12 front, back | yes | 12 / 12, RGB mode, back reads buffer 1 | 0xfff, 0xfff000 | 6 | 12-bit, RGB ramp 1, back adds buffer select |
| ci12 front, back | yes | 12 / 12 | 0xfff, 0xfff000 | 7 | 12-bit, CI |
| rgba12 front, back | yes | 12 / 12, RGBA planes, RGB mode | 0xfff, 0xfff000 | 8 | 12-bit, RGB ramp 1 |
| ci4 front, back | no | 4 / 4 | 0xf, 0xf0 | 9 | 4-bit, CI |
| rgb4 front, back | no | 4 / 4, RGB mode | 0xf, 0xf0 | 10 | 4-bit, RGB ramp 1 |
| pup2 | no | 4 / 4, pop-up planes | 0xcc | none | no display ID |
| cid2 | no | 4 / 4, CID planes | 0x33 | none | no display ID |

The write masks 0xcc and 0x33 for the pop-up and CID planes, with the PROM's `REX3_PUP_WRMASK` 0xcc, `REX3_CID_WRMASK` 0x33 and
overlay mask 0xffff00, show the aux planes are interleaved bit-pairs of one plane group: **inferred**.
