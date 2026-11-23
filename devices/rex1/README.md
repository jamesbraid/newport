# REX1 raster engine (Indigo Entry graphics board, LG1)

REX1 is the drawing chip on the Indigo's Entry graphics board. It takes coordinate, colour and command writes from the CPU over
GIO32 and fills, copies and plots pixels in an 8-bit-per-pixel 1024 by 768 frame buffer, and it is also the access path to the
board's video controller ([VC1](../vc1/README.md)), colour map ([Bt479 / LUT1](../bt479/README.md)) and pixel clock. The register
list is in [registers.md](registers.md) (source `registers.toml`); this page is the working model a QEMU implementer needs.
Board-level facts (slot, probing, interrupts, what the PROM and IRIX do) are in the [LG1 board page](../../platforms/lg1/README.md).

Grades follow [AGENTS.md](../../AGENTS.md). Sources, in the order used: the IRIX 6.5 IP20 boot object `lg1.a`
(members `light.o`, `light_init.o`, `light_tp.o`, `light_retrace.o`, `light_dma.o`, decompiled in Ghidra through the retools
submodule and cross-read as MIPS assembly), the IP20 PROMs 070-8116-004 (4.0.5D) and 070-8116-005 (4.0.5G), the IRIX `ide`
diagnostic for the IP20 (the REX register test and its register-name strings), and the NetBSD sgimips `light.c`/`lightreg.h` (a
public driver; software expectation). MAME's `light.cpp` was read afterwards as a note from another project; its offsets and
command values agree with what is written here and it supplied none of it. The chip's revision as read by software:
`WCLOCK` bits 2:0, see below. Nothing was measured on a board.

## Identity and what software can learn

- **Chip marking, observed** in a photograph of an LG1 board (Library
  `photos/sgistuff-indigo/indigo-lg1a-1001.jpg`): the large LSI Logic gate-array package on the right-hand half of the board
  (beside eight small memory parts) is marked "LSI LOGIC", "REX1.5", "REV. A" (**observed**, read at high magnification, text upside down on the board as photographed). The part number line above it reads L1A6761 or a near misprint of it: treat the digits as **unknown**. The software name "REX" (lightProbe's board info, the ide test's "REX register r/w test") is **established**.
- **Revision as software sees it.** `WCLOCK` read with `CONFIGSEL` = 4: bits 2:0 are a board revision. The kernel takes
  `rev < 2` to be an LG1 (Bt479 colour map, first clock table, `htp` function table `lg1_htp_fncs`) and `rev >= 2` an LG2
  (LUT1 colour map, second clock table, `lg2_htp_fncs`). Bits 5:3 are a monitor type (6 selects a variant of the colour map
  command word) and bit 6 set means "no video board". NetBSD agrees about the `rev < 2` rule. **Established.**
  Values a real board returns: **unknown**.
- A second "head": a second board at the next 0x8000 (`0x1f3f8000`). Established that both addresses are probed; whether a
  real second board works with IRIX: the kernel keeps a per-board table of two entries, so the code path exists.

## Address model

Established. The board occupies at least 32K of the GIO graphics slot (NetBSD maps 0x7fff bytes; the kernel maps 0x5000 bytes
to a user process, so the register file ends below 0x5000). Three kinds of location:

1. **Drawing registers** at 0x000 to 0x08c, 32 bits each (see the register list).
2. **Configuration registers** at 0x4790 to 0x47ff.
3. **GO aliases**: every register at `x` is also at `x + 0x800`.

A write to a SET address (`x`) stores the value and does nothing else. A write to the GO address stores the value and then
runs the command word that is currently in `COMMAND`. A *read* of a GO address also runs the command (without a store): the
PROM's board probe reads GO address 0x800 after storing a no-op command at 0x000, and NetBSD's rectangle fill ends with a read
of the command GO address. For the off-chip ports the GO alias is the "do it" strobe: writes to GO transfer the byte, a read of
GO starts a read cycle (see below). A qtest can discriminate: a drawing register written at SET draws nothing, the same
register written at GO draws; reading GO draws too.

**Byte lanes.** Every access is a 32-bit load or store; shipped code never uses narrower accesses to this board (not read in
full for every driver path: the X server was not examined). Values are big-endian words as the CPU sees them.

## Busy handling

Established. The engine has a busy flag at `CONFIGMODE` bit 0. Before every drawing sequence the kernel and the PROM spin
reading it until it clears. The probe polls it up to 300000 times with a one microsecond delay each, and treats a board whose
busy bit never clears as absent (`lightProbe`). Cursor and retrace code also wait for `CONFIGMODE` bits 28:24 to clear, which is
**inferred** to be a count of commands still in the board's FIFO. A model that completes drawing synchronously (busy always
reads 0) satisfies all shipped code.

The kernel has a FIFO-full interrupt on GIO line 0 (INT2 local 0 bit 0): `lightFIFO` clears the mask bit, spins until the status
bit falls (up to 300000 microseconds), counts it in a statistics field and re-enables the mask; a timeout prints "lg1: REX fifo
timeout." and kills the offending process. Established that this is the only user. What raises the interrupt (the REX FIFO
above a threshold; the driver exposes the thresholds `mg1_hiwater` = 0 and `mg1_lowater` = 4 as global variables that nothing
in this object reads) is **inferred**. A model may never assert it.

## Drawing model

All established from what the shipped code issues; the chip's behaviour for commands the code never issues is unknown.

- **Coordinates.** XSTARTI, YSTARTI, XENDI, YENDI are 12-bit integers; software sets y = 767 - row, so the origin is the
  bottom-left. `XYWIN` is initialised to 0x08000800 and a board answering anything else in that register is rejected by
  NetBSD's match routine. `SMASK1X/1Y` clip to a rectangle of 10-bit fields; the other three screen masks are for window
  context switches.
- **Colour.** Foreground is an 8-bit index in `COLORREDI`. Background in `COLORBACK` is used only by NetBSD with ZOPAQUE.
- **Write mask.** `RWMASK` (set to 0xff by init) gates which planes a pixel read/write touches. `AUX2`'s top three bits select a
  destination group (`lightSetDestinationPlanes`); how a model should honour them: **unknown**.
- **Logic op.** Bits 31:28 of the command. Only value 3 (replace) is ever issued.

### Commands the software issues (full list)

| Word | Meaning | Issuer |
|---|---|---|
| `0x00000000` | no-op; latches coordinates | PROM and NetBSD before a glyph, board probe |
| `0x30000329` | solid rectangle XSTARTI..XENDI by YSTARTI..YENDI in the foreground colour | kernel `light_sboxfi`, PROM clear/fill, NetBSD fill |
| `0x30080329` | rectangle copy: destination is the rectangle, source is displaced by `XYMOVE` | PROM scroll, NetBSD copy |
| `0x30000001` | one pixel at XSTARTI, YSTARTI | kernel `light_pnt2i`, PROM |
| `0x300005b9` | glyph row up to 16 wide; each write to `ZPATTERN` GO draws one row, y steps down | kernel `light_drawbitmap`, PROM |
| `0x300005a1` / `0x300005a9` | wide glyph: pieces of up to 16 pixels, last piece (`a9`) ends the row | kernel `light_drawbitmap` |
| `0x30200021`, `0x30210021`, `0x30200023` | pixel-memory read/write used by the board's memory probe | kernel `lightInitInfo`, PROM |

Pixel result, where the code makes it clear: the rectangle commands set every pixel in the closed range [XSTARTI, XENDI] x
[YSTARTI, YENDI] to the colour (NetBSD's comment says the end coordinates are inclusive; the PROM clear writes XENDI = 1023 and
YENDI = 767 through the stored 767 - y form). A pattern draw with ENZPATTERN and XYCONTINUE writes one row per `ZPATTERN` GO
write: pattern bit 31 maps to the start x, bit 30 to x+1, and so on up to the span end; one-bits are painted with the
foreground colour; zero-bits leave the pixel unchanged (no ZOPAQUE) in the shipped kernel and PROM, and take `COLORBACK` with
ZOPAQUE (NetBSD only). After each `ZPATTERN` write the y moves one row down and x returns to the start (the `XYCONTINUE` state).
Established for the shipped use; the exact y-step rule at the screen edge is unknown.

The copy: source x and y are the destination's plus the `XYMOVE` halves; the copy direction is chosen by software so
overlapping scrolls work (the PROM and NetBSD arrange start and end y so that the engine runs the right way), so the model needs
overlap-safe copying only for those.

### What each shipped routine does per call

| Routine | Register writes |
|---|---|
| `light_sboxfi(x0, y0, x1, y1)` | busy wait; `YENDI` = 767 - y0; `YSTARTI` = 767 - y1; `XSTARTI` = x0; `XENDI` = x1; command 0x30000329 at GO (for y0 <= y1 the stored YSTARTI <= YENDI) |
| `light_pnt2i(x, y)` | busy wait; `XSTARTI`, `YSTARTI` = 767 - y; command 0x30000001 at SET, then a read of the GO alias runs it |
| `light_color(c)` | busy wait; `COLORREDI` = c |
| `light_drawbitmap` | busy wait; XSTARTI, YSTARTI, XENDI = x + w - 1, YENDI = 0; GO command 0; command 0x300005b9 (or `a1/a9` pieces); one `ZPATTERN` GO write per row |

## The off-chip ports

Established. `WCLOCK`, `RWDAC` and `RWVC1` share `CONFIGSEL` as the register index. A write stores the byte in the port and in
its GO alias; a read reads the GO alias, waits, then reads the SET alias (the PROM and NetBSD) or uses the GO read's value
(the kernel colour-map reads). The three chips' registers are in their own pages; here only the REX side is modelled:

| Port | SET / GO | Behind it | Index values seen |
|---|---|---|---|
| `WCLOCK` | 0x47e4 / 0x4fe4 | clock program (write) and board config byte (read) | write with 2; read with 4 |
| `RWDAC` | 0x47e8 / 0x4fe8 | colour map | 0, 1, 2, 3, 6 |
| `RWVC1` | 0x47f0 / 0x4ff0 | video controller | 0 to 6 |

The offsets are given here because this page is prose; the generated register list names the registers.

## Board initialisation and probe, in order

Established for the kernel (`lightInit`, `lightInitInfo`, `initRex`, `rexClear`, `initClock`, `initBt479` / `initLUT1`, `initVC1`)
and, by matching register-store patterns instead of a function-by-function reading, **inferred** for the PROM
(0xbfc0fa00 .. 0xbfc10320 in 4.0.5D):

1. **Reset the board** (optional): clear then set MC `cpuctrl0` bit 10 (graphics reset, active low, each held 5 microseconds).
   The kernel does this only when `lightInit`'s third argument is nonzero; the PROM pulses it on the console path (per the
   chips repository's `platforms/ip20/address-map.md`, which describes the MC side).
2. `initRex`: wait idle; `XYWIN` = 0x08000800; `CONFIGMODE` = 0x807fe000; `AUX2` = 0x20000000; `COMMAND` GO write 0; `AUX1` = 0.
3. `rexClear`: wait idle, write `AUX2` = 0x40000000, wait idle, then `COMMAND` = 0x00000329 (logic op 0 instead of the usual 3;
   a clear is inferred), `XSTATE` = 0x03ff0000, `XSTARTI` = 0, `YSTARTI` = 0, `XENDI` = 0x3ff, and `YENDI` = 0x2ff written at its
   GO alias to run it; then the same again with `AUX2` = 0x20000000. So both destination plane groups are cleared. The role of
   `XSTATE`: unknown.
4. `lightInitInfo`: read the board revision byte and monitor type, read the VC1 revision, run the pixel-memory probe described
   under `RWAUX1`, test the graphics-DMA interrupt with a short DMA to memory, then hand the result to the driver framework.
5. `initClock`: write the 17 clock bytes.
6. `initBt479` or `initLUT1` according to the revision, then `initVC1` (unless the VC1 revision read gave zero).

A model that needs only the PROM console can skip steps 1 and 5 and 6 in terms of side effects, but it must (a) answer the
probe with 0x033c0000 at XSTART, (b) present busy = 0, (c) return a sensible board revision, monitor type and VC1 revision, and
(d) accept the colour map and VC1 writes without error. The kernel additionally requires the VC1 revision to be nonzero or it
skips the VC1 initialisation.

## What IRIX does after init

Established from `lightPositionCursor`, `lightSetDisplayMode`, `lightSetDestinationPlanes`, `lightPcxSwap`, `lightRetrace*`,
`Lg1PixelDma`. Cursor and display-mode writes go through `RWVC1` as described in [VC1](../vc1/README.md). A window context
switch (`lightPcxSwap`) saves 40 words of drawing and screen-mask registers of the outgoing window into its context and loads the
incoming window's, writing the drawing registers at their SET offsets and `CONFIGMODE` last. Pixel DMA (`Lg1PixelDma`) programs the
MC's virtual DMA engine to move user pixels to the board, with `CONFIGMODE` = 0x807fe000 held for the transfer and restored
afterwards; the board side of that DMA (which register the MC writes into) is not read, see the open questions.

## Comparison with the NetBSD driver (public driver, software expectation)

NetBSD's `light.c` agrees with every register offset and command value above that it uses, and adds three things: it probes by
reading `XYWIN` (0x08000800), it names the board revision register `WCLOCKREV` and the selector `CFGSEL`, and it uses ZOPAQUE
glyphs. It never programs the colour map. All differences with this page are noted in the register list; none contradicts it.

## Open

Filed in [questions/README.md](../../questions/README.md): what the command bits 21 and 16 do; what `CONFIGMODE` bits 31 and 22:13 are; the digits of the REX chip's part number; the
format of `RWAUX1`'s memory-probe outcome.

## Review (2026-11-23)

Independent review of the register map and drawing model against `lg1.a` (`light.o`, `light_init.o`, `light_tp.o`), the 4.0.5D PROM
and the IP20 `ide` image, re-disassembled from the shipped objects. Verdicts per claim:

- **Probe (CONFIRMED).** `lightProbe` and the PROM probe (0xbfc0f9a8) store 0x12345678 at +0xc, 0 at +0x0, read +0x800, read +0x14 and
  compare with 0x033c0000. 0x678 << 15 = 0x033c0000. The ide test confirms the derivation directly: it writes +0xc and reads +0x14
  expecting (value & 0xfff) << 15. Correction: the PROM probe calls a one-instruction return between the GO read and the compare, so it
  has no real delay, as already written. Whether XSTARTI at +0xc itself reads back is **unknown**: neither the probe nor the ide test reads it.
- **SET/GO and busy (CONFIRMED).** `light_pnt2i` and the PROM fill/point routines store the command at SET and then *read* the GO alias;
  the fill/glyph/copy paths write GO. Busy is `CONFIGMODE` (0x47f8) bit 0 in every routine. The kernel's `lightProbe` wait is 300000 iterations of a
  1 microsecond delay and comes before the probe stores.
- **Commands (CONFIRMED).** 0x30000329, 0x30080329 (PROM copy at 0xbfc2d9f8: command at SET, XYMOVE written at 0x834), 0x30000001,
  0x300005b9 and the 0x300005a1/0x300005a9 piece loop are as listed. **WRONG** in the first version: the `light_sboxfi` row had the y stores swapped.
  The code stores `YSTARTI` = 767 - y1 and `YENDI` = 767 - y0 (arguments x0, y0, x1, y1), the PROM fill does the same, so YSTARTI <= YENDI for y0 <= y1.
  The kernel's `light_pnt2i` also reads the GO alias after storing the command at SET.
- **CONFIGSEL port sharing (CONFIRMED).** WCLOCK, RWDAC and RWVC1 use it. The board revision, monitor type and bit 6 are read with CONFIGSEL 4 (GO read, 1 microsecond,
  SET read); bit 6 clear stores 1 in the info word at +0x2c. The VC1 revision read is CONFIGSEL 3 after the address counter was set to 5. `initClock` writes the selector through its
  GO alias (0x4fec). Not a fault: `lightInit` runs `rexClear` twice, the second after `lightInitInfo`, whose pixel-memory probe leaves pixels behind.
- **Offsets named only by the ide test (UPGRADED to established).** The ide test at 0xa853d968 calls a helper (0xa853d670) with the write offset, the read-back offset, the
  name, a mask and a shift, and all 41 offsets are now read directly. Every inferred offset was right. Findings that change the model: XSTARTF (0x10), XENDF
  (0x18), YSTARTF (0x20), YENDF (0x28) are not fractions; the test reads XSTART/YSTART back after writing XSTARTI/XSTARTF and reads XENDF/YENDF back after
  writing XENDI/YENDI (shift 11, mask 0xfff), and COLORREDI/GREENI/BLUEI (0x38/0x40/0x48) read back through COLORRED/GREEN/BLUE (0x3c/0x44/0x4c)
  as (value & 0xff) << 11. The slope registers (0x50 to 0x58) read back sign-adjusted (bit 19 copied to bit 20). The six SMASK2 to SMASK4 words are named
  by the ide test's own offsets (0x4790 to 0x47a4), and are now all in the register list. After each write the test stores 0 at 0x800 three times (a no-op command at GO),
  so a model that derives read-back values at GO time passes; one that derives them on every write passes too.
- **Start-up (CONFIRMED)** for the kernel stores in `initRex`, `rexClear`, `initClock`, `lightInitInfo`; the PROM `initRex`-equivalent matches store for store.
- **Not settled.** `CONFIGMODE` bit 31 inversion and bits 22:13, command bits 21 and 16, the `RWAUX1` outcome meanings.
