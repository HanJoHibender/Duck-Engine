use bevy::pbr::{CascadeShadowConfigBuilder, DirectionalLightShadowMap};
use bevy::prelude::*;
use duck_input::DuckInputPlugin;
use duck_render::DuckRenderPlugin;
use duck_ui::DuckUiPlugin;
use duck_world::VoxelWorld;

pub struct DuckEnginePlugin {
    pub render_distance: i32,
    pub seed: u32,
}

impl Default for DuckEnginePlugin {
    fn default() -> Self {
        Self {
            render_distance: 3,
            seed: 42,
        }
    }
}

impl Plugin for DuckEnginePlugin {
    fn build(&self, app: &mut App) {
        let world = VoxelWorld::new(self.seed, self.render_distance);

        app.insert_resource(world)
            .insert_resource(DirectionalLightShadowMap { size: 2048 })
            .add_plugins((DuckRenderPlugin, DuckInputPlugin, DuckUiPlugin))
            .add_systems(Startup, (setup_world_terrain, setup_environment));
    }
}

/// Spawns the initial voxel terrain chunks.
fn setup_world_terrain(mut world: ResMut<VoxelWorld>) {
    let r = world.render_distance;
    info!("DuckEngine: Generating procedural terrain with radius {}...", r);

    for cx in -r..=r {
        for cz in -r..=r {
            for cy in -1..=1 {
                world.generate_chunk(IVec3::new(cx, cy, cz));
            }
        }
    }
    info!("DuckEngine: Generated {} chunks.", world.chunks.len());
}

/// Sets up sun, ambient lighting, and sky atmosphere.
fn setup_environment(mut commands: Commands) {
    // Ambient light
    commands.insert_resource(AmbientLight {
        color: Color::srgb(0.7, 0.75, 0.85),
        brightness: 400.0,
    });

    // Directional sunlight with shadows
    commands.spawn((
        DirectionalLight {
            color: Color::srgb(1.0, 0.95, 0.85),
            illuminance: 12_000.0,
            shadows_enabled: true,
            ..default()
        },
        Transform::from_xyz(40.0, 70.0, 30.0).looking_at(Vec3::ZERO, Vec3::Y),
        CascadeShadowConfigBuilder {
            first_cascade_far_bound: 15.0,
            maximum_distance: 120.0,
            ..default()
        }
        .build(),
    ));
}
