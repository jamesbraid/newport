# VC1 timing, frame and display-id tables

The byte tables the Indigo software loads into the VC1's external SRAM at start-up. They are listed as bytes only. The format of
the table entries is **unknown** (see [the VC1 page](README.md#timing-tables)), so no row is decoded here. Both come from
shipped binaries read in full: the table bytes were dumped from the object's data section and from the PROM image; nothing
was typed in.

## IRIX kernel driver, 1024 by 768

From the Entry graphics object of the IRIX 6.5 IP20 boot set (`lg1.a`, member `light_init.o`, data symbols `vtg_ltable`,
`vtg_frtable`, `did_linetable`, `frametable`). Sizes are the symbol sizes. The driver's `initVC1` copies each table to the
SRAM address shown.

### `vtg_ltable`, 0x23a bytes, loaded at SRAM 0x0000

```
0000  0c 00 d8 0d 0c 84 03 0c 85 7f 8c 78 0c 05 d0 81
0010  00 00 00 0c 00 d8 0d 0c 84 03 0c 85 7f 8c f9 00
0020  00 13 0c 00 d9 0d 0c 84 03 0c 87 7f 8c 78 08 8f
0030  81 00 00 22 0c 00 dd 0d 0c 84 03 0c 87 7f 8c 78
0040  08 8f 81 00 00 34 0c 00 dd 0d 0c 84 03 0c 87 78
0050  0c 07 df 7f 0c 8f 81 00 00 46 04 00 df 02 8c 0b
0060  0c 84 03 0c 87 14 ac 01 fc 04 fe 02 7e a7 01 7f
0070  f7 2c fb 02 ff 56 fb 02 ff 32 df 01 8f 11 8d 02
0080  0d d7 01 0c 87 0e 0c 8f 81 00 00 8c 04 00 df 02
0090  8c 0b 0c 84 03 0c 87 0a fc 0f fe 02 7e a7 01 7f
00a0  f7 1a fb 02 ff 45 a7 01 87 01 8f 12 ff 4d bf 01
00b0  8f 07 8d 02 0d d7 01 0c 87 0e 0c 8f 81 00 00 c0
00c0  04 00 df 02 8c 0b 0c 84 03 0c 87 14 ac 01 fc 04
00d0  fe 02 7e a7 01 7f f7 2c fb 02 ff 56 fb 02 ff 32
00e0  df 01 8f 11 8d 02 0d d7 01 0c 87 0e 0c 8f 81 00
00f0  00 f2 04 00 df 02 8c 0b 0c 84 03 0c 87 05 dc 01
0100  fc 13 fe 02 7e a7 01 7f f7 10 a7 01 87 01 8f 12
0110  ff 52 fb 02 ff 46 af 01 8f 0b 8d 02 0d d7 01 0c
0120  87 0e 0c 8f 81 00 01 28 04 00 df 02 8c 0b 0c 84
0130  03 0c 87 0c bc 01 fc 0c fe 02 7e a7 01 7f f7 2f
0140  fb 02 ff 59 87 02 8f 11 df 01 ff 26 df 01 8f 05
0150  8d 02 0d d7 01 0c 87 0e 0c 8f 81 00 01 5e 04 00
0160  df 02 8c 0b 0c 84 03 0c 87 14 ac 01 fc 04 fe 02
0170  7e a7 01 7f f7 2c fb 02 ff 56 fb 02 ff 32 df 01
0180  8f 11 8d 02 0d d7 01 0c 87 0e 0c 8f 81 00 01 90
0190  04 00 df 02 8c 0b 0c 84 03 0c 87 08 ac 01 fc 10
01a0  fe 02 7e a7 01 7f f7 39 87 02 8f 11 df 01 ff 3d
01b0  fb 02 ff 34 cf 01 8f 09 8d 02 0d d7 01 0c 87 0e
01c0  0c 8f 81 00 01 c6 04 00 df 02 8c 0b 0c 84 03 0c
01d0  87 14 ac 01 fc 04 fe 02 7e a7 01 7f f7 58 fb 02
01e0  ff 5e df 01 8f 11 8d 02 0d d7 01 0c 87 0e 0c 8f
01f0  81 00 00 5a 04 00 df 02 8c 0b 0c 84 03 0c 87 14
0200  ac 01 fc 04 fe 02 7e a7 01 7f f7 58 fb 02 ff 5e
0210  df 01 8f 11 8d 02 0d d7 01 0c 87 0e 0c 8f 81 00
0220  01 f4 0c 00 d9 0d 0c 84 03 0c 87 78 0c 07 99 02
0230  0c 07 d9 7d 08 8f 81 00 02 22
```

### `vtg_frtable`, 0x2c bytes, loaded at SRAM 0x0800

```
0000  03 2d 00 00 01 00 13 02 00 34 26 00 46 01 00 5a
0010  78 00 5a 78 00 5a 78 00 5a 78 00 5a 78 00 5a 78
0020  00 5a 2f 01 f4 01 00 22 02 02 22 01
```

### `did_linetable`, 0x8a bytes, loaded at SRAM 0x4800

```
0000  00 01 00 00 00 01 00 01 00 01 00 02 00 01 00 03
0010  00 01 00 04 00 01 00 05 00 01 00 06 00 01 00 07
0020  00 01 00 08 00 01 00 09 00 01 00 0a 00 01 00 0b
0030  00 01 00 0c 00 01 00 0d 00 01 00 0e 00 01 00 0f
0040  00 01 00 10 00 01 00 11 00 01 00 12 00 01 00 13
0050  00 01 00 14 00 01 00 15 00 01 00 16 00 01 00 17
0060  00 01 00 18 00 01 00 19 00 01 00 1a 00 01 00 1b
0070  00 01 00 1c 00 01 00 1d 00 01 00 1e 00 01 00 1f
0080  00 04 00 00 00 00 00 00 00 00
```

### `frametable`, 0x600 bytes, loaded at SRAM 0x4000

Not initialised data: `initVC1` builds it at run time, storing the byte pair 0x48, 0x00 for each of the 0x300 entries and then
overwriting the last pair with 0x48, 0x40. Established (read in full in `initVC1`).

## PROM 4.0.5D (070-8116-004)

The PROM's own copy: 0x232 bytes at PROM address 0xbfc4cf90 (loaded to SRAM 0x0000, length argument 562) and 0x2a bytes at
0xbfc4d1c4 (loaded to SRAM 0x0800, length argument 42). They differ from the kernel's tables in length and contents.

```
bfc4cf90  08 00 98 02 8c 0b 0c 84 03 0c 85 7f 8c 78 0c 05
bfc4cfa0  90 81 00 00 00 08 00 98 02 8c 0b 0c 84 03 0c 85
bfc4cfb0  7f 8c f9 00 00 15 08 00 99 02 8c 0b 0c 84 03 0c
bfc4cfc0  87 7f 8c 78 0c 8f 81 00 00 26 08 00 9d 02 8c 0b
bfc4cfd0  0c 84 03 0c 87 7f 8c 78 0c 8f 81 00 00 3a 08 00
bfc4cfe0  9d 02 8c 0b 0c 84 03 0c 87 78 0c 07 9f 7f 0c 8f
bfc4cff0  81 00 00 4e 04 00 9f 02 8c 0b 0c 84 03 0c 87 14
bfc4d000  ac 01 f8 02 fc 02 fe 02 7e a7 01 7f f7 7f ff 39
bfc4d010  df 01 8f 11 8d 02 0d d7 01 0c 87 0e 0c 8f 81 00
bfc4d020  00 92 04 00 9f 02 8c 0b 0c 84 03 0c 87 0a fc 01
bfc4d030  f8 02 fc 0c fe 02 7e a7 01 7f f7 61 af 01 87 02
bfc4d040  8f 11 ff 01 fb 02 ff 4a bf 01 8f 07 8d 02 0d d7
bfc4d050  01 0c 87 0e 0c 8f 81 00 00 ca 04 00 9f 02 8c 0b
bfc4d060  0c 84 03 0c 87 14 ac 01 f8 02 fc 02 fe 02 7e a7
bfc4d070  01 7f f7 7f ff 39 df 01 8f 11 8d 02 0d d7 01 0c
bfc4d080  87 0e 0c 8f 81 00 00 f8 04 00 9f 02 8c 0b 0c 84
bfc4d090  03 0c 87 05 dc 01 fc 01 f8 02 fc 10 fe 02 7e a7
bfc4d0a0  01 7f f7 10 af 01 87 02 8f 11 ff 01 fb 02 ff 7f
bfc4d0b0  ff 18 af 01 8f 0b 8d 02 0d d7 01 0c 87 0e 0c 8f
bfc4d0c0  81 00 01 34 04 00 9f 02 8c 0b 0c 84 03 0c 87 0c
bfc4d0d0  bc 01 fc 01 f8 02 fc 09 fe 02 7e a7 01 7f f7 7f
bfc4d0e0  ff 0b 8f 01 87 02 8f 10 df 01 fb 02 ff 24 df 01
bfc4d0f0  8f 05 8d 02 0d d7 01 0c 87 0e 0c 8f 81 00 01 70
bfc4d100  04 00 9f 02 8c 0b 0c 84 03 0c 87 14 ac 01 f8 02
bfc4d110  fc 02 fe 02 7e a7 01 7f f7 7f ff 39 df 01 8f 11
bfc4d120  8d 02 0d d7 01 0c 87 0e 0c 8f 81 00 01 9e 04 00
bfc4d130  9f 02 8c 0b 0c 84 03 0c 87 08 ac 01 f8 02 fc 0e
bfc4d140  fe 02 7e a7 01 7f f7 39 8f 01 87 02 8f 10 df 01
bfc4d150  fb 02 ff 71 cf 01 8f 09 8d 02 0d d7 01 0c 87 0e
bfc4d160  0c 8f 81 00 01 d6 04 00 9f 02 8c 0b 0c 84 03 0c
bfc4d170  87 14 ac 01 f8 02 fc 02 fe 02 7e a7 01 7f f7 7f
bfc4d180  ff 39 df 01 8f 11 8d 02 0d d7 01 0c 87 0e 0c 8f
bfc4d190  81 00 00 64 04 00 9f 02 8c 0b 0c 84 03 0c 87 14
bfc4d1a0  ac 01 f8 02 fc 02 fe 02 7e a7 01 7f f7 7f ff 39
bfc4d1b0  df 01 8f 11 8d 02 0d d7 01 0c 87 0e 0c 8f 81 00
bfc4d1c0  02 04
```

```
bfc4d1c4  03 2d 00 00 01 00 15 02 00 3a 26 00 4e 01 00 64
bfc4d1d4  78 00 64 78 00 64 78 00 64 78 00 64 78 00 64 78
bfc4d1e4  00 64 2f 02 04 01 00 26 03 00
```

The PROM 4.0.5G (070-8116-005) holds the same two tables at 0xbfc50a10 and 0xbfc50c44 (byte-identical in the comparison run:
the 4.0.5D bytes were searched in the 4.0.5G image).

## Clock programming bytes

17 bytes written one at a time to the clock port (WCLOCK in the REX1 page) with the function selector at 2, chosen by the
board revision byte (below 2, the first; 2 and above, the second). The kernel's two tables are at `light_init.o` data 0x600 and
0x618; the PROM carries the first at 0xbfc4d230 (4.0.5D) and 0xbfc50cb0 (4.0.5G).

```
rev below 2   c4 00 10 24 30 40 59 60 72 80 90 ad b6 d1 e0 f0 c4
rev 2 and up  c4 0c 17 20 30 4f 51 60 71 80 90 ad b6 d1 e0 f0 c4
```
