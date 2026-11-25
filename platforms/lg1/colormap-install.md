# LG1: how the X server installs a colour map and picks a window's display ID

What the IRIX 5.3 X server does, from an `XInstallColormap` request down to the Bt479 writes and the VC1 mode word, and which
colour-map bank a window ends up in. Written to answer why a private-colour-map client (the desktop's icon windows) shows the
wrong colours when a model displays through the right bank but loads the wrong one, or the reverse. The palette protocol is on
[colour-map banks](../../devices/bt479/banks.md), the DID tables on [VC1: display IDs](../../devices/vc1/did-xmap.md) and the
icon drawing on [desktop icons](desktop-and-overlays.md).

Grades follow [AGENTS.md](../../AGENTS.md). **[binary]** is read in a shipped object, with address; **[source]** is the IRIX
source tree, cited by path; **[inferred]** says what it rests on. Addresses: `lg1mc.so` and `Xsgi` are virtual addresses in the
IRIX 5.3 objects, `lg1.a` members are byte offsets in the 5.3 `IP20boot/lg1.a`, `rrm.o` and `gfx.o` are offsets in the 5.3
`IP20boot` objects (checksums in [irix-files.md](../../references/irix-files.md)). Nothing here was run, and the 6.5 objects
were not compared.

## Answers in brief

| Question | Answer | Grade |
|---|---|---|
| Which bank does an install write? | The bank in the low nibble of the hardware map's table byte: maps 0 to 6 write banks 0, 1, 2, 0, 3, 3, 3. | established |
| How is it selected? | CONFIGSEL 0 and 0x82 to RWDAC, then CONFIGSEL 6 and `(bank << 4) \| 0x0f`; then per entry CONFIGSEL 0 and the address, CONFIGSEL 1 and red, again green, again blue. Every byte goes to RWDAC and again to its GO alias. | established |
| Who adds the pixel-offset nibble? | Software adds it to the palette address of every write (nonzero only for hardware maps 5 and 6: 0x30, 0x40). The chip must add the mode word's bits 7:4 on lookup, or those maps could not work. | established for software; inferred for the chip |
| Where does pixel 0x10 of a window on hardware map 2 land? | Bank 2, palette index 0x10, no offset. Written only if the colour map's entry 0x10 is allocated when the map is installed or stored into. | established |
| Is bank 2 ever loaded? | Yes: by the second distinct 8-plane colour map installed after server start (the first goes to bank 1), and by stores to it while installed. Until then it holds the zeros `bt479Init` wrote. | established for the mechanism; the install order of a real session is not static |
| Which colour map should be in bank 2 when a window shows DID 5 with mode bits 3:2 = 2? | The one the server installed into hardware map 2 and tied to DID 5. For the desktop icons that is the private map the desktop installs. | established for the rule; which client holds it is inferred |
| What writes RWMASK = 0, and is 0xff only the probe? | The kernel's rendering-node context load (`lightPcxSwap` restoring a zeroed image). The 0xff stores are the board-info probe only (the PROM always, the kernel when CONFIGMODE bits 7:4 read 0); the X server never writes it. | established for the code; a guest run shows the order |
| Does the hardware gate PutImage, GetImage and the tile fill with RWMASK? | No: the guest draws with RWMASK = 0 and the pictures show; the mask these paths set is XSTATE's. | inferred from working software |

## 1. Installing a colour map

### The call chain [binary]

The X screen record's colour-map hooks are one table in `lg1mc.so` data at 0x5e3c05e4: create (`rexInitializeColormap`
0x5e30615c), destroy (`rexDestroyColormap` 0x5e3060cc), install (`nfbInstallHWColormap` 0x5e2fdd5c), uninstall
(`nfbUninstallHWColormap` 0x5e2fd5e0), list installed (`nfbListInstalledHWColormaps` 0x5e2fe070) and store colours
(`nfbHWStoreColors` 0x5e2fd974). There is no function named `rexInstallColormap`; the board-specific parts sit in a group table:

- `rexCmapGroups` (0x5e3c00ec) has three records of 24 bytes: colour-map count, pointer to a list of (hardware map, next position)
  pairs, a head position (0), install routine, store routine, uninstall routine (none set).
- Group 0 (3 maps): list (0, 1), (1, 2), (2, 0): hardware maps 0, 1, 2. Install `rexInstallNormalMap` (0x5e3073e8), store
  `rexStoreNormalColors` (0x5e306eb8).
- Group 1 (1 map): list (3, 0): hardware map 3. Install `rexInstallPupMap` (0x5e306a9c), store `rexStorePupColors` (0x5e306588).
- Group 2 (3 maps): list (4, 1), (5, 2), (6, 0): hardware maps 4, 5, 6. Same routines as group 0.
- `rexHWCmaps` (0x5e3c0138) has seven records of 24 bytes (`rexNumHWCmaps` = 7). Word +0x10 and word +0x14 are:

| Hardware map | Group | +0x10 (display ID the server associates) | +0x14 (table byte) | Bank | Palette offset |
|---|---|---|---|---|---|
| 0 | 0 | 0 | 0x00 | 0 | 0 |
| 1 | 0 | 4 | 0x01 | 1 | 0 |
| 2 | 0 | 5 | 0x02 | 2 | 0 |
| 3 | 1 | 0x20 | 0x00 | (pop-up routines use bank 3 at 0x10 + pixel) | n/a |
| 4 | 2 | 6 | 0x03 | 3 | 0 |
| 5 | 2 | 7 | 0x33 | 3 | 0x30 |
| 6 | 2 | 8 | 0x43 | 3 | 0x40 |

Each visual has a 12-byte record at 0x5e3c01e4 (six, in the order of the six visuals at `rexVisuals` 0x5e3c022c): default display
ID, group, plane-group code. The 8-plane PseudoColor visual is {0, group 0, 1}, the 8-plane StaticColor 3-3-2 {8, 0, 1}, the 8-plane
TrueColor {0, 0, 1}, the 4-plane TrueColor and 4-plane PseudoColor {6, group 2, 1} and the 2-plane PseudoColor {0x20, group 1, 2}.
The group is read at `nfbInstallHWColormap` 0x5e2fddb0 to 0x5e2fdddc; the per-visual table reaches the code through the screen
record's pointer at 0x5e3c03e8. Pairing record i with visual i is **inferred** (the visual IDs are assigned at run time).
This corrects the earlier reading on the [bank page](../../devices/bt479/banks.md): the pop-up map is hardware map 3, and hardware
maps 4, 5 and 6 are ordinary maps of the 4-plane visuals that happen to live in bank 3.

### Which hardware map a colour map gets: `nfbInstallHWColormap` [binary, established]

Read in full (0x5e2fdd5c to 0x5e2fe06c). The colour map's private word (`devPriv[0]`) holds its hardware map, or -1.

1. Not in hardware (-1): take the group's head position, move to its "next" position, make that the new head, and use the hardware
   map named there. With the initial head 0, group 0 hands out hardware map **1**, then **2**, then **0**, then 1 again.
   Group 2 hands out 5, 6, 4.
2. The previous owner of that hardware map (word +0 of its record) is walked with `TellLostMap` and its private word is set
   to -1; any maps listed as sharing the hardware (word +8 of the record: empty for all seven) are evicted the same way.
3. The group's install routine runs on the new colour map (this is the palette load, below).
4. The record's owner is set to the colour map, and the window tree is walked with `nfbTellGainedMap` (0x5e2fe0e0).
5. Already in hardware: nothing is loaded. The position is moved to the head, so the order is least-recently-used.

So the default colour map, the first 8-plane map installed after the root window exists, lands in hardware map 1 (bank 1, DID 4),
the next distinct map in hardware map 2 (bank 2, DID 5), the next in hardware map 0, then they evict each other in turn. Which
colour maps are installed in which order in a live session (the default maps of the other group-0 visuals compete for the same
three maps) is not fixed by the code. The earlier statement that the default map is hardware map 0 had no basis in the binary.

### The palette load: `rexInstallNormalMap` and `rexStoreNormalColors` [binary, established]

`rexStoreNormalColors` is read in full; `rexInstallNormalMap` (0x5e3073e8 to 0x5e3082b4) was read through the 8-bit PseudoColor,
StaticColor and 8-bit TrueColor loops. Both do the same register work:

1. Decode the table byte of the colour map's hardware map: offset = byte & 0xf0, bank = byte & 0x0f
   (`rexInstallNormalMap` 0x5e30753c to 0x5e30757c; `rexStoreNormalColors` 0x5e307054 to 0x5e307074).
2. Wait until CONFIGMODE bit 0 reads 0 (0x5e3075e0 to 0x5e307604).
3. Bank select, Bt479 board (board revision below 2): CONFIGSEL = 0; RWDAC and its GO alias = 0x82; CONFIGSEL = 6; RWDAC and GO =
   `(bank << 4) | 0x0f` (0x5e307638 to 0x5e30764c). LUT1 board: CONFIGSEL = 6, a read of the GO alias, a read of RWDAC, then write
   `(old & 0x0f) | (bank << 6)` to both (0x5e30760c to 0x5e307634).
4. Per colour-map entry: CONFIGSEL = 0 and RWDAC/GO = `pixel + offset`; CONFIGSEL = 1 and RWDAC/GO = red >> 8; CONFIGSEL = 1
   and green >> 8; CONFIGSEL = 1 and blue >> 8. The address register is set for every entry, so the load does not depend on the
   chip's auto-increment. The order is red, green, blue and each is the high byte of the 16-bit X value.
5. Which entries: a dynamic class (PseudoColor, GrayScale, DirectColor) writes only entries whose use count is nonzero and whose
   pixel is in the colour map's stored-pixel bitmap (0x5e307be0 to 0x5e308120). The bitmap starts empty
   (`nfbInitColormapBitmap` 0x5e2fd46c) and `nfbHWStoreColors` adds every pixel the X colour-map layer passes to its store hook
   (`nfbSetColorBitmap` 0x5e2fdd08), which is what allocation and `XStoreColors` do. Static classes write all entries (0x5e3078bc to
   0x5e307bd4). An entry nobody allocated is not written, so the bank keeps whatever an earlier owner or `bt479Init` left.
6. The bank is not restored: the access bank stays at the last bank written. Routines that need bank 0 (`rexSetColor` 0x5e31951c)
   select it themselves, with the same 0x82 / 0x0f pair.

`rexStoreNormalColors` returns without touching the board when the colour map is not in hardware (0x5e307008), so a store into an
uninstalled map only changes the X colour map and is loaded at its next install. The pop-up pair (`rexInstallPupMap`, `rexStorePupColors`)
does the same with bank 3 selected (0x3f; LUT1 `0xc0`) and address `0x10 + index`, starting at index 1 (**[binary]**, the whole
install routine was not traced to its end).

### Pixel 0x10 on hardware map 2

Table byte 0x02: bank 2, offset 0. The install wrote palette index 0x10 of bank 2 with the colour-map entry whose pixel value is
0x10, if that entry was allocated. The mode word of DID 5 carries bits 3:2 = 2 and bits 7:4 = 0, so the chip must look pixel 0x10
up at bank 2, index 0x10 (**inferred** for the chip side: nothing shipped reads the lookup back). The pixel offset nibble is
therefore added by software to the write address and, by the mode word, by the chip on lookup; for hardware maps 0 to 4 both are 0.

## 2. Which banks are used

| Bank | Used by | Source |
|---|---|---|
| 0 | hardware map 0 (third distinct 8-plane colour map); `rexSetColor`; the PROM and kernel palette | tables above |
| 1 | hardware map 1 (the default colour map on a fresh server) | tables above |
| 2 | hardware map 2 (the second distinct map) | tables above |
| 3 | hardware maps 4, 5, 6 (4-plane visuals, index = pixel, pixel + 0x30, pixel + 0x40), the pop-up map (hardware map 3, 0x10 + pixel), the cursor colours | tables above; [cursor](../../devices/vc1/cursor.md) |

Pixel-plane 8-bit windows use banks 0 to 2 and bank 3 serves the small visuals and the cursor: **established** from the group
tables (`bt479Init` also clears banks 0, 2, 3 and loads a grey ramp into bank 1, [banks](../../devices/bt479/banks.md#the-access-bank)). The
default colour map uses the first hardware map of its group's rotation, 1 (bank 1). Bank 2 is loaded only when a second distinct
group-0 colour map is installed, or on a store into it while installed. Until then DID 5 shows zeros, not blue.

### Who loads banks 0 to 2

Only the X server's colour-map code, apart from the boot-time clears. The writers in the shipped objects are the PROM's palette
routines, the kernel's `initBt479` (bank 0 default table, zeros in banks 1 to 3; run when `gfxinit` makes its initialize request,
[gfxinit](gfxinit.md), and at early init when the PROM did not set the board up), the server's `bt479Init` (zeros in all four banks, a grey ramp in bank 1) and then `rexInstallNormalMap`, `rexStoreNormalColors`
and `rexSetColor`. No other shipped writer was found (`gfxinit` itself only makes that request; clients reach the palette through X requests; no colour-map daemon
was found writing the palette, but the shipped binaries were not searched for one exhaustively). The bulk loads in a guest run (model behaviour) fit this: two passes of zeros, then whole 256-entry loads per
install, and single-entry loads as clients allocate colours. Three hardware maps are shared by every group-0 colour map, so a bank
holds whichever map was installed in it last: an 8-plane PseudoColor map (the default map's reserved colours, then client entries),
the StaticColor map the server fills from its module table (entry 0x0f = 0xaa, entry 0x20 = 0x0a), and the 8-plane TrueColor map.
The 3-3-2 cube in bank 2 is that TrueColor visual's map: its masks are red 0xe0, blue 0x18, green 0x07 (the sixth-visual table at
0x5e3c022c), loaded by the TrueColor loop of `rexInstallNormalMap` (0x5e30767c). Its gamma-curved twin in bank 0 is the same layout;
which colour map carries the gamma values was not traced (`nfbCreateGammaRamp` 0x5e2fda38 builds a ramp at server start, but the
install loops read only the colour map's own entries). A bank snapshot at the end of a boot therefore says nothing about what bank 2
held while the icons were drawn: that is whichever map was last installed in hardware map 2 at that moment, and when the desktop's
private map is evicted its windows fall back to the group's first hardware map (bank 0) until it is installed again. There is no
contradiction with "the server writes bank 3 entries at 0x11 to 0x13, 0x21 to 0x23, 0x30 to 0x4f": those are its bank 3 loads; it writes
banks 0 to 2 as well.

## 3. Choosing a window's display ID and mode word

The display-ID layer (`FindFreeID`, `SetDIDMode`, `UpdateDIDMode`, `FreeID` and `compareModes`, 0x5e315840 to 0x5e3161a0) is in
`lg1mc.so`; `rrmInit` and `rrmSetReservedDID` are in `Xsgi` (0x10053110, 0x100530a0).

### The table

`rrmInit` copies the screen's DID template (`rexRRMPriv` 0x5e3c077c: 32 entries) and zeroes each entry's type. An entry is 24 bytes
at +140 in the layer's screen record: window list head and tail (+0, +4), two mode words (+8: window flag word, +12: the 16-bit
VC1 mode word), flags (+16), type (+18), window count (+20). `rexInit` (0x5e2d262c to 0x5e2d26e0) then reserves six entries with
`rrmSetReservedDID`, which sets the flags to 0xd and stores the two words:

| DID | Flag word (+8) | Mode word (+12) | Bank / offset |
|---|---|---|---|
| 0 | 0 | 0x0300 | 0 / 0 |
| 4 | 0 | 0x0304 | 1 / 0 |
| 5 | 0 | 0x0308 | 2 / 0 |
| 6 | 3 | 0x030d | 3 / 0 |
| 7 | 2 | 0x033d | 3 / 0x30 |
| 8 | 2 | 0x034d | 3 / 0x40 |

These are the words `vc1Init` loaded into the VC1 ([DID tables](../../devices/vc1/did-xmap.md#initial-entries)); **established**.
Flag bits read from use (**inferred**): bit 0 keeps `FindFreeID` off the entry (reserved), bit 1 in use, bit 2 shared, so the mode
word must not be edited in place, bit 3 mode loaded.

### Selection

- `FindFreeID` (0x5e315840, read in full): a type-1 window (`rexInitWindowType` 0x5e312c80 sets type 1 when the window's `nfb` record has a nonzero word at +24, otherwise 0) gets index 32,
  one past the table, and no entry, as long as bit 0 of the layer's board flags (`rexRRMPriv` +12 = 3) is set. Any other window keeps its current
  entry when that entry is not shared; otherwise the first entry of its type that is neither reserved nor in use is taken.
- `FindBestID` (0x5e3249b0) and `StealID` (0x5e324568) were read as listings, not traced to the end (**inferred**): they look for a
  shared entry of the same type whose words compare equal to the window's (`compareModes` 0x5e315960: flag word equal, and mode word
  equal under the mask 0x60fc, that is bits 14:13 and 7:2) and use it; failing that a free entry; failing that the colour map's
  own DID (`cmapDID` 0x5e315b8c: the DID of its hardware map, or the visual's default if not installed).
  A window with no special flags and a colour map in hardware map 1 or 2 therefore compares equal to the reserved DID 4 or 5 and
  shares it.
- `SetDIDMode` (0x5e315674): the first time an entry is used it copies the window's two words into it, marks it loaded and calls
  the screen's mode routine (`rexValidateMode`, 0x5e312f04, read in full). `UpdateDIDMode` (0x5e315760) refreshes the entry's words
  from the window for an entry that is not shared (and flips bit 2 of the flag word for a swapped buffer).

### The mode word [binary, established]

`rexValidateMode` and `rexChangeDIDCmap` (0x5e312a68, read in full) build it the same way:

`word = (previous & 0x7003) | 0x0300 | ((byte & 0x0f) << 2) | (byte & 0xf0)`, where `byte` is the table byte of the colour map's
hardware map, and bit 1 is then set or cleared from the window's flag word if the window is double buffered. A colour map not yet in
hardware uses the first hardware map of its group (list position 0: map 0 for group 0, map 4 for group 2). The word is stored in
the entry and loaded into the VC1 by private request 1017, which `rrm.o`'s request table (entry 17) maps to `RRM_LoadDisplayMode`
(0x100021f4); that calls slot 76 of the board's function table, `lightSetDisplayMode` (`light.o` +0x1540), which writes the
word at VC1 mode-table address `2 x DID` (**established**).

On an install, `nfbTellGainedMap` (0x5e2fe0e0) reaches `rexChangeDIDCmap` for each window of the map whose hardware group has two or
more maps and which does not use a fixed DID. If the window's entry is reserved and its mode bits differ from the new map's,
`rexChangeDIDCmap` frees it and steals one whose mode matches (the reserved DID 4 or 5, say) before loading. So **the bank load
comes first, then the DID's mode word follows** (**established** for the order).

### The desktop icons

The icon client is a private-colour-map client (`fiChooseVisual`, see [desktop icons](desktop-and-overlays.md#desktop-icons)):
an 8-plane PseudoColor map the desktop installs itself and one 4Dwm may also install. Under the rules above:

- Installed in hardware map 2 (the first private map after the default): its windows, the Icon Catalog interior and the Console icon
  if it uses the same map, take DID 5, mode word 0x0308, bank 2, offset 0. Installed in map 0: DID 0, 0x0300. Evicted by two later
  maps: back to the first hardware map of the group, bank 0, until reinstalled.
- The model trace (fill pixel 0x10, DID 5, bank 2) is the first case. Then bank 2 must already hold the desktop's colour map when
  the icons are drawn, written by the server's install of that map (steps 3 and 4 above) before the window's mode word changed. The
  server writes it when the map is installed and again for stores while installed; it never writes entries nobody allocated.
- If a model shows a flat 0x0000aa for pixel 0x10 through bank 2, bank 2 index 0x10 holds that value in the model. The reserved
  colours `rexCreateDefColormap` (0x5e306264) gives the default map have pixel 0x10 = 0xc9c9c9 (light grey, alternating with 0x868686
  at 0x11), so the blue is not from the default map. The bank-2 contents are either the desktop's own entry 0x10 or a write that
  reached the wrong bank (a selector-6 write with the address register at 0x84 or an access bank not honoured: [banks](../../devices/bt479/banks.md)).
  Which of these happened is not decidable from the binaries.

## 4. RWMASK

`RWMASK` (0x78, GO alias 0x878) reads and stores as one word. Searched for stores to offsets 0x78 and 0x878 from a register-page
pointer in every object that touches the board:

| Object | Store | Value | Grade |
|---|---|---|---|
| `lg1mc.so` (X server) | none | | established (the whole text was searched for stores at offsets 120 and 2168; the hits are all stack frames and unrelated records) |
| `Xsgi` | none | | inferred (not searched; it does not map the board) |
| `kernel.o` | none | | inferred (not searched; the board is reached only through `lg1.a`) |
| `lg1.a` `light_init.o` `lightInitInfo` +0xb4 (0x10000a9c) | 0xff | | established; runs only when CONFIGMODE bits 7:4 read 0 |
| `lg1.a` `light.o` `lightPcxSwap` (+0x15c save, +0x344 restore) | copies the word between hardware and a saved image | image word | established |
| the other `lg1.a` members (`light_dma.o`, `light_retrace.o`, `light_tp.o`) | none | | established (searched for the offsets and for the constants) |
| PROM board library (`lg1_init.c`, **[source]**) | 0xff | | source; written just before its pixel-memory probe, unconditionally |
| ide REX test and write-mask command (`rex.c`, `minigl.c`) | test patterns, user value | | source; diagnostics only |

So no desktop, tile, `XFillRectangle`, `GetImage`, cursor or private-request path (`lightPrivate`'s seven requests) writes RWMASK. The
one routine that can write 0 is the context load. The graphics manager gives each client process a rendering node
(`lightCreateDDRN`, `light.o` 0x10000770): a 172-byte image that is zeroed except two words (+164 = 0x20000000, the AUX2 plane group,
and +168 = 0x80084000, CONFIGMODE as restored). When the node's process first touches the board register page, the page-fault
path (`gfx_fault` in `gfx.o`, `rrmValidateMyPcx` in `rrm.o`, which calls slot 56 of the board table, `lightPcxSwap`) loads the
incoming node, and that copies every image word, RWMASK included, into the hardware (**inferred** for the order: the fault path was
read as a listing). When the previous holder is a node with a saved image, its registers (RWMASK too) are read
back into it first, so a node that ran on a board initialised to 0xff keeps 0xff across switches.

**What a guest run shows.** An emulator run of the 5.3 desktop (model behaviour, not hardware evidence) logged every RWMASK store:
0xff three or four times around the probe, then RWMASK = 0 immediately followed by a store of 0 to SMASK1X (0x7c), and pairs of
0xff with SMASK1X = 0xfffffffd; the tile and image commands came after a zero pair, and nothing stored 0xff after the last zero.
That is the order of `lightPcxSwap`'s restore (RWMASK, COMMAND, SMASK1X, SMASK1Y; `light.o` 0x100013cc to 0x100013e8): a zero pair
is a node with a never-saved image, a 0xff pair is a node whose image was saved from a board the init code had set up. So the node
that draws the desktop was loaded from a zero image and ran with RWMASK = 0 (**established** for the kernel path; the node
identification is from the run). Real boards run the same kernel and server, so they draw with RWMASK = 0 too. Since the
desktop's pictures do show on real Indigos, the hardware does not gate the `RWAUX1` host-data writes (command 0x200121 tile fill, the
0x302000a1 PutImage runs) by RWMASK, only by the plane mask in `XSTATE` bits 23:16 (**inferred**: it rests on the
working product, not on a register description). The same argument covers GetImage (0x2000ab, LDPIXEL through `RWAUX1`): X would not
read its own pixels back with a read mask of 0. What RWMASK does gate, if anything, is not shown by any desktop path; the PROM
and kernel set it to 0xff before their pixel-memory probe, which uses the same command shapes, and the ide write-mask command loads it.

## What a model must do

All **inferred** from the software contract unless noted.

1. Keep four palette banks and an access bank latched by selector 6 while the address register is 0x82; keep it until the next
   such write (the installers do not restore bank 0). Every colour-map entry load is an address write then three data bytes in the
   order red, green, blue.
2. Display lookup: bank = mode word bits 3:2, index = `pixel + (mode word & 0xf0)`. After the server's start, bank 1 holds a grey ramp
   and banks 0, 2, 3 hold the clear values `bt479Init` wrote (on top of the kernel's own writes), so an uninstalled bank is black or grey,
   not any colour a client chose.
3. Treat the VC1 mode table as plain storage at `2 x DID` loaded through the private-request path, and do not assume the DID, mode
   word and bank load happen in one step: the palette load precedes the mode word.
4. Do not apply RWMASK to the pixel writes or reads driven by `RWAUX1` (tile fill, PutImage, GetImage): the guest leaves it 0 while
   it draws. Use `XSTATE` bits 23:16 as their mask. Keep RWMASK readable and writable so the context save and restore round-trip.

## Not established

- Install order and hardware-map assignment in a live desktop session (default maps of other group-0 visuals, 4Dwm's own map).
- What RWMASK gates in hardware, if anything (the probe commands set it; no desktop path depends on it).
- The display ID 32 given to type-1 windows (outside the 32-entry table; the line-table writer was not read for it) and what a
  window of the pop-up visual shows.
- Full traces of `FindBestID`, `StealID`, `rexInstallPupMap` and the 8-plane TrueColor load path.
- The chip's own use of the mode word's bit 0 and bits 7:4 (no data sheet; [VC1](../../devices/vc1/did-xmap.md#open)).
