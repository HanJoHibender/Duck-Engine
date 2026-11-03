use bevy::prelude::*;

#[derive(Copy, Clone, Debug, PartialEq, Eq, Hash, Default)]
#[repr(u8)]
pub enum BlockType {
    #[default]
    Air = 0,
    Grass = 1,
    Dirt = 2,
    Stone = 3,
    Wood = 4,
    Leaves = 5,
    Sand = 6,
    Glass = 7,
}

impl BlockType {
    /// Returns true if the block is solid (blocks light and has solid faces).
    #[inline]
    pub fn is_opaque(&self) -> bool {
        match self {
            BlockType::Air => false,
            BlockType::Glass => false,
            _ => true,
        }
    }

    /// Returns true if the block is air (empty space).
    #[inline]
    pub fn is_air(&self) -> bool {
        matches!(self, BlockType::Air)
    }

    /// Returns base RGBA color for this block type (used for vertex colors and materials).
    pub fn base_color(&self) -> Color {
        match self {
            BlockType::Air => Color::srgba(0.0, 0.0, 0.0, 0.0),
            BlockType::Grass => Color::srgb(0.28, 0.65, 0.22),
            BlockType::Dirt => Color::srgb(0.48, 0.33, 0.21),
            BlockType::Stone => Color::srgb(0.55, 0.55, 0.55),
            BlockType::Wood => Color::srgb(0.42, 0.28, 0.14),
            BlockType::Leaves => Color::srgb(0.18, 0.52, 0.15),
            BlockType::Sand => Color::srgb(0.85, 0.80, 0.55),
            BlockType::Glass => Color::srgba(0.80, 0.90, 0.95, 0.35),
        }
    }

    /// Returns top face tint if different from side (e.g. Grass top).
    pub fn face_color(&self, normal: IVec3) -> Color {
        match self {
            BlockType::Grass => {
                if normal.y > 0 {
                    Color::srgb(0.32, 0.72, 0.24) // Brighter green on top
                } else if normal.y < 0 {
                    Color::srgb(0.48, 0.33, 0.21) // Dirt bottom
                } else {
                    Color::srgb(0.38, 0.50, 0.25) // Mixed side
                }
            }
            _ => self.base_color(),
        }
    }
}

#[derive(Copy, Clone, Debug, Default, PartialEq, Eq)]
pub struct Voxel {
    pub block: BlockType,
}

impl Voxel {
    pub const AIR: Self = Self {
        block: BlockType::Air,
    };

    #[inline]
    pub fn new(block: BlockType) -> Self {
        Self { block }
    }
}

