// @generated from devices/rex1/registers.toml by defs-gen - do not edit, change the source
// defs-gen 3
// input sha256 3aa82cc4c75111a7e0822c6310f63dc8287b56b5dbc253e1bbc9299ec9d46901
// REX1 raster engine on the Indigo Entry graphics board (LG1)
#![allow(dead_code)]
#![allow(clippy::doc_markdown)]
#![cfg_attr(rustfmt, rustfmt_skip)]

/// Drawing command. Bits 31:28 hold the logic operation, the low bits the opcode and flags listed as CMD_ constants. A write at 0x000 stores it; a write  (established)
pub mod command {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x0;
}
/// Auxiliary control word, one per window context. initRex zeroes it. lightAux1Register builds a value from a window's saved value with bits 4:2 cleared, (established)
pub mod aux1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4;
    pub mod ditherrange { // bits 9:9, unknown
        pub const SHIFT: u32 = 9;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod colorcompgt { // bits 8:8, inferred
        pub const SHIFT: u32 = 8;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod colorcompeq { // bits 7:7, inferred
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod colorcomplt { // bits 6:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod doublebuf { // bits 5:5, inferred
        pub const SHIFT: u32 = 5;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dblsrc { // bits 4:4, inferred
        pub const SHIFT: u32 = 4;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dbldst1 { // bits 3:3, inferred
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dbldst0 { // bits 2:2, inferred
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod fraction { // bits 1:0, unknown
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x3;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Packed draw state word. The kernel stores 0x03ff0000 here before each full-screen clear (rexClear, the command word 0x329 with no logic-operation nibb (established)
pub mod xstate {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8;
    pub mod zopaque { // bits 31:31, unknown
        pub const SHIFT: u32 = 31;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod lsopaque { // bits 30:30, unknown
        pub const SHIFT: u32 = 30;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod copyflag { // bits 29:29, inferred
        pub const SHIFT: u32 = 29;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod coloraux { // bits 28:28, inferred
        pub const SHIFT: u32 = 28;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod logicop { // bits 27:24, inferred
        pub const SHIFT: u32 = 24;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod planemask { // bits 23:16, inferred
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0xff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod colour { // bits 7:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Draw start x as an integer. Twelve bits are kept (the ide test mask is 0xfff) and appear in XSTART at bit 15 and above: lightProbe writes 0x12345678 h (established)
pub mod xstarti {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xc;
}
/// Draw start x, fraction. Test mask 0x7fffff. Offset read from the ide test. Software that draws only rectangles never writes it. Offset established by  (established)
pub mod xstartf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x10;
}
/// Draw start x, integer and fraction combined: 27 bits in the ide test mask, integer in bits 26:15. Read at offset 0x14 by the board probe after XSTARTI (established)
pub mod xstart {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x14;
}
/// Draw end x, fraction (ide mask 0x7ff800). Offset established by the ide test. Holds the end x with the integer in bits 22:11 (a write to XENDI at 0x84 (established)
pub mod xendf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x18;
}
/// Draw start y as an integer, 12 bits kept; the ide test writes it and reads YSTART (0x24) expecting (value & 0xfff) << 15. Software stores 767 minus it (established)
pub mod ystarti {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1c;
}
/// Draw start y, fraction. Offset established by the ide test. Mirror of XSTARTF for y; a write appears in YSTART bits 26:4. For lines the IRIX 6.2 GL wr (established)
pub mod ystartf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x20;
}
/// Draw start y, integer and fraction combined, counterpart of XSTART. Offset inferred; no shipped code reads it. Offset established by the ide test. Com (established)
pub mod ystart {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x24;
}
/// Draw end y, fraction. Offset established by the ide test. Holds the end y with the integer in bits 22:11, as XENDF. (established)
pub mod yendf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x28;
}
/// Saved x start (the x that a block-draw returns to at the start of each row, inferred from its name and the context save). lightPcxSwap saves it with t (established)
pub mod xsave {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x2c;
}
/// Line-draw minor-axis slope. Never written by the shipped light code for rectangles, text or points. Only the name (ide) and the slot between XSAVE and (established)
pub mod minorslope {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x30;
}
/// Copy source offset: x delta in the high 16 bits and y delta in the low 16, each source minus destination, in stored coordinates (display row = stored  (established)
pub mod xymove {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x34;
}
/// Foreground pixel colour (the ide test reads a write back through COLORRED at 0x3c as (value & 0xff) << 11), an 8-bit index into the colour map (the bo (established)
pub mod colorredi {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x38;
}
/// Red channel with fraction for shaded draws, 20 bits in the ide mask. Offset by name order. Offset established by the ide test. COLORRED holds the red  (established)
pub mod colorred {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3c;
}
/// Green channel integer (shaded draws). Never written by shipped light code. Offset from the ide name order and NetBSD. Offset established by the ide te (established)
pub mod colorgreeni {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x40;
}
/// Green channel with fraction. Offset established by the ide test. 20 bits kept. Same format as COLORRED. (established)
pub mod colorgreen {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x44;
}
/// Blue channel integer. Offset established by the ide test. A write here appears in COLORBLUE bits 18:11. (established)
pub mod colorbluei {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x48;
}
/// Blue channel with fraction. Offset established by the ide test. 20 bits kept. Same format as COLORRED. A store at the GO alias (0x84c) runs the latche (established)
pub mod colorblue {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4c;
}
/// Red slope for shaded lines and spans. Not written by shipped light code. Offset established by the ide test. Slope registers are signed: the ide test  (established)
pub mod slopered {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x50;
}
/// Green slope. Not written by shipped light code. NetBSD names offset 0x54 of the configuration page WCLOCKREV, which is a different page. Offset establ (established)
pub mod slopegreen {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x54;
}
/// Blue slope. Not written by shipped light code. Offset established by the ide test. As SLOPERED. Same rule as SLOPERED. A store at the GO alias (0x858) (established)
pub mod slopeblue {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x58;
}
/// Background colour index used for pattern zeros when ZOPAQUE is set. The shipped kernel and PROM glyph paths never write it (transparent background); N (established)
pub mod colorback {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x5c;
}
/// Pixel pattern for the pattern-enabled commands. Software writes it at the GO alias (0x860): each write draws one row of the glyph, taking pattern bits (established)
pub mod zpattern {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x60;
}
/// Line stipple pattern. Not written by shipped light code. Offset established by the ide test. Fully read/write. The IRIX 6.2 GL stores the 16-bit GL st (established)
pub mod lspattern {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x64;
}
/// Line stipple mode. Not written by shipped light code. NetBSD's configuration-page name CFGMODE for offset 0x68 is a different page. Offset established (established)
pub mod lsmode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x68;
}
/// Antialias weight. Not written by shipped light code. Offset established by the ide test. Fully read/write. The IRIX 6.2 GL writes 0xdb987642 once at c (established)
pub mod aweight {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x6c;
}
/// Read/write auxiliary word used to read and write pixel memory with a draw command. lightInitInfo writes 0x01081020 here, then 0x09090909 with a 0x3021 (established)
pub mod rwaux1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x70;
}
/// Second read/write auxiliary word. Not written by shipped light code. Offset established by the ide test. Fully read/write. (established)
pub mod rwaux2 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x74;
}
/// Plane write mask for read/write pixel access. lightInitInfo and the PROM write 0xff (all eight planes) before the pixel-memory probe. The ide mask 0xf (established)
pub mod rwmask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x78;
}
/// Screen mask 1, x range: maximum x in bits 25:16 and minimum x in bits 9:0, each clipped to 0..1023 (the object clamps with 0x3ff). Software computes t (established)
pub mod smask1x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x7c;
}
/// Screen mask 1, y range, same packing, clipped to 0..767 (0x2ff). The y values are flipped (height minus row minus one) before packing, so they use the (established)
pub mod smask1y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x80;
}
/// Draw end x (integer, inclusive): the last column a STOPONX command draws. The ide test reads it back through XENDF (0x18) as (value & 0xfff) << 11. (established)
pub mod xendi {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x84;
}
/// Draw end y (integer, inclusive), top-down row like YSTARTI. The glyph commands also use the order of YSTARTI and YENDI to pick the direction rows adva (established)
pub mod yendi {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x88;
}
/// First of six consecutive screen-mask words, in the order SMASK2X, SMASK2Y, SMASK3X, SMASK3Y, SMASK4X, SMASK4Y. The six-word run is established by the  (established)
pub mod smask2x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4790;
}
/// Screen mask word 2Y. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six. (established)
pub mod smask2y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4794;
}
/// Screen mask word 3X. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six. (established)
pub mod smask3x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4798;
}
/// Screen mask word 3Y. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six. (established)
pub mod smask3y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x479c;
}
/// Screen mask word 4X. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six. (established)
pub mod smask4x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47a0;
}
/// Screen mask word 4Y. Packing as smask1x. Added in the 2026-11-23 review so the generated header names all six. (established)
pub mod smask4y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47a4;
}
/// Second auxiliary control word. Both initialisations store 0x20000000. lightSetDestinationPlanes keeps bits 28:0 of the window's saved value, ORs in th (established)
pub mod aux2 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47a8;
    pub mod planegroup { // bits 31:29, inferred
        pub const SHIFT: u32 = 29;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cidmatch4 { // bits 23:20, inferred
        pub const SHIFT: u32 = 20;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cidmatch3 { // bits 19:16, inferred
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cidmatch2 { // bits 15:12, inferred
        pub const SHIFT: u32 = 12;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cidmatch1 { // bits 11:8, inferred
        pub const SHIFT: u32 = 8;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod smask_inside { // bits 7:4, inferred
        pub const SHIFT: u32 = 4;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod smask_enable { // bits 3:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// VRAM diagnostic access. No shipped kernel or PROM runtime path touches it; the ide VRAM test is the only candidate user and was not read. Offset and r (inferred)
pub mod diagvram {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47d8;
}
/// Port to the pixel clock generator and the board configuration byte; the byte is picked by CFGSEL. Reading with CFGSEL 4 (after a dummy read of the GO  (established)
pub mod wclock {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47e4;
}
/// Port to the colour map chip. CFGSEL picks the chip register (see CFGSEL constants). Software writes the same byte to RWDAC and to its GO alias; the se (established)
pub mod rwdac {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47e8;
}
/// Three-bit function selector shared by WCLOCK, RWDAC and RWVC1: the value written here is the chip register index the next access to any of the three p (established)
pub mod configsel {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47ec;
}
/// Port to the video controller (VC1), same SET/GO scheme as RWDAC with its GO alias 0x800 above it. A write stores the byte at SET and again at GO; a GO (established)
pub mod rwvc1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47f0;
}
/// Written with 0 in the middle of a window context swap. lightPcxSwap reads ten registers (XSTART, YSTART, COLORRED, COLORGREEN, COLORBLUE, LSPATTERN, L (inferred)
pub mod togglectxt {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47f4;
}
/// Configuration and status. Bit 0 is the engine busy flag: all software spins until it is clear before touching a drawing register (the kernel and the P (established)
pub mod configmode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47f8;
}
/// Window origin offset: x in bits 27:16 and y in bits 11:0, 0x800 each at init (the window offset of 2048 that centres a 12-bit coordinate space; the ce (established)
pub mod xywin {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x47fc;
}
pub const BASE_HEAD0: u32 = 0x1f3f0000; // established
pub const BASE_HEAD1: u32 = 0x1f3f8000; // established
pub const CFGSEL_DAC_ADDR: u32 = 0x0; // established
pub const CFGSEL_HADDR: u32 = 0x5; // established
pub const CFGSEL_LADDR: u32 = 0x4; // established
pub const CFGSEL_PALETTE: u32 = 0x1; // established
pub const CFGSEL_PIXMASK: u32 = 0x2; // established
pub const CFGSEL_RDADDR: u32 = 0x3; // established
pub const CFGSEL_SYSCTL: u32 = 0x6; // established
pub const CMD_BLOCK: u32 = 0x8; // established
pub const CMD_CLEAR_RGB_DITHER: u32 = 0x3000c329; // established
pub const CMD_COPY_RECT: u32 = 0x30080329; // established
pub const CMD_COPY_RECT_GL: u32 = 0x30280329; // established
pub const CMD_COPY_RECT_STATE: u32 = 0x80329; // established
pub const CMD_DITHER: u32 = 0x8000; // inferred
pub const CMD_DRAW: u32 = 0x1; // established
pub const CMD_ENLSPATTERN: u32 = 0x800; // inferred
pub const CMD_ENZPATTERN: u32 = 0x400; // established
pub const CMD_FILL_RECT: u32 = 0x30000329; // established
pub const CMD_FILL_RECT_STATE: u32 = 0x329; // established
pub const CMD_GLYPH16: u32 = 0x300005b9; // established
pub const CMD_GLYPH_PIECE: u32 = 0x300005a1; // established
pub const CMD_GL_TRIANGLE_ROW_SHADED_MASKED: u32 = 0x3212c5b1; // established
pub const CMD_HOSTDATA: u32 = 0x200000; // inferred
pub const CMD_HOSTDATA_READ: u32 = 0x2000ab; // established
pub const CMD_HOSTDATA_WRITE: u32 = 0x2000a9; // established
pub const CMD_INITFRAC: u32 = 0x40000; // unknown
pub const CMD_LENGTH32: u32 = 0x10; // inferred
pub const CMD_LOGICOP_SHIFT: u32 = 0x1c; // established
pub const CMD_LOGICSRC: u32 = 0x80000; // inferred
pub const CMD_LRQPOLY: u32 = 0x2000000; // unknown
pub const CMD_LSADVLAST: u32 = 0x1000; // inferred
pub const CMD_LSCONTINUE: u32 = 0x2000; // inferred
pub const CMD_OP_READ: u32 = 0x2; // inferred
pub const CMD_PIXMEM_BIT16: u32 = 0x10000; // inferred
pub const CMD_PIXMEM_READ: u32 = 0x30200023; // established
pub const CMD_PIXMEM_WRITE_A: u32 = 0x30200021; // established
pub const CMD_PIXMEM_WRITE_B: u32 = 0x30210021; // established
pub const CMD_POINT: u32 = 0x30000001; // established
pub const CMD_QUAD: u32 = 0x20; // inferred
pub const CMD_RGBMODE: u32 = 0x4000; // inferred
pub const CMD_SHADE: u32 = 0x20000; // inferred
pub const CMD_SHADECONTINUE: u32 = 0x100000; // inferred
pub const CMD_SPAN: u32 = 0x121; // established
pub const CMD_SPAN_LSPATTERN: u32 = 0x921; // inferred
pub const CMD_STOPONX: u32 = 0x100; // established
pub const CMD_STOPONY: u32 = 0x200; // established
pub const CMD_TILE_HOSTDATA: u32 = 0x200121; // established
pub const CMD_XMAJOR: u32 = 0x40; // inferred
pub const CMD_XYCONTINUE: u32 = 0x80; // established
pub const CMD_ZCONTINUE: u32 = 0x1000000; // unknown
pub const CMD_ZOPAQUE: u32 = 0x800000; // inferred
pub const GO_OFFSET: u32 = 0x800; // established
pub const PROBE_READBACK: u32 = 0x33c0000; // established
pub const VC1_SYSCTL_CURSOR: u32 = 0x10; // inferred
pub const VC1_SYSCTL_CURSOR_ON: u32 = 0x20; // inferred
pub const VC1_SYSCTL_VIDEO_ON: u32 = 0x4; // established
pub const XRES: u32 = 0x400; // established
pub const YRES: u32 = 0x300; // established
