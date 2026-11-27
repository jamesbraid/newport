# REX3 byte lanes: register, display-bus and pixel-port writes, and a little-endian CPU

Which bytes of a 32-bit store REX3 takes for its registers, for `DCBDATA0` and for `HOSTRW0`; what the Indy and Indigo2 memory
controller and data multiplexer do to a store on the way; and what a CPU that runs little-endian (an NT kernel on the Indy, after
the PROM's endian flip) has to write. Scope: REX3 on the Indy (IP24) and Indigo2 (IP22), the 64-bit GIO configuration the shipped
IP22 builds use. The Indigo (IP20) and the R8000 and R10000 Indigo2 boards (IP26, IP28) were not read.

Grades follow [AGENTS.md](../../AGENTS.md). Review 2026-11-27: written from the sources listed at the end; nothing was run on a board
or in an emulator for this page.

## Answer

| Question | Answer | Grade |
|---|---|---|
| Does the memory controller or the GIO path swap bytes for a little-endian CPU? | No. The data multiplexer can only pass a word through, swap the two 32-bit halves of a double word, or copy one half onto both. There is no byte or halfword swap on the CPU-to-GIO path, and a word keeps its numeric value across it. | **established** (published memory controller and multiplexer specifications; chip revisions in [Sources](#sources)) |
| Which bytes does REX3 take, on a big-endian CPU? | Those of the transfer, in address order, starting at the transfer's start byte, `DATAWIDTH` bytes of them for the display bus; a word store of a three-byte quantity puts the first byte in bits 31:24. Three independent drivers agree. | **established** as the drivers' expectation; the start-byte rule behind it is **inferred** |
| What must a little-endian driver do for a 32-bit register? | Store the numeric value. No swap. | **inferred**; the alternative (every register word byte-reversed) is disfavoured, not excluded |
| What must a little-endian driver do for `DCBDATA0` and `HOSTRW0` data that is more than one byte? | **unknown.** The sources leave three candidate rules; [the table below](#what-a-little-endian-driver-stores-under-each-rule) gives the store for each. No shipped software or published source runs REX3 from a little-endian CPU. | **unknown** |

The consequence for a driver that copies the big-endian constants unchanged (`ireg << 24`, `px << 24`) is that it is right only
under rule 2 below, the one an emulator author is most likely to have chosen. Nothing read shows the hardware does that.

## What the published specifications say

All **established** (as statements in the published documents, which are the designers' own; the REX3 specification is revision 1.0
of 13 August 1993):

- REX3's registers are 32-bit words at 4-byte offsets, listed in pairs: `HOSTRW0` at 0x230 is the "most significant word" and
  `HOSTRW1` at 0x234 the "least significant word" of the host data port; `DCBDATA0` (0x240) and `DCBDATA1` (0x244) likewise. A
  write to a register at address plus 0x800 starts a drawing command (REX3 section 3.1).
- REX3 section 4.1: "The REX3 supports both little-endian and big-endian addressing conventions in GIO64 mode." The feature list
  says "Bi-endian support". Nothing else in the 149 pages says what that covers.
- The `HOSTRW` packing figure (REX3 section 3.10) is captioned "big endian format illustrated". No little-endian figure exists. In
  it, one 32-bit transfer occupies the low word of the 64-bit bus, and an unpacked 8-bit pixel sits in the top byte of that word,
  an unpacked 4-bit pixel in the low nibble of that byte, a packed 8-bit transfer holds four pixels with the first one in the top
  byte, and a 32-bit pixel fills the word. The text says RGB fields are ordered with red least significant and blue (or alpha)
  most significant, and "the leftmost field is the first one to be used".
- `DRAWMODE1` bit 11 and `DCBMODE` bit 28 are both named `SWAPENDIAN`, described as the OpenGL `SWAP_ENDIAN` storage attribute:
  the byte order inside short and long packed data is reversed. The chip's interface block diagram shows a "Byte/Short/Word Swap"
  stage on the data path in both directions.
- `DCBMODE` `DATAWIDTH` (bits 1:0: 0 is four bytes, 1 one, 2 two, 3 three) says how many bytes of each `DCBDATA` word go over the
  8-bit display bus, and `ENDATAPACK` (bit 2) sends all four.
- The graphics FIFO carries the GIO transfer's start byte (`GF_STARTBYTE`) and a 32-bit-or-64-bit flag taken from the byte count
  and start byte. The PIO table (REX3 Table 24) gives start byte 0 or 4 and byte count 8 or 4 for a PIO write to the graphics
  side, so partial writes to graphics registers and `HOSTRW` are not specified. The display-bus side is not in that table.
- The GIO64 specification (draft 1.1, April 1992): the bus does nothing different for big and little endian; the byte-count cycle
  carries a "little endian transfer" bit and the starting byte, and the slave address and starting byte are to be read in that
  endianness. A 32-bit transfer places byte 0 in bits 31:24 when big-endian and in bits 7:0 when little-endian; a 64-bit transfer
  does the same across 63:0. "The bit numbering scheme is always little-endian." For a device that cannot switch endianness, "the
  software will be responsible for fixing the data".

## What the Indy and Indigo2 memory controller does

All **established** (published MC and multiplexer specifications):

- The MC answers its own registers at two addresses and the CPU must use the one for its endianness: the word addresses ending in
  4 and 0xc when big-endian, the ones ending in 0 and 8 when little-endian. The MC sits on the low 32 bits of the CPU bus. The
  value of a word is the same either way.
- A CPU write to GIO goes through the multiplexer with one control, `data_sel(0)`: 0 passes the 64-bit CPU bus to the 64-bit GIO
  bus; 1 exchanges the two 32-bit halves. A CPU read passes the GIO bus straight through, or copies the low GIO word to both CPU
  halves (the 32-bit device case), or moves the high GIO word to the low CPU half. None of these touches a byte order.
- The MC has a `LITTLE` control bit that must match the CPU, and drives a big-endian signal to the rest of the machine. That the MC
  copies it into the byte-count cycle's little-endian bit for a CPU access is **inferred** (the specification says the byte-count
  cycle carries the bit, and that the MC drives the address and byte count while the multiplexer drives the data).

So a little-endian word store of value V arrives on the 64-bit GIO bus as V in one half, on the half that the word's address and
the CPU's endianness select, with the little-endian bit set. This is **inferred** from the two specifications read together.

## What the drivers do on a big-endian CPU

The shipped IP22 kernel, the PROM source and the two public drivers all touch `DCBDATA0` the same way. Evidence per source:

| Source | One byte (`DATAWIDTH` 1) | Two bytes | Three or four bytes | Grade |
|---|---|---|---|---|
| IRIX 6.5 IP22 kernel, `initXMAP9` (read in full) | byte store at `DCBDATA0`+3 | not in this function | word store at +0 | **established** for that function |
| Same kernel, `newport_init.o` of `ng1.a`, by instruction pattern | 92 byte stores and 16 byte loads at offset 0x243 from the REX3 base pointer, none at +0 to +2 | 12 halfword stores and 4 halfword loads at 0x242 | 32 word stores at 0x240, no word loads at 0x240, no doubleword store | **inferred** (counted by pattern; the base register was not checked at every site). The other three members (`newport.o`, `newport_retrace.o`, `newport_tp.o`) show the same patterns and no others at 0x240 to 0x243 |
| Linux `newport.h` (v7.2-rc7) | byte at `b3` (+3) | halfword at `s1` (+2) | word | **established** (public driver) |
| NetBSD `newport.c` | word store with the byte in bits 31:24 (`val << 24`), word load shifted right 24 | word store with the pair in bits 31:16, load shifted right 16 | word store, first byte in bits 31:24 | **established** (public driver) |

Read together the three disagree on where one and two byte quantities sit in the word (bits 7:0 and 15:0 against bits 31:24 and
31:16), and all three work on boards. The one reading that fits is that REX3 takes the bytes the transfer actually carried,
beginning at its start byte, in address order: a word store at +0 starts at byte 0, a byte store at +3 starts at byte 3, a
halfword store at +2 starts at byte 2. Loads obey the same rule in reverse. **Inferred**: no source states it, and the start-byte
input of the graphics FIFO in the REX3 specification is the only structural support. It breaks the idea that REX3 reads fixed bit
positions of the word, which is what an emulator that models `DCBDATA0` as one 32-bit register would assume.

Other big-endian facts from the same sources:

- Two-byte colour-map address writes set `DCBMODE.SWAPENDIAN` (Linux `NPORT_DMODE_SENDIAN`, NetBSD `REX3_DCBMODE_SWAPENDIAN`) and
  store the 16-bit index so that the low byte goes to colour-map register 0 and the high byte to register 1. With the bit set the
  pair is sent low byte first. **Established** (both public drivers agree; the colour-map chip is not specified here).
- A mode-table write to the XMAP9 is one four-byte `DATAWIDTH` 0 word: entry index in bits 31:24 then the three mode bytes most
  significant first, since the table is "Big Endian" in the XMAP9 specification (all three drivers; **established**).
- The 16-bit VC2 index-register write is a three-byte transfer, register index in bits 31:24 and the value in bits 23:8
  (`(ireg << 24) | (val << 8)`): all three drivers; **established**.
- Host pixel data at each depth, as the IRIX diagnostics set it up for a big-endian CPU (`ng1visuals.c`, `minigl3.c`, the field is
  labelled "Big Endian" in `ng1visuals.h`; **established** for these diagnostics, **source**):

  | Draw depth / host depth | Unpacked word (`RWPACKED` clear) | Packed (`RWPACKED` set) |
  |---|---|---|
  | 4-bit | pixel in bits 27:24 (mask `0xf << 24`) | eight pixels, first in the top nibble (REX3 figure; **established** as the published figure) |
  | 8-bit | pixel in bits 31:24 (`0xff << 24`) | four pixels, first in bits 31:24 (figure) |
  | 12-bit | pixel in bits 27:16 (`0xfff << 16`) | two pixels, first in the upper halfword (the PROM's depth probe writes `0xabc << 16 \| 0xdef` and reads back `0x0abc0def`; **source** and the kernel's `fbdepth`, both read in full) |
  | 24-bit draw, 32-bit host | blue, green, red in bits 23:0, red least significant (mask `0xffffff`) | same, one pixel a word |

  Linux's console logo path writes an 8-bit pixel as `pixel << 24`; NetBSD writes stipple rows as `bitmap << 24`. The diagnostics
  read a one-pixel packed 8-bit read through a byte pointer on the returned word, which on a big-endian CPU is bits 31:24.
- With `SWAPENDIAN` set the ide DMA test builds each 16-bit packed pixel with its two bytes exchanged against the unswapped
  value, which is the published behaviour (**established** for the diagnostic, **source**).

## The little-endian question

**Unknown.** The routes tried, so nobody repeats them: the REX3 specification in full text (the little-endian statement quoted
above is the whole of it, and the packing figure is big-endian only); the GIO64, MC and multiplexer specifications; the IRIX 6.5.7
Newport sources (`libsk` and the ide diagnostics), searched for `endian`, `little` and `_MIPSEL`: only the `SWAPENDIAN` handling
turns up, so the Newport sources have no little-endian branch (the IP22 PROM source has a little-endian build option for its own
start-up code, in `csu.s`); the 6.5 IP22 kernel's Newport objects, read for their `DCBDATA0` and `HOSTRW0` access sizes only; the
X server module `ng1.so`, read for its depth tables only, not searched for endian handling; Linux and NetBSD, which are big-endian
only for this chip (Linux's IP22 is configured for big-endian CPUs only). The OpenBSD and MAME Newport code was not read. The Library's
Usenet archive and mailing-list inboxes had no hit for a little-endian Newport driver. The specification of the colour-map chip is
not held, and the RAMDAC specification (`erikarn-bt445_ramdac.pdf`) is an image-only PDF that was
not read.

Three rules cover everything the sources leave open. Rule 1 is what the GIO64 text and the "addressing conventions" sentence most
naturally mean; rule 2 is what an emulator that applies the CPU's lane view to word stores does; rule 3 is a byte-reversal done in
the chip. Grades are **unknown** for all three; "disfavoured" below is a judgment, not a finding.

1. **Address order, numeric words.** REX3 reads the little-endian bit and the start byte; byte *n* of a transfer is the byte at
   address *n*, which a little-endian CPU has in bits 8n+7:8n. A whole 32-bit register or 32-bit pixel is its numeric value.
2. **Fixed lanes.** REX3 ignores the endian bit for data and applies its big-endian lane map unchanged: start byte *n* is read
   from bits 31-8n:24-8n of the word, and the word is numeric. A word store then behaves exactly as on a big-endian CPU, and a
   little-endian sub-word store lands in the wrong lane (the byte store at +3 that Linux and the IRIX kernel issue would put its
   byte in bits 31:24 where the chip looks at bits 7:0). An emulator that hands a CPU word store to its register model unchanged and mirrors sub-word lanes matches this rule (the iris Indy
   model is reported to work that way; not read for this page, and an emulator's choice is not evidence).
3. **Memory image.** REX3 reverses the bytes of every 64-bit bus word when the endian bit is set, so each multi-byte register
   and pixel is a byte-reversed number. **Disfavoured:** it makes every 32-bit register differ between the two CPU modes, which the
   MC and GIO specifications read above do not do for any device they describe.

### What a little-endian driver stores under each rule

Derived from the rules, not observed. `V` is the value the big-endian code stores; `bswap` reverses the bytes of the width named.

| Access | Big-endian code | Rule 1 | Rule 2 | Rule 3 |
|---|---|---|---|---|
| 32-bit register (`DRAWMODE0`, `XYENDI`, and so on) | word `V` | word `V` | word `V` | word `bswap32(V)` |
| `DCBDATA0`, 1 byte `b` | byte at +3, or word `b << 24` | byte at +3 (same address, value `b`), or word `b` | word `b << 24` only; sub-word stores are wrong | as rule 1 |
| `DCBDATA0`, 2 bytes `h` | halfword at +2, or word `h << 16` | halfword at +2 of `bswap16(h)`, or the same halfword with `h` and `DCBMODE.SWAPENDIAN` | word `h << 16` | as rule 1 |
| `DCBDATA0`, 3 or 4 bytes | word `V` | word `bswap32(V)` | word `V` | word `bswap32(V)` |
| `HOSTRW0`, unpacked 8-bit pixel `p` | word `p << 24` | word `p` | word `p << 24` | word `p` |
| `HOSTRW0`, packed 8-bit, four pixels in order `p0..p3` | `p0<<24 \| p1<<16 \| p2<<8 \| p3` | `p0 \| p1<<8 \| p2<<16 \| p3<<24` (the word a little-endian load of the pixels in memory order gives) | as big-endian | as rule 1 |
| `HOSTRW0`, packed 12-bit pair | `p0 << 16 \| p1` | `p0 \| p1 << 16` | as big-endian | as rule 1 |
| `HOSTRW0`, 32-bit pixel (24-bit draw depth) | word `A<<24 \| B<<16 \| G<<8 \| R` | same number | same number | `bswap32` of it |

What a driver can do without knowing the rule:

- Use only word stores of the numeric big-endian constants for registers (right under rules 1 and 2). Probe for rule 3 once at
  start: the PROM's own probe, which stores `0x12348765` to `XSTARTI` and expects `(0x12348765 & 0xffff) << 11` from `XSTART`, reads
  back differently under rule 3.
- Use the 32-bit host format (`HOSTDEPTH` 32) for pixel data at any draw depth; it is numeric under rules 1 and 2.
- Settle rule 1 against rule 2 at start with a read-back of a display-bus register that holds one byte and nothing else changes
  it: the XMAP9's cursor colour-map MSB register (CRS 3, 8 bits, read-write, "never modified by the XMAP9" per its specification).
  Write 0x5A as the word `0x5A` and read the word back; if that fails, write `0x5A000000` and read. A driver would then carry the rule
  it found. **Inferred** and untried; a fixed-lane model such as iris's cannot tell the two apart.

What would settle it: a published description of REX3's GIO pad logic, the chip's source, or a recorded run of a little-endian
CPU against real REX3. No hardware is available and none is planned; see [AGENTS.md](../../AGENTS.md).
Entered in [questions](../../questions/README.md#rex3-and-newport-from-a-little-endian-cpu).

## Sources

- REX3 Specification, revision 1.0, 13 August 1993 (Library `library/cache/graphics/indy/erikarn-sgi_indy_rex3.pdf`): sections 1.3, 3.1,
  3.1.1.2, 3.1.1.7, 3.10, 3.13, 4.1, 5.1 and the DDA port table; page 79 figure read as an image.
- GIO Bus 64 specification, version 1.1 draft, 7 April 1992 (`erikarn-sgi_indy_gio64.pdf`): sections 2, 4.2.1, 4.8 to 4.12.
- MC Chip Specification (`erikarn-sgi_indy_mc.pdf`), sections 1.3, 2.4, 2.5, 3.2, the register map notes and the CPU control register;
  MUX Chip Specification (`erikarn-sgi_indy_dmux1.pdf`), section 1.4. Both describe the first MC and multiplexer revisions; that the
  Indy and Indigo2 parts match them is **inferred** (the MC revision register distinguishes revisions A and B in the MC text).
- IRIX 6.5.7 source tree: `stand/arcs/lib/libsk/graphics/NEWPORT/ng1_init.c` (`Ng1Probe`, `getfbdepth`),
  `stand/arcs/ide/fforward/graphics/NEWPORT/ng1visuals.c`, `ng1visuals.h`, `minigl3.c`, `newport_init.c`, and
  `stand/arcs/IP22prom/csu.s`, `r4k_eerom.s`.
- IRIX 6.5 base media: `usr/cpu/sysgen/IP22boot/ng1.a` (members `newport_init.o`, `newport.o`, `newport_retrace.o`, `newport_tp.o`),
  `usr/lib/X11/dyDDX/ng1.so`; hashes in [irix-files.md](../../references/irix-files.md).
- Linux v7.2-rc7 `include/video/newport.h`, `drivers/video/console/newport_con.c`; NetBSD `sys/arch/sgimips/gio/newport.c` and
  `newportreg.h` (tree at `07004b2a9dac`).
