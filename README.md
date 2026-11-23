# newport

Notes on the SGI Newport graphics family: LG1 (Indigo Entry, REX1) and Newport (REX3, with VC2, XMAP9, CMAP and Bt445) in the Indy and Indigo2, and the IRIX code that drives them.

Nothing is written yet beyond the workspace layout. Every fact will note the binary, document or public driver it came from and whether it is established, inferred or unknown.

## Layout

- `devices/`, `formats/`, `platforms/`, `software/`: chip, data-format, board and IRIX-side pages.
- `references/`: what we hold and cite.
- `generated/`: tool output built from the register maps.
- `questions/`: open questions.
- `retools/`: shared tooling (submodule).

Working rules are in [AGENTS.md](AGENTS.md).

## REX1 and REX3

LG1's REX1 and the Indy and Indigo2's REX3 are named alike and the shipped software treats them alike in places. These are the
lineage claims that can be graded today. All are **inferred** unless a source is named; no source states that REX3 descends from
REX1, so none of it is established lineage.

- **A public driver says it.** NetBSD's `light.c` (sgimips, public) states, in its header comment, that "Light's REX chip is
  the precursor of the REX3 found in newport, hence much similarity exists". That is a driver author's remark (a statement
  from a public source, not a hardware document).
- **Shared register names.** Names that appear in both chips' registers, per the shipped IRIX software and NetBSD's two drivers:
  `XSTARTI`, `XSTART`, `XYMOVE`, `COLORBACK`, `ZPATTERN`, `LSPATTERN`, `LSMODE`, `SMASK1X` to `SMASK4Y`, `XYWIN`. The REX3 page
  names also `DRAWMODE0`, `DRAWMODE1`, `COLORI`, `WRMASK`, which REX1 does not have under those names. REX1's single `COMMAND`
  word (opcode, flags and logic op in the high nibble) corresponds in role to REX3's `DRAWMODE0` plus the GO write.
- **Shared access model.** Both have a SET address and a GO alias 0x800 above it (REX1 offset + 0x800; REX3 `REX3_REG_GO` =
  0x800). Both execute the pending command when a register is written at the GO address. REX1 also executes it on a read of
  the GO address; REX3's behaviour on reads of GO is not read here.
- **Different layouts.** The offsets of the shared names differ (REX1 `XSTARTI` 0x0c, REX3 0x148; REX1 `XYMOVE` 0x34, REX3
  0x114), the REX3 screen masks live at 0x1300 and up against REX1's 0x7c/0x80 and 0x4790 onward, and REX1's pixels are 8 bits
  with the stored y counted from the top of the screen (see the REX1 page) while REX3's drawing modes include a `YFLIP` bit. Nothing in this repository shows the
  register layouts were derived from each other.
- **Off-chip chips differ.** REX1 reaches VC1, a Bt479/LUT1 colour map and a clock port through three ports sharing `CONFIGSEL`;
  REX3 reaches VC2, XMAP9, CMAP and Bt445 through its display-control bus (`DCBMODE`/`DCBDATA`). The VC1 and VC2 share a name
  prefix; whether VC2 is a successor of VC1 is not read here and not claimed.
- **Where to read next.** The REX1 reading is in [devices/rex1](devices/rex1/README.md) and the board in
  [platforms/lg1](platforms/lg1/README.md). The REX3 side has no page yet.
