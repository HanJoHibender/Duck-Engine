use bevy::prelude::*;
use duck_engine::input::DuckFlyCam;
use duck_engine::DuckEnginePlugin;

fn main() {
    App::new()
        .add_plugins(
            DefaultPlugins
                .set(WindowPlugin {
                    primary_window: Some(Window {
                        title: "Duck Engine - Voxel Sandbox [Bevy 0.15]".to_string(),
                        resolution: (1280.0, 720.0).into(),
                        present_mode: bevy::window::PresentMode::AutoVsync,
                        ..default()
                    }),
                    ..default()
                })
                .set(ImagePlugin::default_nearest()),
        )
        // Clear color matching distance fog for atmospheric horizon
        .insert_resource(ClearColor(Color::srgb(0.68, 0.78, 0.90)))
        .add_plugins(DuckEnginePlugin {
            render_distance: 3,
            seed: 2026,
        })
        .add_systems(Startup, setup_camera)
        .run();
}

fn setup_camera(mut commands: Commands) {
    commands.spawn((
        Camera3d::default(),
        Transform::from_xyz(0.0, 24.0, 28.0).looking_at(Vec3::new(0.0, 6.0, 0.0), Vec3::Y),
        DuckFlyCam::default(),
        DistanceFog {
            color: Color::srgb(0.68, 0.78, 0.90),
            falloff: FogFalloff::Linear {
                start: 30.0,
                end: 75.0,
            },
            ..default()
        },
    ));
}

