# The "Prototype HP2 hardware" console warning

IRIX 5.3 prints `WARNING: Prototype HP2 hardware` the first time the X server asks the kernel for the board's information. This page traces
what decides it and what the model has to provide so it stays quiet. The message is only a warning, but the same flag also changes the X
server's FIFO level and its use of pixel DMA (below), so a model that fails the test runs the server down a different path.

Grades follow [AGENTS.md](../../AGENTS.md). Tags: **[binary]** read in the IRIX 5.3 `IP20boot/lg1.a`, member and offset (checksums in
[irix-files.md](../../references/irix-files.md)); **[inferred]** gives its basis. The functions named were each read from first to last
instruction.

## Where the string is and what prints it

- The text is the second string in `light.o`'s read-only data (`.rdata` +0x18, address 0x10002528 in the member's listing), referenced
  by `lightInfo` (`light.o` +0x168) **[binary, established]**.
- `lightInfo` is the handler for the board-information request (the one `ddxGetBoardInfo` in the X server issues). On entry it loads a
  one-shot flag from the member's initialised small data (address 0x10002658, initial value 1). If the flag is set it clears it, reads
  byte 0x30 of the board-information record (`lightData` +0x64 points at it), and if **bit 6 of that byte is clear** calls the kernel's
  warning printer (`cmn_err` with level 4) with the string. Then it copies up to 0x34 bytes of the record to the caller.
  **Established.** The warning therefore prints at most once per boot, on the first information request, and never when bit 6 is set.

## What sets bit 6 of byte 0x30

`lightInitInfo` (`light_init.o` +0x9e8) fills the record. Byte 0x30 is built in two steps **[binary, established]**:

1. Every call stores `mc_rev_level | 0x80`: the kernel's MC revision level in the low bits (read from a kernel global) with bit 7 always
   set. This is not the part that prints the warning.
2. Only on the first call of the boot (a static word, `vdma_rev`, is zero) it runs an MC graphics-DMA self-test, and if the test
   passes it ORs 0x40 into byte 0x30 and into that static word. On every later call the static word is copied back, so the answer
   from the first call is permanent.

The self-test (`lightInitInfo` +0xba0 to +0xc70 and `tst_vdma_intr`, +0xdd4) is already described, step by step, on the
[board page](README.md#kernel-probe-and-initialisation). What decides it, from the code:

1. `splhi`; clear bit 13 of the MC `cpuctrl0` word (0x1fa00004); save the INT2 local 0 mask byte (0x1fb801c7) and set it to 0x10, so
   only local 0 bit 4 can reach the CPU.
2. `tst_vdma_intr`: set `dma_ctl` (+0x16c) with its interrupt-enable bit 4 on and bit 8 (the translation enable) off; write
   `dma_memadr` (0x1fa02004) with the physical address of a static word, `dma_mode` (0x1fa02034) 0x5a, `dma_stride` (0x1fa0201c)
   0x10000, `dma_size` (0x1fa02014) 0x10004, and `dma_gio_adrs` (0x1fa0202c) 0x89abcdef, which starts the fill (per the chips
   repository's MC page the 0x5a mode is a memory fill and the GIO address register carries the fill constant, so no GIO device is involved).
   Then poll `dma_run` (0x1fa0204c) bit 6 for up to 1000 one-microsecond waits, stopping as soon as it reads 0.
3. Back in `lightInitInfo`: **call `getcause` and test bit 10 (0x400)**. If set, byte 0x30 and the static word get bit 6. Then restore
   `cpuctrl0` and the INT2 mask, clear the `dma_cause` register (+0x164), and run `VdmaInit`, `splx`.

So the decision is exactly: **is the CPU's Cause register bit 10 (the interrupt pin driven by INT2 local 0) set when the code reads it,
right after the DMA has stopped running?** It is not a register read of the graphics board, not the board-information word at +0x2c
(which only reports whether a video board is present and is copied separately), not the pixel-memory probe, and not the
lightInitInfo self-test result words the board page lists (they are the inputs, written before this step). Nothing on the LG1 is
touched by the test.

## What the model must supply

All of this is on the MC and INT2 side; the graphics board model has nothing to add. The chain (with the chips repository's pages
`devices/mc` and `devices/int2` as the owners, checked at their reviewed revisions 0c53829c and 3ea29a9c):

1. The MC fill DMA started by the write to `dma_gio_adrs` runs (in the model it can complete instantly), `dma_run` bit 6 reads 0 after
   it, and it sets the MC's DMA-complete cause bit.
2. Because `dma_ctl` bit 4 (interrupt enable) is on, completion raises the MC's graphics-DMA interrupt, which INT2 latches as **local 0
   status bit 4**.
3. Local 0 is `status AND mask` (mask 0x10 here), and it drives the CPU's Int0 line, **Cause bit 10 (IP2 in hardware naming, `CAUSE_IP3` in
   the kernel's)**. The Cause bit must be visible to `getcause` with interrupts disabled (the code runs at `splhi`), and must stay
   asserted until the code itself clears `dma_cause` after reading Cause.
4. The interrupt is edge-latched into a level: a model that drops the INT2 bit as soon as the DMA finishes, or that gates the pin
   with the CPU's own status mask in a way that hides it from the Cause read, fails the test.

Value to supply when `getcause` returns: bit 10 set. A discriminating test: with INT2 local 0 mask 0x10 and `dma_ctl` interrupt-enable
set, run a fill DMA and read Cause with interrupts masked; bit 10 must read 1 until `dma_cause` is written 0, then 0 (mask still 0x10).

## What else depends on the flag

The board page records that the X server's `rexInitHW` (0x5e2d2720, `lg1mc.so`) chooses its FIFO level (default 7, or 9 or 11 on some CPU boards) from
bit 6 of this byte. The board page already records that a PutImage of 16384 pixels or more uses the kernel's pixel DMA only when the flags byte is 2 or
more and that a failed DMA request prints "lg1DrawImage: LG1_PIXELDMA failed". With bit 6 clear the server is told "prototype hardware"
and takes the conservative path, so a model that cannot raise the interrupt gets both the console warning and a different FIFO level.
**Inferred**: the DMA-use decision tests the same byte, but only its bit 7 and low bits were read.

## Not read here

IRIX 6.5's `lg1.a` was not re-read for this page; the 5.3 member is the only one traced.
