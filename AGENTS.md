# SGI Newport and LG1 reverse engineering

This project reverse-engineers the SGI Newport graphics family and publishes the result as register maps, generated headers and chapters, so that FPGA builders, driver writers, emulator authors and the vintage SGI community can work from findings instead of binaries.

The layout and working style follow [gr2](https://github.com/techomancer/gr2) and [gr4](https://github.com/techomancer/gr4) by Dominik Behr, as the sibling workspaces kona and odsy do. Where this file is silent, do what gr4 does.

## Scope

Two generations of the same drawing engine:

- **LG1** (Indigo Entry graphics), built on the REX1 raster engine.
- **Newport** (XL, Indy and Indigo2), built on the REX3 raster engine with the VC2 video controller, XMAP9 mode and overlay mapper, CMAP palette chips and the Bt445 DAC.

Each board revision and each host (Indy IP22, Indigo2 IP22/IP26/IP28, Indigo IP20) is its own configuration: a fact from one does not fill a gap in another. Block names (REX1, REX3, VC2, XMAP9, CMAP, Bt445) are names from the software and published manuals; each role stays unknown until a labelled description replaces it.

Every fact is labelled **established** (read in full from a binary, the IRIX source or a published document, with function, offset or path), **inferred** (a reasoned reading, with the reasoning) or **unknown**. Anything unlabelled is unknown. Do not fill gaps from memory, from other SGI graphics families or from other reimplementations.

## Binaries

Proprietary SGI binaries are not committed (`root/` is gitignored). Copy them from an authentic IRIX distribution into `root/` as `references/irix-files.md` lists once it exists. Disassembly, decompiled C, headers and notes derived from the binaries are committed. Flat `*_disasm.txt` and `*_dwarfdump.txt` dumps are gitignored.

## Other public sources

- Public OS drivers and emulators that drive Newport: Linux (`drivers/video/fbdev/newport_con.c`, `arch/mips/sgi-ip22`), NetBSD and OpenBSD (`arch/sgi`, the `newport` driver), MAME (`newport.cpp`), and the XFree86/X.Org Newport driver. They show what a working driver expects, not what the hardware does.
- `references/documents/` holds full copies of the published patents, papers, manuals, datasheets and web pages the project cites, each with its SHA-256. They are published designers' statements, graded "established (published)" or "inferred".
- Code submodules, when added, live under `references/code/`.

## Evidence order

Take each fact from the highest source that states it and grade it by that source. The order, the reset-value grading, the hardware-read limit and the checks that enforce them are in `retools/tools/README-analysis.md#evidence-order`. In short: IRIX source, shipped binaries, public OS drivers, published manuals, then other projects' notes, which may confirm or contradict but never supply a fact. A physical hardware read is a last resort and needs the repository owner's approval. Emulator runs are model behaviour, never hardware evidence.

## Evidence: software only

No hardware is available. Do not plan, request or wait for measurements on a real machine. A row is not finished while shipped software or published material still has something to read. Readers may open every shipped binary on every IRIX release, the linked IRIX source tree, vendor specifications (including embedded source or HDL pages), public drivers and emulators, manuals, release notes, man pages and published output from real machines (`hinv`, `gfxinfo`, ide transcripts, X logs, screenshots in posts, archives and forums).

- What the software touches and expects back is the driver's expectation, not proof of hardware behaviour. A fact resting only on a simulated run is `inferred` or `unknown`.
- Write findings in your own words. Never paste vendor source, HDL or proprietary binaries. Never copy source text, comments, macro bodies or internal identifiers from the IRIX source tree, and do not compare a routine with it in committed text. Symbol names from a shipped binary's own tables or debug info, and names in published headers and manuals, are fine.
- Before calling a fact unknown, search the shipped binaries, documents, captures and source tree for the device, its diagnostics and its PROM code, and list the routes tried.
- `established` only for what you read in full: the whole function body or table, or the whole passage of source or document. A reading built from call lists, register-store summaries, a sibling build or a name is `inferred`. Never reword or reformat an entry to change its grade.
- An entry written quickly and not yet checked against its binary, document or public code (cited by project, revision and file) ends with "Unverified." and grades at most `located`.
- When every route is exhausted, write "unknown: no shipped software or published source depends on it" with the routes tried. Never write "needs capture".
- Record an open question in `questions/README.md` with every route tried and the next one, then carry on with other work. When it is answered, move the answer into the owning chapter or header and delete the entry.

## Output

- Register and word layouts live in TOML: `devices/<unit>/registers.toml` for a chip or board unit and `formats/<name>/format.toml` for a software data structure, each item graded and sourced. `generated/` is built from them and never edited by hand. `registers.md` (`format.md`) beside each source is the reference page.
- To change a fact, edit the TOML, run `retools/tools/defs/defs-gen`, then `retools/tools/defs/ci-check` (the check CI runs), and commit both.
- Prose that does not fit a map goes in a chapter beside the unit it describes, under `devices/`, `formats/`, `platforms/` or `software/`. Directory indexes (`README.md`) are generated by `retools/tools/docs-index`.
- `COVERAGE.md` maps what is written and what is missing once the first inventory exists. Keep its rows true when you change them.
- Commit what you cite, and only what rests on shipped binaries, the IRIX source tree, published documents, captures or public code (cited by project, revision and file).

## Tools

Shared tooling is the `retools/` submodule: `retools/tools/` is shared. Change it there and move the pin here. `tools/` holds only this repository's scripts, and `tools/config/` its data and config. Run tools from the repository root. Clone setup: `git submodule update --init retools`.

## Where new work goes

There is no `evidence/` directory. File each page by what it is about:

- `devices/<chip>/`, `platforms/<board>/`, `formats/<name>/`, `software/<area>/`: a note about one device, platform, format or software component.
- `<subject>/readings/<binary>.md`: per-routine readings of one binary, filed under the subject it explains.
- `references/`: what we hold and cite: binary, PROM and firmware lists with checksums, scope lists, source lists. Code submodules stay under `references/code/`.
- `generated/`: tool output that is regenerated and never hand-edited.
- `questions/`: open questions.

`retools/tools/defs/ci-check` fails when an `evidence/` directory comes back.

## Working rules

- Write names exactly as the binary spells them and put the explanation under a heading.
- Commit small and often, straight to `main`. Subjects are lowercase, component-prefixed imperatives (`rex3: label the draw-mode register`); bodies say why. Do not wait to batch work.
