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

Review (2026-11-23): the four IRIX 5.3 archives and the four 5.3 objects above were re-extracted from the IRIX 5.3 install disc image (SGI disk label, EFS partition, sha256 `a194caea63d280109c37d50be929c34a0f80a23c3e951c3cfa2af1315a0d8cad`) and every hash reproduced. For 6.5, `lg1.a` and `kernel.o` were seen in other held copies with the hashes listed; the 6.5 `lg1mc.so` and `Xsgi` hashes were not reproduced, and the disc they came from is not named here. The 6.5 base tree of the archive.org IRIX 6.4 for Origin, Onyx2 and OCTANE image holds different copies (its `lg1.a` is `2267869bb682b891c7b2544bebde41af392da18b9df12f53333ef8e392df9eb6`), so the 6.5 rows should name their disc before they are cited as 6.5.

## Additional files read for gfxinit, the tile fill and the icons (2026-11-24)

IRIX 5.3, from the same install disc image (`dist/eoe1.sw`, `dist/x_eoe.sw`, `dist/desktop_eoe.sw`, `dist/4Dwm.sw`), extracted by the record rule above (the repeated install paths were told apart by the next record's name).

| Item | SHA-256 |
|---|---|
| `usr/gfx/gfxinit` | `524c75008943e9fb7d6db74ae65414573661561f78acc222ef2f78375de91e54` |
| `usr/cpu/sysgen/IP20boot/gfx.o` (generic graphics ioctl layer) | `b2ac8c4dc9c7518241df067d34ddddb9b8ac937b62400fd96aa946feeca25467` |
| `usr/cpu/sysgen/IP20boot/rrm.o` (rendering resource manager: node switching, display-mode requests) | `00767fd570450ad22845d1f456decd4fe9efe1f1846ab6ed5442bd419b720a32` |
| `usr/bin/X11/X` (shell script that runs `gfxinit` and then `Xsgi`) | `26360a4ce1703fd6149f3007bf720dcce9d0e4e59be7390c86cd5da7c105225f` |
| `var/X11/xdm/Xservers` | `8864f49a1b252a67c5e7e35ec528d50197bf9ed0370d86adcbacf83b45909034` |
| `usr/lib/libdesktopFileicon.so` | `4cbc7519fc4db5b478445aadb6aab4c9845850b8872b74cefb6539a000d30c90` |
| `usr/lib/filetype/system/iconlib/Xlogo.fti` | `8b20f6e90de86248c2d238c42f92ae7c32693ad6467d293b867acf1895ff0fb2` |
| `usr/lib/X11/app-defaults/4DWm` | `d7f6ff3e37bca714f0a692e9bb9f9a286f19a6d923b7c83f03fc3096d5c6412b` |

IRIX 6.5 base media (the held 6.5 `lg1.a`, `kernel.o`, `lg1mc.so` and `Xsgi` above, plus):

| Item | SHA-256 |
|---|---|
| `usr/gfx/gfxinit` | `844c396b357a8207f3483f2a3cf7f4068b5701e8b931e703dfa20b6a2856a13b` |
| `usr/cpu/sysgen/IP20boot/gfx.o` | `4295be87a76062f37fd32b04348e1b9667c2629da48308ccb0ad80bab72ee3e2` |

Public header `usr/include/sys/lg1hw.h` and `lg1.h` from the public IRIX 4.0.5F root archive (`405Froot.tar.gz`, SHA-256
`040ca0a91b02c5bfc3d1a9df8b5cd7eee6ac689792770264c4356eaf1895a901`; `lg1hw.h` `5bede59fb3a17c7acf8ff12837ee959f49adba3b2e9fa2dd6260fceca1b5dc9c`): names and values only, as the other pages use it.

The IRIX source tree files cited by path are `irix/kern/ml/IP20.c`, `irix/kern/sys/IP20.h`, `stand/arcs/lib/libsk/graphics/LIGHT/lg1_init.c`, `lg1_tp.c`,
`stand/arcs/lib/libsk/graphics/htport.c`, `stand/arcs/lib/libsc/gui/background.c`, `stand/arcs/include/style.h`, `stand/arcs/ide/fforward/graphics/LIGHT/` (`cid.c`, `maps.h`, `minigl.c`, `rex.c`)
and `stand/arcs/ide/fforward/int2/int2_mask.c`, from the 6.5.7 tree, plus `6.5.5/f/root/usr/include/sys/gfx.h` from the 6.5.5 tree.
