# LG1: the Indigo Entry graphics board

The Entry ("Starter", LG1) graphics board of the SGI Indigo: a REX1 raster engine, a VC1 video controller with its SRAM, a
colour map, a pixel clock generator and eight memory chips on the photographed board (a 1024 by 768 frame buffer at 8 bits per pixel: the resolution and depth are established, the chip count is observed).
This page is the board-level account: what it is, where it sits, how the PROM and IRIX find and drive it. Register detail is in the
chip pages: [REX1](../../devices/rex1/README.md), [VC1](../../devices/vc1/README.md),
[Bt479 and LUT1](../../devices/bt479/README.md).

Grades follow [AGENTS.md](../../AGENTS.md). This is the **Indigo** (IP20 R4000 board; the PROM listing is also the base for the
IP12 R3000 board, which was not read here). The Entry board of the R3000 Indigo is the same board family; the facts below are
read from IP20 objects and PROMs and apply to the IP12 only where its PROM or kernel was read (it was not): **inferred** for IP12.
The Crimson also took an LG1; NetBSD says its register offsets differ significantly, so nothing here applies to it.

## Chips on the board

| Chip | Evidence | Grade |
|---|---|---|
| REX1 raster engine | Software calls the chip "REX" (board info routines, the ide "REX register r/w test"); an LSI Logic gate array on the photographed board; part number not legible. | name established; marking unknown |
| VC1 video controller | Package marked `L1A6654 VC1 REV B` in the photograph (`photos/sgistuff-indigo/indigo-lg1a-1001.jpg`); software and the ide test call it VC1 ("VC1 Chip Revison %d", "VC1 SRAM test") | established name; revision as read by software: see the VC1 page |
| Colour map | Brooktree-marked package and a package marked `L1A6651 LUT1 REV A` on the photographed board; ide prints "Bt479 element" for the board-rev-below-2 path; the kernel calls the other variant `lg2` / LUT1 | name established per variant; which variant is on which board: inferred from the software's revision rule |
| Pixel clock generator | Written with 17 bytes from a table, one table per board revision; chip: unknown (no printed name, no datasheet) | role inferred, chip unknown |
| Frame buffer | Eight identical memory parts beside the REX on the photographed board; the ide VRAM test reports errors by chip reference (U2x); part type unknown | count observed; type unknown |
| XMAP | The VC1 carries the display-mode (XMAP) table itself (a register window); there is no separate XMAP chip in any shipped software path | established that software addresses it through the VC1 |

The board has two physical halves in the photograph (a GIO32 card with REX and the frame buffer, and a daughter card with
VC1 and the colour map); whether the video-board-present bit (WCLOCK bit 6) refers to that daughter card: **inferred**.

## Where it sits: GIO and addresses

Do not duplicate: the graphics slot, the probe addresses and the probe sequence are on the chips repository page `platforms/ip20/gio.md`. In short (all
established there): the board lives in the 4 MiB graphics window of the GIO space at 0x1f3f0000, with a second head at
0x1f3f8000; the LG1 does not answer the GIO product-ID read; and the board interrupts on GIO lines 0 (FIFO) and 2 (retrace),
INT2 local 0 bit 0 and local 1 bit 7 (see the chips repository's `devices/int2/README.md`).

What the probe's registers mean, from the REX side (the new part):

1. Store 0x12345678 at base + 0xc: this is `XSTARTI`. Only its low 12 bits stick (the ide register test masks it with 0xfff).
2. Store 0 at base + 0: `COMMAND` = no-op.
3. Read base + 0x800: the GO alias of `COMMAND`; this executes the no-op, which also makes the chip capture the pending coordinate.
4. Read base + 0x14: `XSTART`, the combined integer-and-fraction start x. It returns the 12-bit integer in bits 26:15:
   0x678 << 15 = 0x033c0000, the value the probe compares with. A flat read/write register at that offset cannot pass; a model
   needs XSTART to derive from XSTARTI (and the PROM expects the same on the second head). Established from `lightProbe`
   (`light_init.o`) and the PROM probe at 0xbfc0f9a8 (4.0.5D) / 0xbfc12858 (4.0.5G), as the page above records.
5. Before step 1 the kernel's `lightProbe` waits for `CONFIGMODE` bit 0 (busy) to clear, polling up to 300000 times: a board
   that is stuck busy is treated as absent. The PROM's probe has no wait (it stores first, reads later).

NetBSD probes differently: it requires the `XYWIN` register to read 0x08000800 (its `XYOFFSET`) after the PROM has
initialised the board. A model that initialises `XYWIN` to 0x08000800 on first PROM access passes both; a model whose
`XYWIN` resets to 0x08000800 passes NetBSD without help. The reset value of `XYWIN`: unknown (no shipped code reads it before
writing it).

## What the PROM does (IP20 4.0.5D and 4.0.5G)

Mostly established; the PROM routines are read by listing, function by function for the routines named, with the larger
initialisation function (0xbfc0fd00, 4.0.5D) matched against the kernel's by its stores rather than read line for line, so the
claim "the PROM initialises the board exactly as the kernel does" is **inferred**.

- **Probe loop.** A table at 0xbfc4d1f0 (4.0.5D) lists the board addresses 0xbf3f0000, 0xbf3f8000, 0. The loop at
  0xbfc10320 calls the probe (0xbfc0f9a8) on each, stops at the first board found, saves its address at 0xa8741260 and calls
  the board init (0xbfc102a8), which runs, in order: board info (0xbfc0fa00), colour map and clock (0xbfc0fb84), REX and VC1
  (0xbfc0fd00), and the palette entries for the console colours. The second loop at 0xbfc103e8 registers each board found as an
  ARCS display node named `SGI-LG1` with a `LG1MC` string and the display type constants; the strings are at 0xbfc4d220 and
  0xbfc4d228 (4.0.5D). The GR2 probe is tried first on the console path (callers 0xbfc0f6dc and 0xbfc0f814 in the chips
  page) and, if it answers, the LG1 loops are not needed: the order between the two families was not traced.
- **Board info.** `0xbfc0fa00` copies the 16-byte name "LG1MC" into the info block, stores 1024 and 768 as halfwords at
  info + 0x20 and + 0x22 and 0x34 at info + 0x24, reads the `WCLOCK` configuration byte (revision at info + 0x28, monitor
  type at info + 0x2b, a flag at + 0x2c set when bit 6 of the byte is clear), runs the pixel-memory probe (info + 0x29) and
  the VC1 revision read (info + 0x2a). The same fields in the kernel's board info structure are what `lightInfo` copies to user
  space: 0x34 bytes in all. **Established** for the layout as stored; unknown: what each of the three codes at + 0x29 means.
- **Console function table.** The PROM exports ten routines in a table at 0xbfc54040 (4.0.5D); 4.0.5G has its own copy at a
  different address. In table order, with addresses in 4.0.5D: blank/unblank (0xbfc2d430: `CONFIGSEL` 6 read-modify-write
  of VC1 SYS_CTL bit 2), set foreground colour (0xbfc2d4b0: store at 0xa87456b8, `COLORREDI` = colour), set one palette entry
  (0xbfc2d4e8), fill rectangle (0xbfc2d5c0: command 0x30000329), plot point (0xbfc2d620: 0x30000001), set current position
  (0xbfc2d670: store at 0xa87456b0, 0xa87456b4), draw bitmap (0xbfc2d684: the glyph blit, below), copy rectangle
  (0xbfc2d9f8: `XYMOVE` plus 0x30080329, for scrolling), report screen size (0xbfc2dab0: returns the 1024 and 768 halfwords stored
  in the board info), set cursor position (0xbfc2dad0: VC1 registers 0x22 and 0x24). **Established** for each routine's
  stores as listed (read through the whole routine).
- **Font blit path.** The PROM's console draws text with the drawing-bitmap routine: for a glyph at the current position it
  loads `XSTARTI` (x minus the glyph origin), `YSTARTI` (767 minus the y position, offset by the glyph origin), `XENDI`
  = x + width - 1 and `YENDI` = 0, writes the `COMMAND` GO alias with 0 (a no-op that latches the coordinates), writes the
  `COMMAND` 0x300005b9 (width up to 16 pixels: one command, then one `ZPATTERN` GO write per glyph row, the row's 16 bits in
  the top half) or the `a1`/`a9` piece commands (wider glyphs), then advances the current position by the glyph's advance.
  The glyph pixels come from a bit-per-pixel bitmap in the PROM image; transparent background. Screen scrolling uses the copy-rect
  routine, clearing uses fill-rect. **Established** for the register sequence; the PROM's own font and the console geometry
  (rows, columns) were not extracted: see the open questions.
- **What it probes first**: the REX probe described above, before anything else is written; the monitor type and revision are
  read in the board info step and decide the colour map path (revision below 2: Bt479 path).

## What IRIX does (6.5 IP20boot `lg1.a`)

Established from the member objects; the function names are the objects' own symbols.

- `lg1_earlyinit` (called early in boot): loops over the two-entry board table in `light.o` (addresses 0xbf3f0000 and
  0xbf3f8000 as kseg1 words), calls `lightProbe` on each and, for boards found, either only reads the board info and sets up the
  cursor (when the PROM console is on this board: the console argument's first byte is 'g' and the board has been initialised
  once already) or runs `lightInit` in full; then registers the board's `htp` function table (`lg1_htp_fncs` for revision
  below 2, `lg2_htp_fncs` otherwise) for the kernel's own console text path.
- `lg1_init`: allocates a 0x124-byte per-board structure for each board found, records it in the inventory (class 7 graphics,
  type 10, controller number), initialises its retrace state (`lightRetraceInit`), registers it with the graphics manager
  (`GfxRegisterBoard`), then sets bit 3 of the INT2 port register to enable retrace interrupts (with a bus flush) and installs
  `lightFIFO` on GIO line 0 and `lightRetrace` on line 2.
- `lightRetrace`: counts, calls the retrace handler, then pulses INT2 port register bit 3 clear and set to acknowledge. The
  retrace handler (`lightRetraceHandler`) walks 32 swap slots, performs pending buffer swaps by toggling bit 1 of the display-mode
  entry in the VC1 window and runs the retrace callbacks. Established; the VC1 side of what generates the retrace: unknown (no
  shipped code sets a VC1 field for it).
- User-visible entry points (the object's table at `.data` 0x28 onward): info, attach, detach, initialize, download, start,
  position-cursor, create/destroy display-rendering-node, validate-clip, null-clip, map/unmap graphics (`lightMapGfx` maps 0x5000
  bytes: the register file and its GO aliases), pcx swap/switch, swap-buffer scheduling, display mode, suspend, resume, set
  destination planes, set screenmask, get geometry, read display (colour maps and display modes), AUX1 register, private ioctl, and a
  pixel DMA entry. A model that supports the PROM console needs none of these; a model that supports IRIX needs the whole register
  file, the retrace interrupt and DMA.
- **X server.** The X server's LG1 path (the shipped 6.5 X server and the `lg1` direct-draw library) was not located in the
  files held; see the open questions. What an IRIX X server would see is the register page `lightMapGfx` maps, so it uses the
  same registers.

## What a QEMU implementer needs, in order

1. A GIO device at 0x1f3f0000 (32 KiB window) with 32-bit big-endian registers as in the REX1 list, GO aliases at + 0x800, and the
   `XSTART` derived-register behaviour for the probe.
2. `CONFIGMODE` bit 0 reads 0.
3. A clock/config port that returns a board revision below 2 (so the PROM and IRIX take the Bt479 path), a monitor type, and bit
   6 = 0 (video board present).
4. The `CONFIGSEL`-addressed ports: write storage for the colour map (256 x 3 bytes, bank 0 enough for the PROM), the VC1 SRAM
   (at least 0x4900 bytes), the VC1 revision window (return a value whose low three bits are not 0 or 1; software subtracts one, and a result of 0 skips VC1 initialisation), SYS_CTL.
5. An 8 bpp 1024 by 768 frame buffer scanned out through the colour map (video on = SYS_CTL bit 2).
6. Commands 0x30000329, 0x30080329, 0x30000001, 0x300005b9, 0x300005a1/0x300005a9, with the y-up convention, and the plain
   register store semantics for everything else.
7. For IRIX: retrace interrupt (GIO line 2, INT2 local 1 bit 7, with the port register bit 3 acknowledge), the FIFO interrupt on
   line 0 optional, the pixel DMA entry and the pixel-memory probe (RWAUX1 sequence) or a way to return one of its three outcomes.

## Review (2026-11-23)

Independent review against `lg1.a`, the 4.0.5D and 4.0.5G PROMs, the IP20 `ide` image and the Library photograph; the register-level verdicts are in the
[REX1 review](../../devices/rex1/README.md#review-2026-11-23). Board-level results:

- **Probe, board order, revision rule (CONFIRMED).** The probe table at 0xbfc4d1f0 holds 0xbf3f0000, 0xbf3f8000, 0. `lightInit` chooses `initBt479` for revision below 2 and
  `initLUT1` otherwise, then `initVC1` only if the VC1 revision byte is above 0. Init order in the kernel: `initRex`, `rexClear`, `lightInitInfo`, `rexClear`, `initClock`, colour map, VC1.
- **Chip markings (GRADE kept: observed).** The photograph reads `L1A6654 VC1 REV B` and `L1A6651 LUT1 REV A`, board `030-8077-004 REV A`: correct. The REX package, which the first
  version called illegible, reads `LSI LOGIC`, a part-number line (L1A67x1, digits uncertain), `REX1.5`, `REV. A` (observed). The "Bt" package beside the LUT1 is observed but its
  part type is not legible; its presence on a board that also carries the LUT1 means the photograph alone cannot say which variant a given revision uses.
- **PROM console font and geometry (new, partly settled).** The PROM builds four font records at RAM 0xa8745720 (builder at 0xbfc318a8), 12 bytes each: bitmap pointer, glyph table
  pointer, then two halfwords (cell height and descent). Glyph records are 8 bytes: halfword offset into the bitmap in halfwords, width, height, signed x and y origin
  (negated before use), halfword advance. Bitmap rows are padded to 16 bits. Font 0: bitmap 0xbfc542c0, table 0xbfc5535c, 17 and 4, 9 pixel advance, 190 glyph records
  (index = code - 32, or code - 66 when bit 7 of the code is set). Font 2: 0xbfc559dc, table 0xbfc5693c, 23 and 5, 19 pixel
  advance. Font 3: 0xbfc56c34, table 0xbfc57358, 14 and 3, 9 pixel advance, 9x11 'A'. Codes below 7 select font 1 (a 7-glyph set of box-drawing pieces at table 0xbfc559a4, bitmap 0xbfc5594c).
  The character draw routine is 0xbfc41a14; it fills the descriptor and calls the board's draw-bitmap entry (table entry 6). The PROM's console repaint loop (0xbfc30154) advances 9 pixels per
  character and uses font 0. The window setup function (0xbfc2f864, called with 18178 or 18181) sets cell 9 by 17 and 80 columns, with 36 rows when the screen height is 768
  and 40 otherwise; for 18181 it first runs the 18179 variant (cell height 20, 10 wide, 20 rows). The 4.0.5D data word at 0xbfc42e20 that picks between them is 1, which selects the 18181 chain;
  which variant a 1024 by 768 LG1 console finally uses was not fully traced: **unverified**. The font bitmaps themselves were decoded (the 'A' and 'g' glyphs render correctly).
