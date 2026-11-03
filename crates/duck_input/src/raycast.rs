use bevy::prelude::*;
use duck_world::{BlockType, VoxelWorld};

#[derive(Debug, Clone, Copy)]
pub struct VoxelHit {
    pub block_pos: IVec3,
    pub normal: IVec3,
    pub block_type: BlockType,
    pub distance: f32,
}

/// Traverse 3D voxel grid along a ray using Amanatides-Woo Fast Voxel Traversal (DDA).
pub fn raycast_voxels(
    world: &VoxelWorld,
    origin: Vec3,
    direction: Vec3,
    max_distance: f32,
) -> Option<VoxelHit> {
    let dir = direction.normalize();

    let mut current_voxel = IVec3::new(
        origin.x.floor() as i32,
        origin.y.floor() as i32,
        origin.z.floor() as i32,
    );

    let step_x = if dir.x > 0.0 { 1 } else { -1 };
    let step_y = if dir.y > 0.0 { 1 } else { -1 };
    let step_z = if dir.z > 0.0 { 1 } else { -1 };

    let t_delta_x = if dir.x != 0.0 { (1.0 / dir.x).abs() } else { f32::MAX };
    let t_delta_y = if dir.y != 0.0 { (1.0 / dir.y).abs() } else { f32::MAX };
    let t_delta_z = if dir.z != 0.0 { (1.0 / dir.z).abs() } else { f32::MAX };

    let mut t_max_x = if dir.x > 0.0 {
        ((current_voxel.x + 1) as f32 - origin.x) * t_delta_x
    } else if dir.x < 0.0 {
        (origin.x - current_voxel.x as f32) * t_delta_x
    } else {
        f32::MAX
    };

    let mut t_max_y = if dir.y > 0.0 {
        ((current_voxel.y + 1) as f32 - origin.y) * t_delta_y
    } else if dir.y < 0.0 {
        (origin.y - current_voxel.y as f32) * t_delta_y
    } else {
        f32::MAX
    };

    let mut t_max_z = if dir.z > 0.0 {
        ((current_voxel.z + 1) as f32 - origin.z) * t_delta_z
    } else if dir.z < 0.0 {
        (origin.z - current_voxel.z as f32) * t_delta_z
    } else {
        f32::MAX
    };

    let mut normal = IVec3::ZERO;
    let mut total_distance = 0.0;

    while total_distance <= max_distance {
        let voxel = world.get_voxel(current_voxel);
        if !voxel.block.is_air() {
            return Some(VoxelHit {
                block_pos: current_voxel,
                normal,
                block_type: voxel.block,
                distance: total_distance,
            });
        }

        if t_max_x < t_max_y {
            if t_max_x < t_max_z {
                total_distance = t_max_x;
                t_max_x += t_delta_x;
                current_voxel.x += step_x;
                normal = IVec3::new(-step_x, 0, 0);
            } else {
                total_distance = t_max_z;
                t_max_z += t_delta_z;
                current_voxel.z += step_z;
                normal = IVec3::new(0, 0, -step_z);
            }
        } else if t_max_y < t_max_z {
            total_distance = t_max_y;
            t_max_y += t_delta_y;
            current_voxel.y += step_y;
            normal = IVec3::new(0, -step_y, 0);
        } else {
            total_distance = t_max_z;
            t_max_z += t_delta_z;
            current_voxel.z += step_z;
            normal = IVec3::new(0, 0, -step_z);
        }
    }

    None
}

