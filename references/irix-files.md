# IRIX files read for the LG1 pages

None of these is committed. Each is named by the path it has on the install media and identified by SHA-256. Disassembly and notes derived from them are committed.

## IRIX 5.3 (network install image, `dist/` subsystems)

The `eoe1.sw` and `x_eoe.sw` archives are a 13-byte header (`im001V530P00` and a zero byte) followed by one record per file, in any order: a 16-bit big-endian path length, the path, then the file's data. The size of the data is the `cmpsize` of the matching `.idb` entry, or the file's own size when `cmpsize` is 0; data is `compress` format when the two differ. The member names are those of the `.idb` entries (`f` lines, path in the fifth field).

| Item | SHA-256 |
|---|---|
| `dist/eoe1.sw` | `070ab3b3447879f5c7e44fbe27430d9d2bc6db7d2983b096e2010e1ea7b45780` |
| `dist/eoe1.idb` | `b2db306f94fb366a70fa6e07e55baa02e3924a312ddfaf05daf749271e5d344c` |
| `dist/x_eoe.sw` | `c9659edda9484abbb0a3a6985b7553dc7a7e41cbd1fcabf59aa211c9c6ab716a` |
| `dist/x_eoe.idb` | `0c88537f9c3aed255b7a28202464992ace09be2ad88d3b0f41b1377f2f2b09fc` |
| `usr/cpu/sysgen/IP20boot/lg1.a` (members `light.o`, `light_init.o`, `light_retrace.o`, `light_tp.o`, `light_dma.o`) | `d015824b9cae227f20f1bc336f2059c6cfe124ec11e382a54c3f48dc5f98b124` |
| `usr/cpu/sysgen/IP20boot/kernel.o` | `499ce905329b5a9888db2db6d23c3f1679144f9ecb35c63ef7d03820b883c2d2` |
| `usr/lib/X11/dyDDX/lg1mc.so` (stripped, exported symbols only) | `9c440b4c8c5960934af0dec01ec655631c78903ee6c10ba91589ee6fb15de14d` |
| `usr/lib/X11/dyDDX/lg1.so` (the R3000 board's module; not read in detail) | `bc23e654bc723d4567f0f1ef74a301b1bd98401ec7e6ea0bddb499dd89fe0a32` |
| `usr/gfx/arch/GENERIC/Xsgi` (server executable) | `5096bf18a00ba9b2c344821bf74bfee14144d46c96a6c10d8d22d1e3c236daaa` |

The IP20 boot objects are in the 5.3 `eoe1.sw.unix` subsystem with the mach tag `CPUBOARD=IP20 GFXBOARD=LIGHT`. The R3000 Indigo's copy is `IP12boot/lg1.a` (`49cdfc811977a1fca2696654b9413f0d9d58711fe386f1ace0363a06549294d2`, label "LG1"); the Crimson's is `IP17boot/lg1.a` (label "LG1MP"). Neither was read beyond its label.

## IRIX 6.5 base media

| Item | SHA-256 |
|---|---|
| `usr/cpu/sysgen/IP20boot/lg1.a` | `4b5728a5ffb26b7d71926ba0e8839005cb9a4cde9d6253913abf1a27a15a107f` |
| `usr/cpu/sysgen/IP20boot/kernel.o` | `d67a044d547c3275be37ec62551bdf340a2c89e2dd39312127945b9f68e40dfe` |
| `usr/lib/X11/dyDDX/lg1mc.so` | `961f73ed6a4a8a56e21dae5fed8d76997f6bf7ad0aa70af8b3c203eec9158207` |
| `usr/gfx/arch/GENERIC/Xsgi` | `c28eaabc80ab83dc7ea5d949ae3b1d5303abe6c0a867b91419c4e7cd0f786453` |

The 6.5 objects are compiled for the n32 ABI. They were disassembled with a standard MIPS disassembler and read by hand; no decompiler was run on either release, so no reading here is graded above what a hand read of the whole routine supports.
