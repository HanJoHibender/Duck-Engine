use bevy::prelude::*;
use duck_engine::input::DuckFlyCam;
use duck_engine::DuckEnginePlugin;

fn main() {
    App::new()
        .add_plugins(
            DefaultPlugins
                .set(WindowPlugin {
                    primary_window: Some(Window {
                        title: "Duck Engine - Bender Sandbox [Bevy 0.15]".to_string(),
                        resolution: (1280.0, 720.0).into(),
                        present_mode: bevy::window::PresentMode::AutoVsync,
                        ..default()
                    }),
                    ..default()
                })
                .set(ImagePlugin::default_nearest()),
        )
        .insert_resource(ClearColor(Color::srgb(0.68, 0.78, 0.90)))
        .add_plugins(DuckEnginePlugin {
            render_distance: 2,
            seed: 7777,
        })
        .add_systems(Startup, setup_camera)
        .run();
}

fn setup_camera(mut commands: Commands) {
    commands.spawn((
        Camera3d::default(),
        Transform::from_xyz(0.0, 20.0, 25.0).looking_at(Vec3::new(0.0, 5.0, 0.0), Vec3::Y),
        DuckFlyCam::default(),
        DistanceFog {
            color: Color::srgb(0.68, 0.78, 0.90),
            falloff: FogFalloff::Linear {
                start: 25.0,
                end: 65.0,
            },
            ..default()
        },
    ));
}
