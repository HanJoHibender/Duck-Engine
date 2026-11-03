use bevy::input::mouse::MouseMotion;
use bevy::prelude::*;
use bevy::window::{CursorGrabMode, PrimaryWindow};

#[derive(Component)]
pub struct DuckFlyCam {
    pub move_speed: f32,
    pub boost_speed: f32,
    pub sensitivity: f32,
    pub yaw: f32,
    pub pitch: f32,
    pub cursor_locked: bool,
}

impl Default for DuckFlyCam {
    fn default() -> Self {
        Self {
            move_speed: 12.0,
            boost_speed: 32.0,
            sensitivity: 0.0025,
            yaw: -90.0f32.to_radians(),
            pitch: 0.0,
            cursor_locked: true,
        }
    }
}

pub fn fly_cam_controller_system(
    time: Res<Time>,
    keyboard: Res<ButtonInput<KeyCode>>,
    mouse_button: Res<ButtonInput<MouseButton>>,
    mut mouse_motion: EventReader<MouseMotion>,
    mut windows: Query<&mut Window, With<PrimaryWindow>>,
    mut query: Query<(&mut Transform, &mut DuckFlyCam)>,
) {
    let Ok(mut window) = windows.get_single_mut() else {
        return;
    };
    let Ok((mut transform, mut cam)) = query.get_single_mut() else {
        return;
    };

    // Toggle cursor grab on click or escape
    if mouse_button.just_pressed(MouseButton::Left) && !cam.cursor_locked {
        cam.cursor_locked = true;
        window.cursor_options.grab_mode = CursorGrabMode::Locked;
        window.cursor_options.visible = false;
    } else if keyboard.just_pressed(KeyCode::Escape) && cam.cursor_locked {
        cam.cursor_locked = false;
        window.cursor_options.grab_mode = CursorGrabMode::None;
        window.cursor_options.visible = true;
    }

    if !cam.cursor_locked {
        return;
    }

    // Mouse look
    let mut delta = Vec2::ZERO;
    for event in mouse_motion.read() {
        delta += event.delta;
    }

    if delta != Vec2::ZERO {
        cam.yaw -= delta.x * cam.sensitivity;
        cam.pitch -= delta.y * cam.sensitivity;

        let max_pitch = 89.0f32.to_radians();
        cam.pitch = cam.pitch.clamp(-max_pitch, max_pitch);

        let rotation = Quat::from_axis_angle(Vec3::Y, cam.yaw)
            * Quat::from_axis_angle(Vec3::X, cam.pitch);
        transform.rotation = rotation;
    }

    // Keyboard movement
    let speed = if keyboard.pressed(KeyCode::ControlLeft) || keyboard.pressed(KeyCode::ShiftLeft) {
        cam.boost_speed
    } else {
        cam.move_speed
    };

    let mut move_vec = Vec3::ZERO;
    let forward = transform.forward().as_vec3();
    let right = transform.right().as_vec3();
    let up = Vec3::Y;

    if keyboard.pressed(KeyCode::KeyW) {
        move_vec += forward;
    }
    if keyboard.pressed(KeyCode::KeyS) {
        move_vec -= forward;
    }
    if keyboard.pressed(KeyCode::KeyA) {
        move_vec -= right;
    }
    if keyboard.pressed(KeyCode::KeyD) {
        move_vec += right;
    }
    if keyboard.pressed(KeyCode::Space) {
        move_vec += up;
    }
    if keyboard.pressed(KeyCode::KeyC) {
        move_vec -= up;
    }

    if move_vec != Vec3::ZERO {
        transform.translation += move_vec.normalize() * speed * time.delta_secs();
    }
}

