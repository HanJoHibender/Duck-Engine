use crate::controller::DuckFlyCam;
use crate::raycast::{raycast_voxels, VoxelHit};
use bevy::prelude::*;
use duck_world::{BlockType, VoxelWorld};

#[derive(Resource)]
pub struct SelectedBlock(pub BlockType);

impl Default for SelectedBlock {
    fn default() -> Self {
        Self(BlockType::Stone)
    }
}

#[derive(Resource, Default)]
pub struct TargetBlockHit(pub Option<VoxelHit>);

pub fn voxel_selection_system(
    keyboard: Res<ButtonInput<KeyCode>>,
    mut selected: ResMut<SelectedBlock>,
) {
    if keyboard.just_pressed(KeyCode::Digit1) {
        selected.0 = BlockType::Grass;
    } else if keyboard.just_pressed(KeyCode::Digit2) {
        selected.0 = BlockType::Dirt;
    } else if keyboard.just_pressed(KeyCode::Digit3) {
        selected.0 = BlockType::Stone;
    } else if keyboard.just_pressed(KeyCode::Digit4) {
        selected.0 = BlockType::Wood;
    } else if keyboard.just_pressed(KeyCode::Digit5) {
        selected.0 = BlockType::Leaves;
    } else if keyboard.just_pressed(KeyCode::Digit6) {
        selected.0 = BlockType::Sand;
    } else if keyboard.just_pressed(KeyCode::Digit7) {
        selected.0 = BlockType::Glass;
    }
}

pub fn voxel_interaction_system(
    mouse_button: Res<ButtonInput<MouseButton>>,
    mut world: ResMut<VoxelWorld>,
    selected: Res<SelectedBlock>,
    mut target_hit: ResMut<TargetBlockHit>,
    mut gizmos: Gizmos,
    query: Query<(&Transform, &DuckFlyCam)>,
) {
    let Ok((cam_transform, cam)) = query.get_single() else {
        return;
    };

    if !cam.cursor_locked {
        target_hit.0 = None;
        return;
    }

    let origin = cam_transform.translation;
    let forward = cam_transform.forward().as_vec3();
    let hit_opt = raycast_voxels(&world, origin, forward, 8.0);
    target_hit.0 = hit_opt;

    if let Some(hit) = hit_opt {
        // Draw target bounding box outline
        let center = Vec3::new(
            hit.block_pos.x as f32 + 0.5,
            hit.block_pos.y as f32 + 0.5,
            hit.block_pos.z as f32 + 0.5,
        );
        gizmos.cuboid(
            Transform::from_translation(center).with_scale(Vec3::splat(1.002)),
            Color::srgba(1.0, 1.0, 1.0, 0.8),
        );

        // Break block on Left Click
        if mouse_button.just_pressed(MouseButton::Left) {
            world.set_voxel(hit.block_pos, BlockType::Air);
        }

        // Place block on Right Click
        if mouse_button.just_pressed(MouseButton::Right) {
            let place_pos = hit.block_pos + hit.normal;
            // Prevent placing block inside player camera
            let player_pos = origin.floor().as_ivec3();
            if place_pos != player_pos {
                world.set_voxel(place_pos, selected.0);
            }
        }
    }
}

