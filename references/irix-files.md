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
`stand/arcs/lib/libsk/graphics/htport.c`, `stand/arcs/lib/libsc/gui/background.c`, `stand/arcs/include/style.h`, `stand/arcs/ide/fforward/graphics/LIGHT/` (`cid.c`, `maps.h`, `minigl.c`, `rex.c`, `vram.c`, `vdma/lg1_stride.c` and the other `vdma` tests that issue the read command)
and `stand/arcs/ide/fforward/int2/int2_mask.c`, from the 6.5.7 tree, plus `6.5.5/f/root/usr/include/sys/gfx.h` from the 6.5.5 tree.

## IRIX 6.2 install media (shaded-drawing pages, 2026-11-25)

Two SGI-labelled CD images, each a volume header and an EFS filesystem holding a `dist/` tree of inst products (the install media of IRIX 6.2, IP20 Version 03131015 per the installed system's banner): part 1 of 2 (`525e068e82781b2c12ee6b58de11420f824741c3161db8a7c94808029bbe1928`) holds `eoe` and `x_eoe`, part 2 of 2 (`a6aaf159be8b976b50a64338ebc3881958feae1ca49b009ae2f2d41b92eb4d8c`) holds `sysadmdesktop`. The product archives use the record format described for 5.3 above: a record is found by its length-prefixed path, unique in each archive, and a non-zero `cmpsize` is `compress` format.

| Item | SHA-256 |
|---|---|
| `usr/gfx/arch/IP20LG1MC/libGLcore.so` (`eoe.sw.gfx`; the OpenGL renderer for the Entry board, read) | `d5e47aaed871a2dfe3b3da3d8f8a6e13719c102d368b858195026305351ca5c2` |
| `usr/gfx/arch/IP20LG1MC/libgl.so` (IRIS GL, constants only) | `d14e7192c8ec6272109a8f79b2560b39de45d0a714106d7325c3518d1742b189` |
| `usr/gfx/arch/IP20LG1MC/libGL.so` (the GLX client; not read) | `e635682e3e76f12b59cf11a0c99d954e2c4e358436c38a3b6b48b5ba0d71eda8` |
| `usr/cpu/sysgen/IP20boot/lg1.a` (6.2; context-default code) | `f6d177e2eb2a05df387c6d31a75b8a77e6473148dec08001764dca275e3a2c00` |
| `usr/cpu/sysgen/IP20boot/kernel.o` (6.2; searched for constants only) | `a86e87fd3d08a42d7c2bfd2df2d6a7b493d64cc921936bddfd88b2a60e45cdb3` |
| `usr/include/sys/lg1hw.h` (revision 1.28, names only) | `150090a9091397f445c47d01e6fc6d9c2aaea28efc25ea6930bbe348c6564ac8` |
| `usr/include/sys/lg1.h` | `545597703529772b2a28735a71bec2097513812349c51f649b7bae1c6c255cd8` |
| `usr/lib/X11/dyDDX/lg1mc.so` (`x_eoe.sw.Server`; command words and immediates) | `fbe0ff5bce91be67f788e136b421634e8e97395d15dec153081c3ec978d9ce2d` |
| `usr/gfx/arch/GENERIC/Xsgi` (strings only) | `cd2d1757c46b3dbd2f2dc811f5af0d910c36580a396b8016e1d79a176809a22f` |
| `usr/Cadmin/bin/clogin` (`sysadmdesktop.sw.clients`, part 2; symbols and strings) | `8d63080744252754cba0eb662e8dcdda1c6f8c2fead258705e809e92182d4888` |
| `usr/lib/X11/app-defaults/Clogin` | `d9042ebd8b3ede503be017a6f19d8fb26af5e7b440b35b0c9d3a5ff72791345e` |

The 6.2 objects are 32-bit big-endian MIPS ELF (the shared objects are stripped but export their routine names). The IRIX source files cited by the shaded-drawing pages are `stand/arcs/ide/fforward/graphics/LIGHT/minigl.c`, `rex.c`, `vram.c` and `rexpatterns.c`, from the 6.5.7 tree.

## IP20 PROM read for the power-on test (2026-11-26)

| Item | SHA-256 |
|---|---|
| IP20 PROM 070-8116-005 (4.0.5G), `ip20prom-070-8116-005-BE.bin`, the image whose addresses the Entry power-on test pages cite | `ae35c0971b594c9f028f79e2fd97bf45fbf170697b334d2ca8a4f46349d939bd` |

The ide source files cited with it are `stand/arcs/ide/fforward/graphics/LIGHT/btdac.c` and `rex.c`, from the 6.5.7 tree.

## REX3 specification read for the stipple registers (2026-11-26)

Used only for the layout and names of the sibling REX3 chip, never as a REX1 fact; each statement taken from it is marked as a sibling expectation where it is used.

| Item | SHA-256 |
|---|---|
| REX3 Specification, revision 1.0 (Silicon Graphics, August 1993; held in the Library as `erikarn-sgi_indy_rex3.pdf`; the pages carry a proprietary and confidential banner) | `9abe890d1a806ed67c26647e9b7ab309072d4d2a8faf2c75af52cc1530b33917` |

## Files read for the video-option page (2026-11-26)

Already listed above and read again: the 5.3, 6.2 and 6.5 `lg1.a` and `lg1mc.so`, the 5.3 and 6.5 `kernel.o`, the 6.5 `gfxinit` and `Xsgi`, the 5.3 `Xsgi` (`ddxGetBoardInfo` only), the 6.2 and 6.5 `libgl.so` of the Entry arch (the board-info compatibility check) and the 4.0.5G PROM. New here:

| Item | SHA-256 |
|---|---|
| IP20 PROM 070-8116-004 (4.0.5D), `ip20prom.070-8116-004.BE.bin` | `e6e1f1ed90d5979ef5829f823c2a4ff65ea24c3273a2b065a8b71abeba97f82f` |
| `ide.IP20` from the 6.5 base media (an ECOFF executable; the Entry board-info routine at 0xa85694ac is read from it) | `5ede622efa1b55d199218ff2cf10fb4556289288125b0c0e627bbbd424a4fea0` |
| `usr/gfx/arch/IP20LG1MC/libgl.so` (6.5; the IRIS GL context set-up and the board-info compatibility check) | `1ccdbf47ae829449ecfaa4128db441a0c36f2dbc78c3229dc37a0292cda8ba32` |

The IRIX source files cited with it are `stand/arcs/lib/libsk/graphics/LIGHT/lg1_init.c` and the video board's own diagnostics under `stand/arcs/ide/IP20/video/LIGHT/`, from the 6.5.7 tree, and the published `lg1.h` of the 6.2 media.

## Files read for the dither pages (2026-11-26)

| Item | SHA-256 |
|---|---|
| `usr/gfx/arch/IP20LG1MC/libGLcore.so` (6.5; constants, the dither routines and the span set-up) | `7e0dcde0106d404be00342d3d6a9f0022ce61a24e397eee7354cf9670eb0fcb9` |

The 6.5 `libgl.so` above was read for the same context set-up. The 5.3, 6.2 and 6.5 `lg1mc.so`, `Xsgi`, `gfxinit`, both kernels, both PROMs and the `ide` image were also scanned for the 4 by 4 ordered-dither matrix (only the two `libGLcore.so` copies hold it). The REX3 specification (listed above) was read again for its dither, rounding and colour-register sections; its use stays the same: a sibling expectation, never a REX1 fact.

## Newport (REX3) pages, 2026-11-27

IRIX 6.5 base media, from the disc `irix6.5_foundation1.iso` (subsystems `eoe.sw.gfx`, `eoe.sw.base` and `x_eoe`); the 6.5.30 overlay
image is `Instalation_Tools_and_Overlays1.image`. The members of `ng1.a` were extracted with `ar x` and read as MIPS disassembly
from the toolchain image (`mips64-linux-gnuabi64-objdump`); no decompiler was run.

| Item | SHA-256 |
|---|---|
| `usr/cpu/sysgen/IP22boot/ng1.a` (6.5 base; members `newport_init.o`, `newport.o`, `newport_dma.o`, `newport_retrace.o`, `newport_tp.o`, `corona_i2c.o`; `initXMAP9` and `fbdepth` read in full, the rest searched for `DCBDATA0` access patterns) | `2cab6999585fced59f65bd2ea6e026afc1875cf948808370f18e8584a028962b` |
| `usr/lib/X11/dyDDX/ng1.so` (6.5 base; data tables `rex3Depths8`, `rex3Depths24`, `rex3Formats`, function `rex3Install24Map`) | `4ff30c46ae2470691065ea5426824552d47bf4da49539e1ba056884700c66c71` |
| `usr/lib/X11/dyDDX/ng1.so` (6.5.30; the same three tables compared) | `c1c5c4d188d8861bbdbe06d5d78d6563d7ed512356d8a513d6d74ffd9073acce` |
| `sbin/hinv` (6.5 base; strings only) | `179e6fcef50d000480c73a644b47732fd5b933b41d422887ea5b4d0c51222c14` |

IRIX 6.5.7 source tree files cited by path: `stand/arcs/lib/libsk/graphics/NEWPORT/ng1_init.c` (`d52fe300...`),
`stand/arcs/ide/fforward/graphics/NEWPORT/` (`ng1visuals.c`, `ng1visuals.h`, `minigl3.c`, `newport_init.c`, `rex3.c`, `vram3.c`,
`cid3.c`) and `stand/arcs/IP22prom/csu.s`, `r4k_eerom.s`, `main.c`. The Newport hardware header (`sys/ng1hw.h`) is not in the tree.

Published specifications, Library `library/cache/graphics/indy/`:

| File | SHA-256 |
|---|---|
| `erikarn-sgi_indy_rex3.pdf` (REX3 Specification, revision 1.0, 13 August 1993) | `9abe890d1a806ed67c26647e9b7ab309072d4d2a8faf2c75af52cc1530b33917` |
| `erikarn-sgi_indy_xmap9.pdf` (XMAP9 Specification, revision 2.1, 29 October 1993) | `01f286964acbf1a843483eaad0f4448221e686bc1ef5f7c76ef12bfc02fa64a1` |
| `erikarn-sgi_indy_ro1.pdf` (RO1 Specification) | `d34e27959a9f30a152a86dd0536c58573aa06881ac05d3c3ff33efe369696937` |
| `erikarn-sgi_indy_vc2.pdf` (VC2 Specification; searched, not read in full) | `fe4a6a0ec593254e97443ad9e4ab5811330576c603cc72d188260010c8542fbd` |
| `erikarn-sgi_indy_gio64.pdf` (GIO Bus specification, version 1.1 draft, 1992) | `5b8599ac622fe1b59de3357d664df5ccb943141813e6245849d5be02bd7b69f2` |
| `erikarn-sgi_indy_mc.pdf` (MC Chip Specification) | `03e7062abcb842ea067a81b785756ad5f0d2dd28944fcc313f79c6b2738a3472` |
| `erikarn-sgi_indy_dmux1.pdf` (MUX Chip Specification) | `232fabd4033011941045e82309eb649c8359cc897fef0aa6ae70c274fcb82ed3` |
| `erikarn-bt445_ramdac.pdf` (image-only scan; not read) | `53df11f2aa802bb55632baf4526807dea1662ace6dfdc4d8b51c3ef4e222fe5c` |

Public drivers: Linux v7.2-rc7 (`db2ddb87143519e20a95aa36c60b36107b736a58`) `include/video/newport.h` and
`drivers/video/console/newport_con.c`; NetBSD tree `07004b2a9dac23a1cdd33b76dc45b65be56c6f1f` `sys/arch/sgimips/gio/newport.c`,
`newportreg.h`.
