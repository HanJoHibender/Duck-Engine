use crate::voxel::{BlockType, Voxel};
use bevy::prelude::*;

pub const CHUNK_SIZE: usize = 16;
pub const CHUNK_SIZE_I32: i32 = CHUNK_SIZE as i32;
pub const CHUNK_VOL: usize = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

#[derive(Component, Clone)]
pub struct Chunk {
    pub position: IVec3,
    pub voxels: Box<[Voxel; CHUNK_VOL]>,
    pub dirty: bool,
    pub is_empty: bool,
}

impl Default for Chunk {
    fn default() -> Self {
        Self {
            position: IVec3::ZERO,
            voxels: Box::new([Voxel::AIR; CHUNK_VOL]),
            dirty: true,
            is_empty: true,
        }
    }
}

impl Chunk {
    pub fn new(position: IVec3) -> Self {
        Self {
            position,
            voxels: Box::new([Voxel::AIR; CHUNK_VOL]),
            dirty: true,
            is_empty: true,
        }
    }

    #[inline]
    pub fn to_index(x: usize, y: usize, z: usize) -> usize {
        x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE
    }

    #[inline]
    pub fn get_voxel(&self, x: i32, y: i32, z: i32) -> Voxel {
        if x < 0
            || x >= CHUNK_SIZE_I32
            || y < 0
            || y >= CHUNK_SIZE_I32
            || z < 0
            || z >= CHUNK_SIZE_I32
        {
            return Voxel::AIR;
        }
        self.voxels[Self::to_index(x as usize, y as usize, z as usize)]
    }

    #[inline]
    pub fn set_voxel(&mut self, x: i32, y: i32, z: i32, block: BlockType) -> bool {
        if x < 0
            || x >= CHUNK_SIZE_I32
            || y < 0
            || y >= CHUNK_SIZE_I32
            || z < 0
            || z >= CHUNK_SIZE_I32
        {
            return false;
        }
        let idx = Self::to_index(x as usize, y as usize, z as usize);
        self.voxels[idx] = Voxel::new(block);
        self.dirty = true;
        if !block.is_air() {
            self.is_empty = false;
        }
        true
    }

    /// World coordinates of the chunk origin corner.
    #[inline]
    pub fn world_origin(&self) -> Vec3 {
        Vec3::new(
            (self.position.x * CHUNK_SIZE_I32) as f32,
            (self.position.y * CHUNK_SIZE_I32) as f32,
            (self.position.z * CHUNK_SIZE_I32) as f32,
        )
    }
}

