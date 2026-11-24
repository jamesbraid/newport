# REX1: the GetImage read-back (0x2000ab) and the stippled rectangle fill (0x...9a9)

Two command words the IRIX 5.3 X server issues often, and what it expects from the board for each. Grades and tags follow the
[REX1 page](README.md) and [AGENTS.md](../../AGENTS.md): **[binary]** read in `lg1mc.so` at the address given (5.3 virtual addresses),
**[hdr]** a name from the shipped `sys/lg1hw.h`, **[inferred]** with its basis. Sources: `usr/lib/X11/dyDDX/lg1mc.so` of the IRIX 5.3
install disc (checksum in [irix-files.md](../../references/irix-files.md)). The counts the brief gave (0x2000ab 1283 times and the 9a9 form 230
times in one X start) come from an emulator run, not from these binaries.

## 0x2000ab: host pixel read (`rexReadImage`, 0x5e30e644)

**Established** (the whole function was read; the unaligned paths were read for the access pattern only).

The word is `CMD_HOSTDATA_READ` in the [register list](registers.md): 0x200000 `COLORAUX` [hdr] plus 0xab, which is opcode 3 (`REX_LDPIXEL`
[hdr], "load pixels") with QUADMODE, BLOCK and XYCONTINUE. The same opcode with a different flag set is the pixel-memory probe read 0x30200023, so this is the
same engine function, not a new one. Sequence, per GetImage of rectangle (x0, y0) to (x1, y1) exclusive:

1. Wait for `CONFIGMODE` bit 0 clear (idle).
2. In one branch, chosen by a flag word in the window record, `AUX1` = 0x30 (`DBLSRC` and `DOUBLEBUF` [hdr]); `XSTARTI` = x0, `YSTARTI` = y0,
   `XENDI` = x1 - 1, `YENDI` = y1 - 1; `AUX2` = plane group << 29, the group taken from the window record (1 is `PIXELPLANES` [hdr], 2 `OVERLAYPLANES`, 3 `CIDPLANES`).
3. `COMMAND` (GO alias, 0x800) = 0, then `COMMAND` = 0x002000ab at the SET address.
4. Wait for idle again.
5. One read of `RWAUX1` GO (0x870) whose value is discarded.
6. Then reads of `RWAUX1` GO, ceil(width / 4) per row for a destination aligned to four bytes (the common path, 0x5e30e7a4 to 0x5e30e898,
   with a 16-pixel unrolled loop for the bulk and a masked merge for the last 1 to 3 pixels), for every row of the rectangle, one
   command for the whole rectangle (no per-row restart).
7. `AUX1` = 0 afterwards if it set it.

Each word carries four pixels, **leftmost pixel in the high byte**; the server stores the words as read for an aligned destination and shifts
them for an unaligned one. The start is XSTARTI itself: the server never aligns it to a multiple of four, so the first word holds pixels
x0 to x0 + 3. A partial last word of a row is fully read and the unused low bytes are dropped; the next row starts on a fresh word.
**Inferred** from the consumed counts that the board pads each row to a whole word (the aligned path reads exactly `ceil(width / 4)` words per row and
nothing re-synchronises it). **Unknown** whether the real chip pads rows or runs the stream on
across rows; the aligned path only works if rows are padded. The unaligned destination path was not counted word for word. A
model should pad rows to whole words.

### If the board refuses or ignores the command

The server does no checking: it never looks at a status or a data-valid bit, never times out and never counts words. A model that ignores
the command still gets all the reads, and whatever `RWAUX1` GO returns becomes the image (zero, or the last value written there).
So GetImage replies are silently wrong rather than failing, and everything the server does with a GetImage result goes wrong with them:
a client that reads a window or root region, the server's own copies out of the screen into a pixmap that it later draws back, and
saved regions it restores. Which of these accounts for the 1283 calls was not traced; **unknown**.

What the model must do: run the rectangle in raster order over the selected plane group and buffer, returning one word per four
pixels, high byte first, rows padded to a word, after one discarded read.

## 0x...9a9: stippled rectangle (`rexStippledFillRects`, 0x5e30d930)

**Established** for the command words and register sequence (the loop at 0x5e30da48 to 0x5e30dbf4 was read in full); **inferred** for the
pattern bit order. The words are built at 0x5e30d9d4 and 0x5e30d9f8: `(operation << 28) | 0x9a9` for a transparent stipple and the same with
0x400000 (`LSOPAQUE` [hdr]) added for an opaque one. With the replace operation (3) the first is 0x300009a9. The flags are, by their [hdr] names,
DRAW, BLOCK, QUADMODE, XYCONTINUE, STOPONX and ENLSPATTERN (bit 11) (the [register list](registers.md) already has the same flag set without
ENLSPATTERN as `CMD_SPAN_LSPATTERN`, 0x921, for spans). The word is not an image command: the "mono image" calls are `rexDrawMonoImage`
(0x5b9 and relatives, driven by `ZPATTERN`, see the [register list](registers.md)).

Per rectangle (x0, y0, x1, y1), with w the stipple's width in pixels (the repeat length, encoded into `LSMODE` below):

1. Once, before the first rectangle: `AUX2` = plane group << 29; `LSMODE` = (w - 17) << 16; `XSTATE` = foreground colour in bits 7:0, the plane mask in
   bits 23:16 and, for the opaque form, the background colour in bits 15:8 (0x5e30d9d4 to 0x5e30da24; **inferred** from which
   fields the code ORs together).
2. `XSTARTI` = x0, `YSTARTI` = y0, `XENDI` = x1 - 1, `YENDI` = y1 - 1; `COMMAND` GO alias (0x800) = 0, then `COMMAND` = the word above.
3. One 32-bit store to `LSPATTERN` GO (0x864) for each row y0 to y1 - 1. The word is the stipple's row for that y (the stipple rows
   repeat modulo their height from the stipple origin), rotated left by `(x0 - origin x) mod w`.

So the board must treat each store to `LSPATTERN` GO as "draw one row of the block, from XSTARTI to XENDI, using this word's bits as
the per-pixel mask, then advance y". **Inferred** that bit 31 is the leftmost pixel (the direction the glyph path's `ZPATTERN` takes); that a clear bit leaves the pixel alone when the command lacks
`LSOPAQUE` and paints the background colour in `XSTATE` bits 15:8 when it has it. STOPONY is not set: the number of rows is the number of pattern writes, not
`YENDI`.

If the board ignores the command: the rectangle is not drawn. The X server sends no read-back for it, so nothing hangs; the symptom is
missing patterned fills (window and menu backgrounds that use stipples or tiles of up to 32 pixels, widgets' shaded areas). A model that
draws a solid foreground rectangle for every row instead is closer on screen than dropping the command, but it is wrong for the
background.

## Open

- Whether the board pads GetImage rows to a whole word, and what happens when XSTARTI is not a multiple of four (answer: a data sheet
  for REX1, or the REX3 equivalent, if the two share the host-data unit; they are not claimed to).
- The pattern bit order, and how `LSMODE` encodes a width other than 32.
