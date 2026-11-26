# LG1: how the X server moves a window (pixel copy and exposures)

What the IRIX 6.2 X server sends to the Entry board when a mapped window is dragged: the block copy of the window's pixels, the
order and direction it runs in, and what repaints the area the window left. The display-ID table rewrite that follows the copy is on
[VC1: display IDs](../../devices/vc1/did-xmap.md#when-a-window-moves-irix-62-x-server-read-2026-11-25); the copy command word is on
the [REX1 page](../../devices/rex1/README.md).

Grades follow [AGENTS.md](../../AGENTS.md). **[binary]** is read in the IRIX 6.2 `lg1mc.so` (hash in
[irix-files.md](../../references/irix-files.md); addresses are its virtual addresses; the module exports routine names, the local
helpers have none). Everything here is what the software sends and expects; no board was measured. The slot numbers are byte offsets
in the screen record, as on the display-ID page.

## The copy: slot 224, `rexCopyWindow` (0x5e4acf60)

**What it computes [binary, established].** Arguments are the window, its old origin and the old visible region. dx and dy are the old
origin minus the new one. The old region is translated by (-dx, -dy) (to the new position) and intersected with the window's
`borderClip`, which gives the destination rectangles; each rectangle's source point is its own top-left corner plus (dx, dy), that is,
the same rectangle at the old position. A window with sub-layers (a descendant window in another plane group, such as a rendering child) repeats this once
for each other plane group among its descendants, which are walked depth first; each group gets one region built from those descendants' `borderClip`s
inside the translated old region, and `AUX2` takes that group's value each time. The copy itself is an
unnamed helper at 0x5e4ad4ec, called with the window, the destination region and the source points.

**Box order [binary, established].** The helper looks at the first box only, then reorders the whole list:

1. If the first source y is less than the first destination y1 (the window moves down) and there are at least two boxes, the bands
   are reversed, bottom band first; boxes inside a band keep their order.
2. Then, if the first source x is less than the first destination x1 (the window moves right) and there are at least two boxes, the
   boxes inside each band are reversed, rightmost first.

A down-right drag therefore runs the bottom band first and its rightmost box first, so the box at the window's top-left is the last one
issued. A pure move up or left reverses nothing.

**Register sequence [binary, established].** Once per call: `COMMAND` (0x000, SET) = 0x00080329, `AUX2` (0x47a8) = plane group << 29,
`XSTATE` (0x008) = 0x23ff0000 (the store is established; the field roles, operation 3, all eight planes and bit 29, are inferred on the [register page](../../devices/rex1/registers.md)). Then per box, in this order: `XSTARTI` (0x00c),
`XENDI` (0x084), `YSTARTI` (0x01c), `YENDI` (0x088), and last `XYMOVE` at its GO alias 0x834, which runs the command. After the last box the server
spins on `CONFIGMODE` (0x47f8) bit 0 until it clears. Values, decided per box from the signs of dx and dy (source minus destination):

| Condition | Registers | Direction |
|---|---|---|
| dx >= 0 | `XSTARTI` = x1, `XENDI` = x2 - 1 | left to right |
| dx < 0 | `XSTARTI` = x2 - 1, `XENDI` = x1 | right to left |
| dy >= 0 | `YSTARTI` = y1, `YENDI` = y2 - 1 | top to bottom |
| dy < 0 | `YSTARTI` = y2 - 1, `YENDI` = y1 | bottom to top |

`XYMOVE` = (source x - destination x1) << 16 | (source y - destination y1) & 0xffff, the same for every box of a move. The y values are the
display row with no 767 flip. Window moves down and to the right therefore send both start values above their end values and both halves of
`XYMOVE` negative.

**Left-edge workaround [binary, established; the reason is inferred].** When dx < 0 and a box starts at x1 < 4, the server waits for
`CONFIGMODE` bit 0 to clear, stores `XYWIN` (0x47fc) = 0x07fc0800 (the window x offset 4 lower than the usual 0x08000800), and
sends `XSTARTI` = x2 + 3 and `XENDI` = x1 + 4 for that box. It restores `XYWIN` = 0x08000800, again after a `CONFIGMODE` wait, before the first later box that starts at x1 >= 4 and after the last box. The two shifts cancel, so the pixels land where the plain
sequence would put them; the likely reason (inferred) is that a right-to-left quad copy at the screen's left edge would otherwise run to
negative x. A model that ignores the `XYWIN` x offset moves only the boxes at x < 4 four pixels to the right.

**What a copy engine must do [inferred from the software contract].** Walk x and y from start toward end in the direction the two
registers give, not in normalised ascending order, and read each source pixel at its current value (a memmove). A snapshot of the whole
source taken when the command runs also gives the right result for these sequences, because the server orders the boxes so that no
later box reads pixels an earlier box wrote; an engine that always runs ascending, or swaps start and end and then runs ascending, smears the
top rows and left columns of the window over the rest for every move down or right.

## What repaints the area the window left

Standard X structure, with the nfb routines of the 6.2 server **[binary]**. After the copy, `nfbMoveWindow` calls slot 492,
`miHandleValidateExposures` (0x5e486360) for the parent. For the window it is given and every window below it (depth first) that has validation data it calls, in this order:

1. slot 220, `nfbPaintWindowBorder`, for the part of the border that became visible;
2. slot 212, `miWindowExposures` (0x5e48c694), for the region that became visible (**established** for the call; what each window's region
   holds comes from the validation code, which was not re-read, **inferred**).

`miWindowExposures` **always** paints the background first, when the region is not empty: slot 216, `nfbPaintWindowBackground` (0x5e490fcc), with the
region's rectangles passed straight to the REX fill or tile routine, in the window's plane group. Only then, and only if some client selected
`ExposureMask` on the window, does it call `miSendExposures`, which sends Expose events for the region. That same condition adds one step before the fill: when the
exposed region has 26 or more rectangles it is replaced by its extents, for the Expose events and for the fill alike (the fill covers the extents clipped to the window's `clipList`, so it can paint pixels outside the exposed region). The background step by state of the window's background (bits 31:30 of the word at +124):

- none: nothing is painted (a GL canvas window has this state);
- parent-relative: the nearest ancestor that is not parent-relative supplies the fill;
- pixel: a solid rectangle fill in the window's colour;
- pixmap: a tile fill with the tile origin taken modulo the tile size.

So the server paints the vacated area itself, once, window by window with each window's own background colour, and sends Expose events; **the paths read here redraw no window contents**. (For a window whose backing-store field (+0x74 in the window record, as in the standard X structure) is set, `miWindowExposures` first calls screen slot 248
before the fill, and by the standard structure that slot restores saved pixels; it was not traced, so such a window may need no Expose.) A
client repaints its icons, text and widgets only in answer to its Expose events. The moved window's own newly visible part gets its own background fill and Expose events
in the same way.

## What a strip along the top and left edge of a moved window means

Two different faults give a strip in the top-left corner of a moved window, and they are told apart by where it sits and which drags show it.

- **Inside the window's new rectangle: a copy fault.** A down-right drag issues the box at the top-left last, so a copy that is cut short or mishandles
  start above end (an exclusive end, an empty range, ascending iteration) leaves the top rows and left columns of the new rectangle with whatever was on screen at the
  new position before the copy. That is the colour of another window's interior when the mover was dragged over that window. The strip then stays until
  the client repaints the row. Only moves down or to the right (or both) show it.
- **Outside the new rectangle, in the L-shaped area the window left: a repaint fault.** The server paints the vacated area with the background of the window behind it (the colour of
  that window's interior) and sends it Expose events. A plain-background strip with no content in it means the fill ran and the window behind did not repaint; the
  fill is not the fault. The strip mirrors for the opposite drag (bottom and right edges of the old position after an up-left drag).

Discriminating checks the model can run:

1. Compare the strip's rectangle with the new window rectangle and the drag's dx and dy: inside means the copy, outside means the repaint.
2. Drag the same window up-left, then down-right. A copy fault shows only after the second; a repaint fault shows at mirrored edges.
3. Replay the logged copy commands (the per-box registers above) on a snapshot of the frame buffer with a memmove and compare with the model's frame
   buffer after the move. Any difference is a copy fault.
4. For the repaint case, look for drawing commands from the client inside the strip rectangle after the background fill. None means no Expose
   reached the client (check `miSendExposures`, and `ExposureMask` on the window behind); some, with the strip unchanged, means the model mishandles those
   draws.

## Unknown, with the routes tried

- What each window's exposed region holds (new visible area minus old visible area translated) comes from `nfbLayerValidateTreeSL`, which was
  not read line by line; the order and the two calls above were.
- The layered branch of `rexCopyWindow` (windows with a rendering child) was read for its structure, not traced for every ancestor case.
- The 5.3 and 6.5 modules were not read for this path.
