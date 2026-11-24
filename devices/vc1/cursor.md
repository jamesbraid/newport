# VC1: the hardware cursor

What the IRIX 5.3 X server and kernel do to draw the pointer on the Entry board, and what a model needs to show it. The chip-level
register list is on the [VC1 page](README.md); this page adds the glyph format, where the glyph lives, the enable bits and the colours.

Grades and tags are as on the [display ID page](did-xmap.md): **[binary]** read at a function and address in the IRIX 5.3 `lg1.a`
(kernel, offsets in the member) or `lg1mc.so` (X server, virtual addresses), **[hdr]** a name or value from the shipped `sys/lg1hw.h`
and `sys/lg1.h`, **[inferred]** with its basis. No VC1 or colour-map data sheet is held.

## What the reviewed pages already said, and what is new

Already on the [VC1 page](README.md) and the [board page](../../platforms/lg1/README.md#x-server-the-colour-map-vc1-and-cursor):
cursor position registers 0x22 and 0x24 with the added constants 0x8c and 0x27 (established); the glyph pointer in register 0x20 and an
area at SRAM 0x3000 (the kernel's, inferred); SYS_CTL bits 4 and 5 (NetBSD names, inferred); a bank-3 colour location 0x21 to 0x23
(from the board page, without the bank).

New here:

- The X server does not use 0x3000: it points register 0x20 at **SRAM 0x0700** and loads its 256-byte glyph there (established, and
  the same address is named `VC1_CURSOR_GLYPH_ADDR` in `sys/lg1.h` [hdr]).
- The glyph is two 128-byte bit planes, 32 rows of 32 pixels (inferred from the builder, established as the byte layout in the
  server's buffer).
- The three cursor colours are palette entries **0x21, 0x22 and 0x23 of bank 3**, not Bt479 overlay-register values (established).
- [hdr] names for all cursor registers, the position offsets and the SYS_CTL bits.

## Registers [hdr]

| Offset | Name [hdr] | What software writes |
|---|---|---|
| 0x20, 0x21 | `CUR_EP` | glyph pointer: kernel `initLg1Cursor` (`light_init.o` +0x7e8) 0x3000; X server `vc1Init` (0x5e2d2d90) and `rexInstallCursor` (0x5e308c4c) 0x0700 (established) |
| 0x22, 0x23 | `CUR_XL` | x + 0x8c - hot x, high byte first (`lightPositionCursor`, `light.o` +0x548; `CURSOR_XOFF` 140 [hdr]) |
| 0x24, 0x25 | `CUR_YL` | y + 0x27 - hot y, high byte first (`CURSOR_YOFF` 39 [hdr]) |
| 0x26 | `CUR_MODE` | X server: 0xc8 (`rexCursorInit` 0x5e2d3688, and `rexDisplayCursor` 0x5e3082b8 for a visible cursor), 0xcb (`rexDisplayCursor`, in the path that also zeroes the hot spot and calls request 20001; **inferred** to be the cursor-removed case); the kernel and `vc1Init` write 0 |
| 0x27 | `CUR_BX` | 0 |
| 0x28 to 0x31 | `CUR_LY`, `CUR_YC`, `CUR_XC`, `CUR_CC`, `CUR_RC` | never written by the kernel, the X server module or the PROM; roles unknown |

[hdr] also lists `CUR_MODE_NORMAL` 0, `CUR_MODE_SPECIAL` 1 and `CUR_MODE_CROSSHAIR` 2. The values 0xc8 and 0xcb do not map onto those three
by their low bits alone (0xc8 has low bits 0, 0xcb has low bits 3); what bits 7:6 and 3 are is **unknown**. A model can store the byte
and treat any non-zero upper nibble as "cursor mode set".

**Established** (traced store sequence of `vc1Init`): the initial position is 0x0240 in both axes (x = 436, y = 537 on screen),
with an all-zero glyph, so nothing shows until the server loads one. A position of 0x8c in x and 0x27 in y puts the glyph's
top-left on screen pixel (0, 0); **inferred** from the constants (no run).

## Enable bits

SYS_CTL (`CONFIGSEL` 6): bit 4 `VC1_CURSOR` and bit 5 `VC1_CURSOR_DISPLAY` [hdr] (both "active high"). **Established** that the server
sets or clears both together: `rexCursorOn` (0x5e319800) ORs 0x30 into, or clears 0x30 from, a software copy of SYS_CTL kept at +4 of the
board record and stores it with no read-back. `rexInstallCursor` clears the two bits in the chip before loading the glyph and restores
the copy afterwards; `vc1LoadDIDTable` does the same around its table load. **Inferred** that bit 4 powers the generator and bit 5
makes it visible; no shipped code sets one without the other.

## Glyph format

256 bytes at SRAM 0x0700. **Established** for the layout the server builds in `rexDisplayCursor` (0x5e3082b8, the loop at
0x5e30842c to 0x5e3084e0 and its sibling at 0x5e308554 to 0x5e3085a0), **inferred** for the pixel-to-colour rule:

- Bytes 0 to 127: plane 0, rows 0 to 31, four bytes per row, big-endian word with the leftmost pixel in bit 31 (the width mask the code
  applies keeps the high bits).
- Bytes 128 to 255: plane 1, same shape.
- A pixel is `(plane 1 bit << 1) | plane 0 bit`: 0 is transparent, 1 to 3 select a colour. In the common builder branch plane 0 is
  `source AND mask` and plane 1 is `NOT source AND mask`, so an X cursor's foreground pixels are code 1 and background pixels code 2. In
  the other branch (taken when a field of the cursor record is non-zero, not decoded) plane 0 is the first bitmap and plane 1 the XOR of the two.
- Widths below 32 are masked on the right. Rows beyond a shorter cursor's height: **unknown** (the buffer's clearing was not read).

The kernel clears the glyph (256 zero bytes at 0x3000 for itself; the server clears 0x0700 to 0x07ff in `rexCursorInit`). A model that
stores SRAM bytes and draws the glyph from where register 0x20 points needs no other rule. The row order (row 0 at the top) is **inferred**:
the server copies its bitmap rows in memory order, so any other order would mirror every cursor.

## Colours

The cursor colour routine (unnamed in the symbol table, at 0x5e308640 after `rexDisplayCursor`; **established** for the stores): selects bank 3 (selector 0 =
0x82, selector 6 = 0x3f, or `0xc0 | low nibble` on the LUT1 variant), then writes palette entries 0x21, 0x22 and 0x23 with red, green,
blue (high byte of each 16-bit X colour). Entry 0x21 takes the cursor's foreground colour, 0x22 its background colour, and 0x23 an optional third
colour taken from a separate record the caller may pass (the field order matches the X cursor structure's fore then back
triples). Entry 0x20 is never written. **Inferred** that pixel code k reads entry 0x20 + k of bank 3; **unknown** what in the VC1 supplies the 0x20 or the bank
(the cursor registers 0x28 to 0x31 are the only candidates and nobody writes them, and the only mode words with bank 3 are DIDs 6 to 8,
whose index offsets are 0x00, 0x30 and 0x40). Shipped code never writes the Bt479's overlay registers (selectors 4, 5 and 7; `OVERLAY_WRITE_ADDR`,
`OVERLAY`, `OVERLAY_READ_ADDR` [hdr]); the cursor colours are in the main palette.

## What a model must do

1. Keep SRAM (64 KiB: the X server uses addresses up to 0x5000 plus its line table, and the kernel readback allows 0x10000 bytes of
   scan records), registers 0x20 to 0x27 and SYS_CTL as plain storage that reads back.
2. When SYS_CTL bits 5 and 4 are both set, draw the 32 x 32 glyph at screen position (reg 0x22/23 - 0x8c, reg 0x24/25 - 0x27)
   with the top-left pixel there, taking the glyph from the SRAM address in registers 0x20/21. Pixel code 0 shows the frame buffer;
   codes 1 to 3 show bank 3 entries 0x21 to 0x23 (inferred base 0x20).
3. Accept 0xc8 and 0xcb in register 0x26; no behaviour is required.

What would settle the unknowns: a VC1 data sheet for registers 0x27 to 0x31; any captured session of the server's hot spot values
against a rendered cursor image.
