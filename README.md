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
