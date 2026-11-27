# The board configuration byte: revision, monitor type and the video-option bit

One read of `WCLOCK` returns a configuration byte of the Entry board: bits 2:0 the board revision, bits 5:3 the monitor type and
bit 6 a flag the software calls "video installed". This page records who reads the byte, what each reader does with bit 6 and
what a model has to return. The register is on the [REX1 register list](../../devices/rex1/registers.md); the board's other
information fields are on the [gfxinit page](gfxinit.md#what-the-board-info-fields-change-printing-and-the-x-server-only).

Grades follow [AGENTS.md](../../AGENTS.md). Tags: **[binary]** read in the named shipped object (checksums in
[irix-files.md](../../references/irix-files.md)), **[source]** the IRIX source tree, by path. Addresses are the ones in the
listing of that object.

## The read

Write `CONFIGSEL` 4, read the GO alias of `WCLOCK`, wait one microsecond, read `WCLOCK` (the SET alias). **Established [binary]**
in the kernel's `lightInitInfo` (`light_init.o`: 5.3 0x10000a30 to 0x10000a64, 6.2 0xa2c to 0xa60, 6.5 0x878 to 0x8a0) and the
PROM board-info routine (4.0.5D 0xbfc0fa48 to 0xbfc0fa6c, 4.0.5G 0xbfc128f8 to 0xbfc1291c). Both store three fields from the
value, in the same order in every build read:

| Field of the byte | Stored at (board-info record) | Test |
|---|---|---|
| bits 2:0 | +0x28 `boardrev`, one byte | mask 7 |
| bits 5:3 | +0x2b `monitortype`, one byte | shift 3, mask 7 |
| bit 6 | +0x2c `videoinstalled`, one 32-bit word | mask 0x40: **bit clear stores 1, bit set stores 0** |

Bit 7 is never tested by any reader, and no reader keeps the byte itself. This bit 6 is unrelated to bit 6 of the flags byte at
+0x30 of the same record, which the kernel's graphics-DMA self-test sets and which gates the "Prototype HP2 hardware" warning
([that page](prototype-hp2-warning.md)). The published `lg1.h` marks `monitortype` and
`videoinstalled` "only supported for boardrev >= 1" (**[hdr]**, names and comment only), so on a revision 0 board the two
fields are not promised.

## Who reads the +0x2c word

Searched in the 5.3, 6.2 and 6.5 `lg1.a` members, the 5.3 kernel, the 4.0.5D and 4.0.5G PROMs, the 6.5 `ide.IP20` image, the
5.3, 6.2 and 6.5 `lg1mc.so` and `gfxinit`, and the IRIX 6.2 and 6.5 `libGLcore.so` and `libgl.so` of the IP20LG1MC arch.

| Reader | What it does with it |
|---|---|
| Kernel `lightInitInfo` (5.3, 6.2, 6.5) | Stores it (above). The only kernel read of `WCLOCK`. `lightInfo` copies the record out to the caller (0x34 bytes) and tests nothing in it but byte +0x30. No other `lg1.a` member loads the word. **Established [binary]**. |
| PROM 4.0.5D, 4.0.5G, and the 6.5 `ide` image | Stores it (above; `ide` 0xa85694ac to 0xa85694f4, its only read of the register) into a fixed RAM record (0xa8741268 in 4.0.5D, 0xa87412a8 in 4.0.5G, from the address handed to the board-info routine). The PROM loads bytes +0x28 (0xbfc100e4, 0xbfc2d50c, 0xbfc2d590 in 4.0.5D; 0xbfc07668, 0xbfc077ac, 0xbfc12f94, 0xbfc33340 and 0xbfc332bc in 4.0.5G) and +0x2b (0xbfc104ac, 0xbfc2d4ec; 0xbfc076d8, 0xbfc1335c, 0xbfc3329c) of that record and never the word at +0x2c; its register-initialisation routine, the only function handed the record, reads only +0x28 and +0x2b. The PROM library source (`stand/arcs/lib/libsk/graphics/LIGHT/lg1_init.c`) names the field `videoinstalled`, sets it in the probe, and nothing in the `libsk` or `ide` source reads it (**[source]**). **No PROM or `ide` path depends on it** (absolute-address search plus the source; **established** for the loads listed). |
| `gfxinit -v` (5.3 0x406614 per the gfxinit page, 6.5 `lg1_info` 0x100069b8 to 0x100069d0) | Prints "video option installed." when the word is non-zero and "video option not installed." when it is zero (6.5 read: the empty and the "not " strings at 0x10039960 and 0x10039968). No branch on it. **Established [binary]** for 6.5, inferred equal for 5.3. |
| X server, IRIX 5.3 and 6.2 `lg1mc.so` | Copies it into the per-screen board record at +24 (`rexGetRevs`, 5.3 0x5e2d207c to 0x5e2d2080; folded into `rexInit` in 6.5). When the record's word is 1, `rexInit` (5.3 0x5e2d2450 to 0x5e2d2490, 6.2 0x5e4c0324 to 0x5e4c0364) calls `Xvsv1ScreenInit`: its first step `sv1InitVideo` (5.3 0x5e322824) opens `/dev/video` and issues the video driver's ioctls 120, 122 and 125; a failure prints a message through `ErrorF` and returns 0. On a non-zero return the word is **rewritten to 0**; on success it stays 1 and the server prints `rexInit(%d): video board found`. **Established [binary]** (5.3 read in full; 6.2 same shape). |
| X server, IRIX 5.3 and 6.2, after `rexInit` | Eleven more routines load the record's word (reached through the screen-private index, `rexScreenPrivateIndex`, so it is the board record and not a window record) and branch on it: `rexDestroyColormap`, `rexStorePupColors`, `rexInstallPupMap`, `rexStoreNormalColors`, `rexInstallNormalMap`, `rexDisplayCursor`, `rexValidateMode`, `rexSetColor`, `sv1InstallVideoMap`, `sv1SetVideoPosition` and `sv1SetVideoDimensions`, the same set in both releases; `sv1Installed` also tests it, returning 2 for a zero word and installing a hook for a non-zero one. A zero word skips the video colour-map and video-position code. The loads were found by tracking each base register back to the screen-private index; the branch was read in `rexDestroyColormap`, `rexStoreNormalColors` and `sv1Installed` (the rest are **inferred** to gate the same kind of code). |
| X server, IRIX 6.5 `lg1mc.so` | Copies the word into the record (`rexInit` 0x5f137cec to 0x5f137cf0) and **nothing loads it**: the module has no `sv1` or video-board code or strings, and every routine that reaches the record through the screen-private index was scanned for a load at +24. **Established [binary]** for the routines scanned. |
| `Xsgi`, GL libraries | `Xsgi`'s `ddxGetBoardInfo` returns the stored pointer unread. The IRIS GL start-up check (`gl_check_gl_lib_compat` in the 6.2 and 6.5 `libgl.so`) issues the board-info request and compares only the board name. **Established [binary]** for those routines. |

The tile-fill and PutImage routines (`rexTileRects`, `rexDrawImage`, `rexRevADrawImage`) do **not** read this word. Their test of
a value of 1 or -1 loads a field of the window's multibuffer private record (the one indexed by the module's
`nmbxWindowPrivateIndex`), reached through the window's private-data array, not the board record; earlier notes on
[tile fill](../../devices/rex1/tile-fill.md) said otherwise and are corrected there.

## What a stock Entry board reads: not stated by any software

Unknown from software: no shipped code, source file or document states the value a given board returns, and no captured
`gfxinit -v` output was found. What the software does fix:

- The byte is a strap, not a probe: the kernel and PROM read it once and keep the result. **Established.**
- The 5.3 and 6.2 X server treats a clear bit as "try the video driver", logs one `ErrorF` message and falls back to 0 when the
  open fails, and prints "video board found" only when it works. A board shipped without the video option must therefore read
  bit 6 **set**, or every X start would log the failure; the bit is **inferred** to be a strap that the optional video board (the
  `sv1` board the X server and the `ide` video tests drive at its own GIO address) pulls low. Boards therefore differ with the
  option, by design.

## What a model should return

**Bit 6 set (the word at +0x2c is 0), as a fixed value, while the machine has no video-option device.** Every shipped path
accepts it: the PROMs, the kernel, the 6.5 server and the libraries do not depend on the bit; the 5.3 and 6.2 server skips its
whole video route (no `/dev/video` open, no `ErrorF` noise, no video colour-map code); `gfxinit -v` prints "video option not
installed.". Returning bit 6 clear without a video device is not fatal either, since `rexInit` writes the word back to 0 when
the open fails, but it costs an error message per X start and runs the video-aware branches until then.

No separate property is needed. If a video-option device is ever added to the machine, derive the bit from whether that device is
present, so the strap and the device cannot disagree. (Revision 1, the "P1 LG1 board" the model reports, is a revision for which
the header promises both fields.)

A qtest can discriminate: `CONFIGSEL` 4, read the GO alias, then the SET alias; bits 2:0 and 5:3 read the configured revision and
monitor type and bit 6 reads 1.
