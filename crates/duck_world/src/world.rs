use crate::chunk::{Chunk, CHUNK_SIZE_I32};
use crate::noise::PerlinNoise;
use crate::voxel::{BlockType, Voxel};
use bevy::prelude::*;
use std::collections::HashMap;

#[derive(Resource)]
pub struct VoxelWorld {
    pub chunks: HashMap<IVec3, Chunk>,
    pub noise: PerlinNoise,
    pub sea_level: i32,
    pub render_distance: i32,
}

impl Default for VoxelWorld {
    fn default() -> Self {
        Self {
            chunks: HashMap::new(),
            noise: PerlinNoise::new(42),
            sea_level: 0,
            render_distance: 3,
        }
    }
}

impl VoxelWorld {
    pub fn new(seed: u32, render_distance: i32) -> Self {
        Self {
            chunks: HashMap::new(),
            noise: PerlinNoise::new(seed),
            sea_level: 0,
            render_distance,
        }
    }

    /// Convert world block coordinate into (ChunkPos, LocalBlockPos).
    #[inline]
    pub fn world_to_chunk_pos(pos: IVec3) -> (IVec3, IVec3) {
        let chunk_x = pos.x.div_euclid(CHUNK_SIZE_I32);
        let chunk_y = pos.y.div_euclid(CHUNK_SIZE_I32);
        let chunk_z = pos.z.div_euclid(CHUNK_SIZE_I32);

        let local_x = pos.x.rem_euclid(CHUNK_SIZE_I32);
        let local_y = pos.y.rem_euclid(CHUNK_SIZE_I32);
        let local_z = pos.z.rem_euclid(CHUNK_SIZE_I32);

        (
            IVec3::new(chunk_x, chunk_y, chunk_z),
            IVec3::new(local_x, local_y, local_z),
        )
    }

    /// Retrieve a voxel at a global block coordinate.
    pub fn get_voxel(&self, pos: IVec3) -> Voxel {
        let (chunk_pos, local) = Self::world_to_chunk_pos(pos);
        if let Some(chunk) = self.chunks.get(&chunk_pos) {
            chunk.get_voxel(local.x, local.y, local.z)
        } else {
            Voxel::AIR
        }
    }

    /// Modify a voxel at a global block coordinate, marking affected chunks dirty.
    pub fn set_voxel(&mut self, pos: IVec3, block: BlockType) -> bool {
        let (chunk_pos, local) = Self::world_to_chunk_pos(pos);
        let success = if let Some(chunk) = self.chunks.get_mut(&chunk_pos) {
            chunk.set_voxel(local.x, local.y, local.z, block)
        } else {
            false
        };

        if success {
            // Also mark adjacent chunks dirty if on chunk boundary (for boundary face culling)
            if local.x == 0 {
                if let Some(c) = self.chunks.get_mut(&(chunk_pos + IVec3::new(-1, 0, 0))) {
                    c.dirty = true;
                }
            } else if local.x == CHUNK_SIZE_I32 - 1 {
                if let Some(c) = self.chunks.get_mut(&(chunk_pos + IVec3::new(1, 0, 0))) {
                    c.dirty = true;
                }
            }
            if local.y == 0 {
                if let Some(c) = self.chunks.get_mut(&(chunk_pos + IVec3::new(0, -1, 0))) {
                    c.dirty = true;
                }
            } else if local.y == CHUNK_SIZE_I32 - 1 {
                if let Some(c) = self.chunks.get_mut(&(chunk_pos + IVec3::new(0, 1, 0))) {
                    c.dirty = true;
                }
            }
            if local.z == 0 {
                if let Some(c) = self.chunks.get_mut(&(chunk_pos + IVec3::new(0, 0, -1))) {
                    c.dirty = true;
                }
            } else if local.z == CHUNK_SIZE_I32 - 1 {
                if let Some(c) = self.chunks.get_mut(&(chunk_pos + IVec3::new(0, 0, 1))) {
                    c.dirty = true;
                }
            }
        }

        success
    }

    /// Procedurally generate terrain in a chunk.
    pub fn generate_chunk(&mut self, chunk_pos: IVec3) {
        if self.chunks.contains_key(&chunk_pos) {
            return;
        }

        let mut chunk = Chunk::new(chunk_pos);
        let origin = chunk.world_origin();

        for x in 0..CHUNK_SIZE_I32 {
            for z in 0..CHUNK_SIZE_I32 {
                let world_x = origin.x as i32 + x;
                let world_z = origin.z as i32 + z;

                // 2D fBM elevation
                let height_noise = self.noise.fbm2d(
                    world_x as f64 * 0.015,
                    world_z as f64 * 0.015,
                    4,
                    0.5,
                    2.0,
                );
                // Scale terrain height between -4 and 20
                let surface_height = ((height_noise + 1.0) * 0.5 * 24.0 - 4.0).round() as i32;

                for y in 0..CHUNK_SIZE_I32 {
                    let world_y = origin.y as i32 + y;

                    // 3D noise for small caves/pockets
                    let cave_noise = self.noise.noise3d(
                        world_x as f64 * 0.05,
                        world_y as f64 * 0.05,
                        world_z as f64 * 0.05,
                    );
                    let is_cave = cave_noise > 0.65 && world_y < surface_height - 2;

                    if world_y <= surface_height && !is_cave {
                        let block = if world_y == surface_height {
                            if world_y <= self.sea_level + 1 {
                                BlockType::Sand
                            } else {
                                BlockType::Grass
                            }
                        } else if world_y >= surface_height - 3 {
                            if world_y <= self.sea_level + 1 {
                                BlockType::Sand
                            } else {
                                BlockType::Dirt
                            }
                        } else {
                            BlockType::Stone
                        };
                        chunk.set_voxel(x, y, z, block);
                    }
                }
            }
        }

        self.chunks.insert(chunk_pos, chunk);
    }
}
