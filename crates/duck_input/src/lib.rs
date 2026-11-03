pub mod controller;
pub mod interaction;
pub mod raycast;

pub use controller::{fly_cam_controller_system, DuckFlyCam};
pub use interaction::{
    voxel_interaction_system, voxel_selection_system, SelectedBlock, TargetBlockHit,
};
pub use raycast::{raycast_voxels, VoxelHit};

use bevy::prelude::*;

pub struct DuckInputPlugin;

impl Plugin for DuckInputPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<SelectedBlock>()
            .init_resource::<TargetBlockHit>()
            .add_systems(
                Update,
                (
                    fly_cam_controller_system,
                    voxel_selection_system,
                    voxel_interaction_system,
                ),
            );
    }
}
