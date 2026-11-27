# gfxinit and "graphics initialize failed" on the Entry board

What the X start-up script and `gfxinit` check on an LG1 before the message "graphics initialize failed" appears, and what the
board model has to return. Short answer: **nothing the board can return decides it.** `gfxinit` never reads a monitor type, a
revision or a VC1 register on this board, and the kernel's initialize entry point for the LG1 returns success whatever the
hardware says. The failure comes from the generic graphics ioctl layer, which refuses the request when the calling open file does
not own the board.

Grades follow [AGENTS.md](../../AGENTS.md). **[binary]** is read in a shipped object, with function and address; **[source]** is
the IRIX source tree, cited by path and written in our own words; **[inferred]** says what it rests on. Sources and checksums are in
[irix-files.md](../../references/irix-files.md). Only the IRIX 5.3 objects were disassembled call by call; the 6.5 objects were
read where stated. Nothing was run.

## Who runs gfxinit

`/usr/bin/X11/X` is a shell script, not the server (5.3 `x_eoe`, read in full, **established**). When the `windowsystem` chkconfig
flag is on it runs `/usr/gfx/gfxinit` (forwarding a `-boards` argument if there is one), reads the gamma value, and `exec`s
`/usr/bin/X11/Xsgi` with `-gamma`. So `gfxinit` runs **before every server start**, including every xdm respawn, and its exit
status is not checked by the script. The xdm server line (`/var/X11/xdm/Xservers`, 5.3) is
`X -bs -nobitscale -c -pseudomap 4sight -solidroot sgilightblue -cursorFG red -cursorBG white`: the root window is a solid
`sgilightblue`, not a tile.

## What gfxinit does for an LG1MC board

`gfxinit` (5.3 `usr/gfx/gfxinit`, addresses are virtual addresses in that file; **[binary]**, the whole control flow around the
messages read, the per-board table read in full):

1. Opens the graphics device and counts boards. For each selected board it issues request 102 (the header's
   `GFX_GETBOARDINFO`) into a 0x28-byte buffer. A failure prints "graphics getboardinfo failed" (0x405b2c, 0x405c80).
2. Looks the returned board name up in a table of 12-byte entries (name, init function, info function) at 0x10000004 by string
   compare. A miss prints "unknown graphics subsystem '%s'" (0x405bd0). The `LG1MC` entry (0x1000001c) has **no init function**
   and the shared info function at 0x406614; the `LG1` entry (R3000 board) is the same, the `LG1MP` entry (Crimson) differs.
3. With `-v` it prints the board and calls the info function (0x406614), which is the only place that reads board-info fields:
   revision (+0x28), pixel-memory code (+0x29), VC1 revision (+0x2a), monitor type (+0x2b), the +0x2c word and the flags byte
   (+0x30). These only select printed words (below). Nothing branches on them.
4. Request 103 (attach, argument: board number and a user address) fails with "graphics attach failed" (0x405eb8); request 110
   ("mapall") with "graphics mapall failed" (0x405f24).
5. **Request 106 with argument 0** (0x405f4c to 0x405f68): if the call returns -1 it calls `perror` with a string held in a global, then `syslog(2, "graphics
   initialize failed")` (0x405f90) and `exit(1)`. This is the only test.
6. The board's own init callback from the table, if any (none for LG1MC), then request 107 ("graphics start failed", 0x406050).

The request numbers are the header's `GFX_BASE` (100) plus the index; the header (`sys/gfx.h`, IRIX 6.5.5 tree, line 65) defines
`GFX_INITIALIZE` as `GFX_BASE + 6` (**[source]**, a one-line fact). The `perror` call runs first, so a failed start prints the
errno text on the line before the syslog message; that errno is the missing fact.

## What the kernel does with request 106

The generic layer is `gfx.o` (5.3 `IP20boot/gfx.o`, `gfxioctl` at +0x1560; 6.5 `gfx.o`, `gfxioctl` at +0x2b48). **[binary]**,
read from its first instruction to its last.

- Requests 102 (board info), 103 (attach), 104 (detach), 105 (is-managed), 108 (download) and 110 (map all) are served without an
  ownership test. Requests 106 (initialize), 107 (start), 109 and 111 (label) first require the open file to be the board's **owner**
  (the dispatch is the jump table at `.rdata` +0x18c of the 5.3 object and the compare chain after it; 6.5 has the same order). The
  board record keeps an owner pointer at +8. Request 103 (attach) calls the board's attach entry and then stores the calling file in the owner field **only if the field was
  empty**; a second opener attaches successfully but does not become owner. Request 106 compares the owner with the calling file and
  returns errno 1 (`EPERM`, "Not owner") when they differ (5.3 +0x1ad4 to +0x1aec; 6.5 +0x2c9c to +0x2cb0).
- Other refusals before the dispatch: a device number at or above the table limit (errno 6), an empty device slot (errno 19), a
  device opened with a flag bit that restricts it to one process and a different caller (errno 13), and a device with no board entry
  table attached (errno 13). None of these depends on the hardware.
- For the owner, request 106 calls the board's initialize entry and returns its result. The LG1's is `lightInitialize` (`light.o` +0x4dc in
  the 5.3 object, +0x33c in 6.5): it calls the console-registration helper with zero arguments, then `lightInit` with the board's
  two saved base values and a zero reset argument, and **returns 0 unconditionally** (read in full in both objects). `lightInit` itself
  returns nothing the caller sees (`initRex`, `rexClear`, `lightInitInfo`, `rexClear`, `initClock`, the colour map, and `initVC1`
  when the VC1 revision byte is above 0; see the [board page](README.md#kernel-probe-and-initialisation)).

**Established:** a hardware read-back, board-info field or VC1 register cannot make request 106 fail. **Inferred (not seen
running):** in the emulated system the error is an ownership failure, `EPERM`, because an earlier opener still holds the board. The
script runs `gfxinit` on every X start, so a previous `Xsgi` or `gfxinit` that is still alive (or whose file descriptor has not
closed) leaves the owner field set and the next start's attach succeeds but its initialize is refused. What would settle it is the
line `perror` printed before the message: "Not owner" is this case; "No such device" (19) or "Permission denied" (13) would be one
of the refusals above, and then the board table or device node is wrong rather than the hardware.

## What the model must do

- **Request 106 itself needs nothing from the model.** `lightInit` runs inside the call and must finish: `CONFIGMODE` bit 0 reads 0
  (and bits 28:24 read 0 before VC1 access), the `RWVC1` read pipeline of the [REX1 page](../../devices/rex1/registers.md) works,
  and the VC1 revision byte is above 0 (otherwise the kernel prints "lg1 init: can't support old VC1s." and skips the VC1 setup,
  which is not a failure).
- **Do not leave the board owned.** If a server dies, its descriptors must close so the owner field clears; when running the script
  by hand twice in a row, the second `gfxinit` refuses to initialize while the first holder lives.

## What the board-info fields change (printing and the X server only)

None of these affect `gfxinit`'s exit; they are what `-v` prints and what the X server later reads.

| Field | Value read | Printed by `gfxinit -v` (5.3 0x406614) | Other readers |
|---|---|---|---|
| +0x28 board revision | 0, 1 | "P0 LG1 board" and "P1 LG1 board"; 2 and 3 print "LG2 revision 1" and "LG2 revision 3" | the kernel picks Bt479 below 2 and LUT1 otherwise; the PROM library decides the same way |
| +0x29 REX revision (the pixel-memory probe's outcome) | 0, 1, 2, other | REX revision "A", "B", "1.5" or "unknown" | none read |
| +0x2a VC1 revision | 0, 1, other | VC1 revision "A", "B", "unidentified" or "unknown" | below 1 the kernel skips VC1 init; the X server's line-table extra entry |
| +0x2b monitor type | 0 to 7 | 6 is 14", 2 and 5 are 16", 1 and 4 are 19", 3 is 20", 7 "unknown", 0 "unidentified (0)" | X's `lg1MonitorSizeTable` (physical size, mm); the PROM and kernel colour-map setup (below) |
| +0x2c video installed (`WCLOCK` bit 6 clear) | 0, 1 | "video option installed." or "video option not installed." (6.5 and 5.3 read: the same word test and the same pair of strings) | the 5.3 and 6.2 X server's video route; nothing in 6.5 ([board configuration byte](board-config-byte.md)) |

The PROM library source (`stand/arcs/lib/libsk/graphics/LIGHT/lg1_init.c`, **[source]**) names the record fields `boardrev` (+0x28),
`rexrev` (+0x29), `vc1rev` (+0x2a), `monitortype` (+0x2b) and `videoinstalled` (+0x2c, 1 when `WCLOCK` bit 6 is clear), and its
probe sets `rexrev` to 0 for the outcome 0x01080909, 1 for 0x09091020 and -1 otherwise: the "pixel-memory probe" of the board page is
a REX revision test, and the pixel-memory code is the REX revision (0 "A", 1 "B", 2 "1.5" which the probe never produces).

The monitor-type words come from the jump table at 0x100019e0 and the strings it reaches (**[binary]**, decoded in full). The
X server's table at 0x5e3c0004 in `lg1mc.so` (5.3) gives the screen size in millimetres per type: 360 by 270 for types 0, 1, 4 and
7, 295 by 221 for 2 and 5, 373 by 280 for 3 and 240 by 180 for 6 (**[binary]**, read as data). The PROM's board library
(`stand/arcs/lib/libsk/graphics/LIGHT/lg1_init.c`, **[source]**) sets the colour-map "sync on green" flag from the monitor type
(on unless the type is 6), skips the ARCS monitor component when the type is 7 and, in its comments, expects the VC1 revision byte
to read 1 on a shipped board. So the model's current monitor type 0 and VC1 register 5 are harmless for `gfxinit`; type 0 prints as
unidentified and register 5 reads as revision byte 4 (printed "unknown"). The photographed chips are `VC1 REV B` and `REX1.5`: a
register 5 value whose low three bits are 2 gives revision byte 1, which prints "B" and keeps the X server on its common path
(**inferred** that this is what a shipped board reads: no document states it).

## Open

- The errno behind the model's failure is not known; it is the first thing to capture ("graphics initialize failed" is printed after
  it).
- The 6.5 `gfxinit` was checked for the same strings and the same `LG1MC` table row, not disassembled call by call; 6.5 `gfx.o` was
  read for the same owner test (**inferred** equal flow for the LG1).
