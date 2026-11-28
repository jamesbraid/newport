// @generated from devices/rex3/registers.toml by defs-gen - do not edit, change the source
// SPDX-License-Identifier: BSD-3-Clause
// defs-gen 5
// input sha256 7ba54c6ee573d96e32054fc5d3a0227ba4f16cf9fe67a4c195d8202f1ea7dea4
// REX3 raster engine (Indy and Indigo2 graphics)
#![allow(dead_code)]
#![allow(clippy::doc_markdown)]
#![cfg_attr(rustfmt, rustfmt_skip)]

pub mod enums {
    pub mod adrmode {
        pub const SPAN: u32 = 0; // established
        pub const BLOCK: u32 = 1; // established
        pub const ILINE: u32 = 2; // established
        pub const FLINE: u32 = 3; // established
        pub const ALINE: u32 = 4; // established
        pub const TLINE: u32 = 5; // inferred
        pub const BLINE: u32 = 6; // inferred
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            Span,
            Block,
            Iline,
            Fline,
            Aline,
            Tline,
            Bline,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::Span,
                    1 => Self::Block,
                    2 => Self::Iline,
                    3 => Self::Fline,
                    4 => Self::Aline,
                    5 => Self::Tline,
                    6 => Self::Bline,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::Span => 0,
                    Self::Block => 1,
                    Self::Iline => 2,
                    Self::Fline => 3,
                    Self::Aline => 4,
                    Self::Tline => 5,
                    Self::Bline => 6,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod dcbaddr {
        pub const VC2: u32 = 0; // established
        pub const CMAP_ALL: u32 = 1; // established
        pub const CMAP0: u32 = 2; // established
        pub const CMAP1: u32 = 3; // established
        pub const XMAP_ALL: u32 = 4; // established
        pub const XMAP0: u32 = 5; // established
        pub const XMAP1: u32 = 6; // established
        pub const RAMDAC: u32 = 7; // established
        pub const VIDEO_CC1: u32 = 8; // established
        pub const VIDEO_AB1: u32 = 9; // established
        pub const LG3_BDVERS0: u32 = 10; // inferred
        pub const ICS1562: u32 = 11; // inferred
        pub const RESERVED: u32 = 15; // inferred
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            Vc2,
            CmapAll,
            Cmap0,
            Cmap1,
            XmapAll,
            Xmap0,
            Xmap1,
            Ramdac,
            VideoCc1,
            VideoAb1,
            Lg3Bdvers0,
            Ics1562,
            Reserved,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::Vc2,
                    1 => Self::CmapAll,
                    2 => Self::Cmap0,
                    3 => Self::Cmap1,
                    4 => Self::XmapAll,
                    5 => Self::Xmap0,
                    6 => Self::Xmap1,
                    7 => Self::Ramdac,
                    8 => Self::VideoCc1,
                    9 => Self::VideoAb1,
                    10 => Self::Lg3Bdvers0,
                    11 => Self::Ics1562,
                    15 => Self::Reserved,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::Vc2 => 0,
                    Self::CmapAll => 1,
                    Self::Cmap0 => 2,
                    Self::Cmap1 => 3,
                    Self::XmapAll => 4,
                    Self::Xmap0 => 5,
                    Self::Xmap1 => 6,
                    Self::Ramdac => 7,
                    Self::VideoCc1 => 8,
                    Self::VideoAb1 => 9,
                    Self::Lg3Bdvers0 => 10,
                    Self::Ics1562 => 11,
                    Self::Reserved => 15,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod dcbwidth {
        pub const W4: u32 = 0; // established
        pub const W1: u32 = 1; // established
        pub const W2: u32 = 2; // established
        pub const W3: u32 = 3; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            W4,
            W1,
            W2,
            W3,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::W4,
                    1 => Self::W1,
                    2 => Self::W2,
                    3 => Self::W3,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::W4 => 0,
                    Self::W1 => 1,
                    Self::W2 => 2,
                    Self::W3 => 3,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod depth {
        pub const D4: u32 = 0; // established
        pub const D8: u32 = 1; // established
        pub const D12: u32 = 2; // established
        pub const D24: u32 = 3; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            D4,
            D8,
            D12,
            D24,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::D4,
                    1 => Self::D8,
                    2 => Self::D12,
                    3 => Self::D24,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::D4 => 0,
                    Self::D8 => 1,
                    Self::D12 => 2,
                    Self::D24 => 3,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod dfactor {
        pub const ZERO: u32 = 0; // established
        pub const ONE: u32 = 1; // established
        pub const SC: u32 = 2; // established
        pub const MSC: u32 = 3; // established
        pub const SA: u32 = 4; // established
        pub const MSA: u32 = 5; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            Zero,
            One,
            Sc,
            Msc,
            Sa,
            Msa,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::Zero,
                    1 => Self::One,
                    2 => Self::Sc,
                    3 => Self::Msc,
                    4 => Self::Sa,
                    5 => Self::Msa,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::Zero => 0,
                    Self::One => 1,
                    Self::Sc => 2,
                    Self::Msc => 3,
                    Self::Sa => 4,
                    Self::Msa => 5,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod hostdepth {
        pub const H4: u32 = 0; // established
        pub const H8: u32 = 1; // established
        pub const H12: u32 = 2; // established
        pub const H32: u32 = 3; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            H4,
            H8,
            H12,
            H32,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::H4,
                    1 => Self::H8,
                    2 => Self::H12,
                    3 => Self::H32,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::H4 => 0,
                    Self::H8 => 1,
                    Self::H12 => 2,
                    Self::H32 => 3,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod logicop {
        pub const ZERO: u32 = 0; // established
        pub const AND: u32 = 1; // established
        pub const ANDR: u32 = 2; // established
        pub const SRC: u32 = 3; // established
        pub const ANDI: u32 = 4; // established
        pub const DST: u32 = 5; // established
        pub const XOR: u32 = 6; // established
        pub const OR: u32 = 7; // established
        pub const NOR: u32 = 8; // established
        pub const XNOR: u32 = 9; // established
        pub const NDST: u32 = 10; // established
        pub const ORR: u32 = 11; // established
        pub const NSRC: u32 = 12; // established
        pub const ORI: u32 = 13; // established
        pub const NAND: u32 = 14; // established
        pub const ONE: u32 = 15; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            Zero,
            And,
            Andr,
            Src,
            Andi,
            Dst,
            Xor,
            Or,
            Nor,
            Xnor,
            Ndst,
            Orr,
            Nsrc,
            Ori,
            Nand,
            One,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::Zero,
                    1 => Self::And,
                    2 => Self::Andr,
                    3 => Self::Src,
                    4 => Self::Andi,
                    5 => Self::Dst,
                    6 => Self::Xor,
                    7 => Self::Or,
                    8 => Self::Nor,
                    9 => Self::Xnor,
                    10 => Self::Ndst,
                    11 => Self::Orr,
                    12 => Self::Nsrc,
                    13 => Self::Ori,
                    14 => Self::Nand,
                    15 => Self::One,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::Zero => 0,
                    Self::And => 1,
                    Self::Andr => 2,
                    Self::Src => 3,
                    Self::Andi => 4,
                    Self::Dst => 5,
                    Self::Xor => 6,
                    Self::Or => 7,
                    Self::Nor => 8,
                    Self::Xnor => 9,
                    Self::Ndst => 10,
                    Self::Orr => 11,
                    Self::Nsrc => 12,
                    Self::Ori => 13,
                    Self::Nand => 14,
                    Self::One => 15,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod opcode {
        pub const NOOP: u32 = 0; // established
        pub const READ: u32 = 1; // established
        pub const DRAW: u32 = 2; // established
        pub const SCR2SCR: u32 = 3; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            Noop,
            Read,
            Draw,
            Scr2scr,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::Noop,
                    1 => Self::Read,
                    2 => Self::Draw,
                    3 => Self::Scr2scr,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::Noop => 0,
                    Self::Read => 1,
                    Self::Draw => 2,
                    Self::Scr2scr => 3,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod planes {
        pub const NONE: u32 = 0; // established
        pub const RGB: u32 = 1; // established
        pub const RGBA: u32 = 2; // established
        pub const OLAY: u32 = 4; // established
        pub const PUP: u32 = 5; // established
        pub const CID: u32 = 6; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            None,
            Rgb,
            Rgba,
            Olay,
            Pup,
            Cid,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::None,
                    1 => Self::Rgb,
                    2 => Self::Rgba,
                    4 => Self::Olay,
                    5 => Self::Pup,
                    6 => Self::Cid,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::None => 0,
                    Self::Rgb => 1,
                    Self::Rgba => 2,
                    Self::Olay => 4,
                    Self::Pup => 5,
                    Self::Cid => 6,
                    Self::Other(v) => v,
                }
            }
        }
    }
    pub mod sfactor {
        pub const ZERO: u32 = 0; // established
        pub const ONE: u32 = 1; // established
        pub const DC: u32 = 2; // established
        pub const MDC: u32 = 3; // established
        pub const SA: u32 = 4; // established
        pub const MSA: u32 = 5; // established
        #[derive(Debug, Clone, Copy, PartialEq, Eq)]
        pub enum Value {
            Zero,
            One,
            Dc,
            Mdc,
            Sa,
            Msa,
            Other(u32),
        }
        impl Value {
            pub const fn from_raw(v: u32) -> Self {
                match v {
                    0 => Self::Zero,
                    1 => Self::One,
                    2 => Self::Dc,
                    3 => Self::Mdc,
                    4 => Self::Sa,
                    5 => Self::Msa,
                    _ => Self::Other(v),
                }
            }
            pub const fn raw(self) -> u32 {
                match self {
                    Self::Zero => 0,
                    Self::One => 1,
                    Self::Dc => 2,
                    Self::Mdc => 3,
                    Self::Sa => 4,
                    Self::Msa => 5,
                    Self::Other(v) => v,
                }
            }
        }
    }
}

/// Draw mode word 1: the plane group and depth a draw writes, the host-port packing (RWPACKED, HOSTDEPTH, RWDOUBLE, SWAPENDIAN, written up in devices/rex (established)
pub mod drawmode1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x0;
    pub mod logicop { // bits 31:28, established
        pub const SHIFT: u32 = 28;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::logicop::Value;
    }
    pub mod blendalpha { // bits 27:27, inferred
        pub const SHIFT: u32 = 27;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod prefetch { // bits 26:26, established
        pub const SHIFT: u32 = 26;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod backblend { // bits 25:25, inferred
        pub const SHIFT: u32 = 25;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dfactor { // bits 24:22, established
        pub const SHIFT: u32 = 22;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::dfactor::Value;
    }
    pub mod sfactor { // bits 21:19, established
        pub const SHIFT: u32 = 19;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::sfactor::Value;
    }
    pub mod blend { // bits 18:18, inferred
        pub const SHIFT: u32 = 18;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod fastclear { // bits 17:17, established
        pub const SHIFT: u32 = 17;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dither { // bits 16:16, inferred
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod rgbmode { // bits 15:15, established
        pub const SHIFT: u32 = 15;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod compare_gt { // bits 14:14, established
        pub const SHIFT: u32 = 14;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod compare_eq { // bits 13:13, established
        pub const SHIFT: u32 = 13;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod compare_lt { // bits 12:12, established
        pub const SHIFT: u32 = 12;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod swapendian { // bits 11:11, established
        pub const SHIFT: u32 = 11;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod rwdouble { // bits 10:10, established
        pub const SHIFT: u32 = 10;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod hostdepth { // bits 9:8, established
        pub const SHIFT: u32 = 8;
        pub const MASK: u32 = 0x3;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::hostdepth::Value;
    }
    pub mod rwpacked { // bits 7:7, established
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod yflip { // bits 6:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dblsrc { // bits 5:5, established
        pub const SHIFT: u32 = 5;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod drawdepth { // bits 4:3, established
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x3;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::depth::Value;
    }
    pub mod planes { // bits 2:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::planes::Value;
    }
}
/// Draw mode word 0, the command register: the opcode, the addressing mode and the per-primitive option bits. NetBSD's console code draws with opcode dra (established)
pub mod drawmode0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4;
    pub mod ystride { // bits 23:23, established
        pub const SHIFT: u32 = 23;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod endptfilter { // bits 22:22, established
        pub const SHIFT: u32 = 22;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod ciclamp { // bits 21:21, established
        pub const SHIFT: u32 = 21;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod xyoffset { // bits 20:20, established
        pub const SHIFT: u32 = 20;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod lronly { // bits 19:19, established
        pub const SHIFT: u32 = 19;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod shade { // bits 18:18, established
        pub const SHIFT: u32 = 18;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod lsopaque { // bits 17:17, inferred
        pub const SHIFT: u32 = 17;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod zpopaque { // bits 16:16, inferred
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod length32 { // bits 15:15, established
        pub const SHIFT: u32 = 15;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod lsadvlast { // bits 14:14, established
        pub const SHIFT: u32 = 14;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod enlspattern { // bits 13:13, established
        pub const SHIFT: u32 = 13;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod enzpattern { // bits 12:12, established
        pub const SHIFT: u32 = 12;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod skiplast { // bits 11:11, established
        pub const SHIFT: u32 = 11;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod skipfirst { // bits 10:10, established
        pub const SHIFT: u32 = 10;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod stopony { // bits 9:9, established
        pub const SHIFT: u32 = 9;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod stoponx { // bits 8:8, established
        pub const SHIFT: u32 = 8;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod alphahost { // bits 7:7, established
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod colorhost { // bits 6:6, established
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dosetup { // bits 5:5, established
        pub const SHIFT: u32 = 5;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod adrmode { // bits 4:2, established
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::adrmode::Value;
    }
    pub mod opcode { // bits 1:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x3;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::opcode::Value;
    }
}
/// Line-stipple mode word. Its field layout is in neither header, so none is given here. (established)
pub mod lsmode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8;
}
/// Line-stipple pattern word. (established)
pub mod lspattern {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xc;
}
/// Backup copy of the stipple pattern, named save by Linux's comment (a backup of the pattern). (established)
pub mod lspatsave {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x10;
}
/// Per-pixel pattern word; NetBSD's glyph path writes it at the GO alias once per row, with the row's glyph bits. (established)
pub mod zpattern {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x14;
}
/// Background colour. NetBSD stores the glyph background colour index here. (established)
pub mod colorback {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x18;
}
/// Clear colour for the fast VRAM clear (Linux comment); NetBSD's rectangle fill writes the colour here with FASTCLEAR set. (established)
pub mod colorvram {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1c;
}
/// Reference alpha value for the alpha-function compare (Linux comment). (established)
pub mod alpharef {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x20;
}
/// NetBSD names this word a stall register and its comment says a write waits until the engine is idle. Linux declares only a pad here. Role inferred fro (inferred)
pub mod stall0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x24;
}
/// Screen mask 0, x extent: a minimum and a maximum packed in one word (NetBSD's comment says min and max, 16.16). Which half is which is not read. (established)
pub mod smask0x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x28;
}
/// Screen mask 0, y extent, packed as SMASK0X. (established)
pub mod smask0y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x2c;
}
/// Setup trigger. Both headers declare it; neither drives it in the console paths read. Linux names it with a leading underscore. (established)
pub mod setup {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x30;
}
/// Linux declares a word here named stepz. Single source; role unknown beyond the name. (inferred)
pub mod stepz {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x34;
}
/// Linux declares it, next to LSPATSAVE; the name reads as restoring the stipple state. Single source; role inferred from the name only. (inferred)
pub mod lsrestore {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x38;
}
/// Linux declares it next to LSRESTORE; the name reads as saving the stipple state. Single source; role inferred from the name only. (inferred)
pub mod lssave {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3c;
}
/// Current x start of the primitive, integer and fraction combined. NetBSD's board probe writes 0x12345678 to XSTARTI and expects this register to read t (established)
pub mod xstart {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x100;
}
/// Current y start, counterpart of XSTART. Single source (the name pairs it with XSTART). (inferred)
pub mod ystart {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x104;
}
/// Current x end point. Single source. (inferred)
pub mod xend {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x108;
}
/// Current y end point. Single source. (inferred)
pub mod yend {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x10c;
}
/// Copy of the integer x start for block addressing, from the Linux comment (a copy of xstart for block mode). Single source. (inferred)
pub mod xsave {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x110;
}
/// Signed x and y offset applied for relative operations such as a screen copy (Linux comment: an offset from xstart, ystart). NetBSD packs x in bits 31: (established)
pub mod xymove {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x114;
    pub mod x { // bits 31:16, established
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod y { // bits 15:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Bresenham line decision term (name only). Single source. (inferred)
pub mod bresd {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x118;
}
/// Bresenham line term S1 (name only). Single source. (inferred)
pub mod bress1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x11c;
}
/// Bresenham octant and first increment. The host-pixel image put clears it before storing pixel words (devices/rex3/host-pixels.md). (established)
pub mod bresoctinc1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x120;
}
/// Bresenham rounding mode and second increment (name only). Single source. (inferred)
pub mod bresrndinc2 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x124;
}
/// Bresenham error term E1 (name only). Single source. (inferred)
pub mod brese1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x128;
}
/// Bresenham term S2 (name only). Single source. (inferred)
pub mod bress2 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x12c;
}
/// Anti-aliased line weight table entry (name only). Single source. (inferred)
pub mod aweight0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x130;
}
/// Anti-aliased line weight table entry (name only). Single source. (inferred)
pub mod aweight1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x134;
}
/// Start x as a float-format value (Linux types it as a float or word union). Single source. (inferred)
pub mod xstartf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x138;
}
/// Start y, same layout as XSTARTF. Single source. (inferred)
pub mod ystartf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x13c;
}
/// End x, same layout as XSTARTF. Single source. (inferred)
pub mod xendf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x140;
}
/// End y, same layout as XSTARTF. Single source. (inferred)
pub mod yendf {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x144;
}
/// Start x as an integer. NetBSD's board probe writes 0x12345678 here and reads XSTART; see that register. (established)
pub mod xstarti {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x148;
}
/// A second end-x word Linux declares (named xendf1). Single source; MAME's model reads this offset as a copy of the XENDF word, which is a model, not ev (inferred)
pub mod xendf1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x14c;
}
/// Start x and y as one packed integer word: x in bits 31:16, y in bits 15:0 (NetBSD packs x << 16 | y; devices/rex3/host-pixels.md records the image put (established)
pub mod xystarti {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x150;
    pub mod x { // bits 31:16, established
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod y { // bits 15:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// End x and y as one packed integer word, packed as XYSTARTI. (established)
pub mod xyendi {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x154;
    pub mod x { // bits 31:16, established
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod y { // bits 15:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Start and end x as integers in one word (name only). Single source. (inferred)
pub mod xstartendi {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x158;
}
/// Red (or colour-index) colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switc (inferred)
pub mod colorred {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x200;
}
/// Alpha colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source (inferred)
pub mod coloralpha {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x204;
}
/// Green colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source (inferred)
pub mod colorgrn {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x208;
}
/// Blue colour, full state. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; (inferred)
pub mod colorblue {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x20c;
}
/// Red (or colour-index) slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch.  (inferred)
pub mod slopered {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x210;
}
/// Alpha slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; t (inferred)
pub mod slopealpha {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x214;
}
/// Green slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; t (inferred)
pub mod slopegrn {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x218;
}
/// Blue slope per pixel. Named and placed by Linux alone, whose comment calls the group iterators with full state for a context switch. Single source; th (inferred)
pub mod slopeblue {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x21c;
}
/// Plane write mask. NetBSD stores 0xffffffff for a fill and 0xff when drawing 8-bit glyphs. (established)
pub mod wrmask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x220;
}
/// Packed integer colour. NetBSD stores the glyph foreground colour index here. (established)
pub mod colori {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x224;
}
/// Linux declares a colour word here named colorx. Single source; role unknown beyond the name. (inferred)
pub mod colorx {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x228;
}
/// Linux declares a second red slope word here. Single source; role unknown beyond the name. (inferred)
pub mod slopered1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x22c;
}
/// Host data port, most significant word (devices/rex3/host-pixels.md for the packing at each depth and the GO alias used for pixel stores). (established)
pub mod hostrw0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x230;
}
/// Host data port, least significant word; used only for 64-bit transfers (devices/rex3/host-pixels.md). (established)
pub mod hostrw1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x234;
}
/// Display control bus mode: the data width, the slave address and register select, the acknowledge type and the chip-select timing for the next DCBDATA  (established)
pub mod dcbmode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x238;
    pub mod swapendian { // bits 28:28, established
        pub const SHIFT: u32 = 28;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cssetup { // bits 27:23, established
        pub const SHIFT: u32 = 23;
        pub const MASK: u32 = 0x1f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cshold { // bits 22:18, established
        pub const SHIFT: u32 = 18;
        pub const MASK: u32 = 0x1f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cswidth { // bits 17:13, established
        pub const SHIFT: u32 = 13;
        pub const MASK: u32 = 0x1f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod enasyncack { // bits 12:12, established
        pub const SHIFT: u32 = 12;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod ensyncack { // bits 11:11, established
        pub const SHIFT: u32 = 11;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dcbaddr { // bits 10:7, established
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::dcbaddr::Value;
    }
    pub mod dcbcrs { // bits 6:4, established
        pub const SHIFT: u32 = 4;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod encrsinc { // bits 3:3, established
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod endatapack { // bits 2:2, established
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod datawidth { // bits 1:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x3;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
        #[allow(unused_imports)]
        pub use super::super::enums::dcbwidth::Value;
    }
}
/// Display bus data, most significant word. Linux accesses it as a word, as halfword 1 at +2 and as byte 3 at +3 depending on DATAWIDTH; NetBSD packs the (established)
pub mod dcbdata0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x240;
}
/// Display bus data, least significant word. (established)
pub mod dcbdata1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x244;
}
/// Screen mask 1 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask1x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1300;
}
/// Screen mask 1 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask1y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1304;
}
/// Screen mask 2 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask2x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1308;
}
/// Screen mask 2 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask2y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x130c;
}
/// Screen mask 3 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask3x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1310;
}
/// Screen mask 3 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask3y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1314;
}
/// Screen mask 4 x extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask4x {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1318;
}
/// Screen mask 4 y extent, a minimum and a maximum packed in one word (NetBSD's comment: min and max, 16.16). Enabled through CLIPMODE. (established)
pub mod smask4y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x131c;
}
/// Top-of-screen scanline. NetBSD's console init stores 0x3ff here with a comment that it does not know why; the meaning is read from the name only. (established)
pub mod topscan {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1320;
}
/// Window origin offset, x in bits 31:16 and y in bits 15:0 (inferred from NetBSD's console init, which stores 4096 in both halves). Linux declares it un (established)
pub mod xywin {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1324;
    pub mod x { // bits 31:16, inferred
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod y { // bits 15:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Clipping mode: one enable per screen mask (0 to 4) in bits 4:0 and four window-id match enables in bits 12:9. NetBSD stores a value at init that sets  (established)
pub mod clipmode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1328;
    pub mod cidmatch3 { // bits 12:12, established
        pub const SHIFT: u32 = 12;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cidmatch2 { // bits 11:11, established
        pub const SHIFT: u32 = 11;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cidmatch1 { // bits 10:10, established
        pub const SHIFT: u32 = 10;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod cidmatch0 { // bits 9:9, established
        pub const SHIFT: u32 = 9;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod smask4 { // bits 4:4, established
        pub const SHIFT: u32 = 4;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod smask3 { // bits 3:3, established
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod smask2 { // bits 2:2, established
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod smask1 { // bits 1:1, established
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod smask0 { // bits 0:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// NetBSD names this word a stall register, matching STALL0. Role inferred from the name; neither driver writes it. (inferred)
pub mod stall1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x132c;
}
/// Configuration register. NetBSD names the offset; the bit groups are Linux's alone, and no reading of any of them exists, so every field is inferred as (inferred)
pub mod config {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1330;
    pub mod fbtyp { // bits 20:20, inferred
        pub const SHIFT: u32 = 20;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod vr { // bits 19:17, inferred
        pub const SHIFT: u32 = 17;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod to { // bits 16:14, inferred
        pub const SHIFT: u32 = 14;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod gfaint { // bits 13:13, inferred
        pub const SHIFT: u32 = 13;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod gd { // bits 12:8, inferred
        pub const SHIFT: u32 = 8;
        pub const MASK: u32 = 0x1f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod bfaint { // bits 7:7, inferred
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod bd { // bits 6:3, inferred
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod ercvr { // bits 2:2, inferred
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod bwidth { // bits 1:1, inferred
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod g32md { // bits 0:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Status. Drivers only read it, polling the busy bits and the FIFO levels before sending more work. NetBSD and Linux agree on the busy bits and on the g (established)
pub mod status {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1338;
    pub mod gfirq { // bits 20:20, inferred
        pub const SHIFT: u32 = 20;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod bfirq { // bits 19:19, inferred
        pub const SHIFT: u32 = 19;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod blevel { // bits 17:13, inferred
        pub const SHIFT: u32 = 13;
        pub const MASK: u32 = 0x1f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod glevel { // bits 12:7, established
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x3f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod vidint { // bits 6:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod vrint { // bits 5:5, inferred
        pub const SHIFT: u32 = 5;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod bbusy { // bits 4:4, established
        pub const SHIFT: u32 = 4;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod gbusy { // bits 3:3, established
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod vers { // bits 2:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Linux declares a second status word here. Single source; no reading of its bits. MAME's model returns the status word for it, which is a model, not ev (inferred)
pub mod ustatus {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x133c;
}
/// Linux declares a display-bus reset word here. Single source; no driver writes it. Role inferred from the name only. (inferred)
pub mod dcbreset {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1340;
}
pub const BASE_FROM_BOARD: u32 = 0xf0000; // established
pub const GO_OFFSET: u32 = 0x800; // established
pub const PROBE_XSTART_SHIFT: u32 = 0xb; // established

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn dcbmode_84100b() {
        assert_eq!(dcbmode::datawidth::get(0x84100b), 3);
        assert_eq!(dcbmode::encrsinc::get(0x84100b), 1);
        assert_eq!(dcbmode::dcbcrs::get(0x84100b), 0);
        assert_eq!(dcbmode::dcbaddr::get(0x84100b), 0);
        assert_eq!(dcbmode::enasyncack::get(0x84100b), 1);
        assert_eq!(dcbmode::cshold::get(0x84100b), 1);
        assert_eq!(dcbmode::cssetup::get(0x84100b), 1);
    }

    #[test]
    fn clipmode_1e00() {
        assert_eq!(clipmode::cidmatch0::get(0x1e00), 1);
        assert_eq!(clipmode::cidmatch1::get(0x1e00), 1);
        assert_eq!(clipmode::cidmatch2::get(0x1e00), 1);
        assert_eq!(clipmode::cidmatch3::get(0x1e00), 1);
        assert_eq!(clipmode::smask0::get(0x1e00), 0);
    }
}
