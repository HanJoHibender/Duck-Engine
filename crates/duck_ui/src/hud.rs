use bevy::prelude::*;
use duck_input::{DuckFlyCam, SelectedBlock, TargetBlockHit};
use duck_world::VoxelWorld;

#[derive(Component)]
pub struct FpsText;

#[derive(Component)]
pub struct PositionText;

#[derive(Component)]
pub struct BlockSelectionText;

#[derive(Component)]
pub struct TargetBlockText;

#[derive(Resource, Default)]
struct FpsTracker {
    frame_count: u32,
    timer: f32,
    current_fps: f32,
}

pub struct DuckUiPlugin;

impl Plugin for DuckUiPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<FpsTracker>()
            .add_systems(Startup, setup_hud)
            .add_systems(Update, (update_fps, update_hud_text));
    }
}

fn setup_hud(mut commands: Commands) {
    // Crosshair in center
    commands
        .spawn(Node {
            position_type: PositionType::Absolute,
            width: Val::Percent(100.0),
            height: Val::Percent(100.0),
            justify_content: JustifyContent::Center,
            align_items: AlignItems::Center,
            ..default()
        })
        .with_child((
            Text::new("+"),
            TextFont {
                font_size: 24.0,
                ..default()
            },
            TextColor(Color::srgba(1.0, 1.0, 1.0, 0.7)),
        ));

    // Top-left diagnostic HUD container
    commands
        .spawn((
            Node {
                position_type: PositionType::Absolute,
                top: Val::Px(12.0),
                left: Val::Px(12.0),
                flex_direction: FlexDirection::Column,
                padding: UiRect::all(Val::Px(10.0)),
                row_gap: Val::Px(4.0),
                ..default()
            },
            BackgroundColor(Color::srgba(0.05, 0.05, 0.08, 0.75)),
            BorderRadius::all(Val::Px(6.0)),
        ))
        .with_children(|parent| {
            // Title
            parent.spawn((
                Text::new("DUCK ENGINE [Bevy 0.15]"),
                TextFont {
                    font_size: 16.0,
                    ..default()
                },
                TextColor(Color::srgb(1.0, 0.85, 0.2)),
            ));

            // FPS
            parent.spawn((
                Text::new("FPS: --"),
                TextFont {
                    font_size: 13.0,
                    ..default()
                },
                TextColor(Color::srgb(0.4, 1.0, 0.4)),
                FpsText,
            ));

            // Position & Chunk info
            parent.spawn((
                Text::new("XYZ: 0.0, 0.0, 0.0 | Chunks: 0"),
                TextFont {
                    font_size: 13.0,
                    ..default()
                },
                TextColor(Color::srgb(0.85, 0.85, 0.85)),
                PositionText,
            ));

            // Active placement block
            parent.spawn((
                Text::new("Placing: Stone [Keys 1-7]"),
                TextFont {
                    font_size: 13.0,
                    ..default()
                },
                TextColor(Color::srgb(0.9, 0.7, 0.4)),
                BlockSelectionText,
            ));

            // Target block
            parent.spawn((
                Text::new("Target: Looking at Air"),
                TextFont {
                    font_size: 13.0,
                    ..default()
                },
                TextColor(Color::srgb(0.7, 0.8, 1.0)),
                TargetBlockText,
            ));

            // Controls legend
            parent.spawn((
                Text::new("WASD: Move | Space/C: Up/Down | Shift: Boost\nLeft-Click: Break | Right-Click: Place | Esc: Toggle Mouse"),
                TextFont {
                    font_size: 11.0,
                    ..default()
                },
                TextColor(Color::srgb(0.65, 0.65, 0.65)),
            ));
        });
}

fn update_fps(time: Res<Time>, mut tracker: ResMut<FpsTracker>) {
    tracker.frame_count += 1;
    tracker.timer += time.delta_secs();

    if tracker.timer >= 0.5 {
        tracker.current_fps = tracker.frame_count as f32 / tracker.timer;
        tracker.frame_count = 0;
        tracker.timer = 0.0;
    }
}

fn update_hud_text(
    tracker: Res<FpsTracker>,
    world: Res<VoxelWorld>,
    selected: Res<SelectedBlock>,
    target_hit: Res<TargetBlockHit>,
    cam_query: Query<(&Transform, &DuckFlyCam)>,
    mut fps_query: Query<&mut Text, (With<FpsText>, Without<PositionText>, Without<BlockSelectionText>, Without<TargetBlockText>)>,
    mut pos_query: Query<&mut Text, (With<PositionText>, Without<FpsText>, Without<BlockSelectionText>, Without<TargetBlockText>)>,
    mut block_query: Query<&mut Text, (With<BlockSelectionText>, Without<FpsText>, Without<PositionText>, Without<TargetBlockText>)>,
    mut target_query: Query<&mut Text, (With<TargetBlockText>, Without<FpsText>, Without<PositionText>, Without<BlockSelectionText>)>,
) {
    for mut text in fps_query.iter_mut() {
        **text = format!("FPS: {:.0} ({:.2} ms)", tracker.current_fps, 1000.0 / tracker.current_fps.max(1.0));
    }

    if let Ok((cam_transform, _)) = cam_query.get_single() {
        let p = cam_transform.translation;
        for mut text in pos_query.iter_mut() {
            **text = format!(
                "XYZ: {:.1}, {:.1}, {:.1} | Chunks: {}",
                p.x, p.y, p.z, world.chunks.len()
            );
        }
    }

    for mut text in block_query.iter_mut() {
        **text = format!("Placing: {:?} [Keys 1-7]", selected.0);
    }

    for mut text in target_query.iter_mut() {
        if let Some(hit) = &target_hit.0 {
            **text = format!(
                "Target: {:?} at ({}, {}, {}) dist: {:.1}",
                hit.block_type, hit.block_pos.x, hit.block_pos.y, hit.block_pos.z, hit.distance
            );
        } else {
            **text = "Target: None (air)".to_string();
        }
    }
}

