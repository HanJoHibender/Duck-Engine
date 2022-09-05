use std::any::Any;
use std::path::Component;
use duck_internal::duck_math::{InstanceOf, Transform, Vec4f};
use duck_internal::duck_scene::duck_component::Drawable::Drawable;
use duck_internal::duck_scene::duck_entity::Entity;
use duck_internal::duck_window::window::duck_window;
use duck_internal::duck_math;

fn main() {


    let ent = Entity::new(Transform::zero());

    let a = Drawable::new(ent, Vec4f::new(0_f32,0_f32,0_f32,0_f32));


    duck_window::init(&mut self::duck_window {
        title: "Hello",
        width: 1920,
        height: 1080,
    });
}
