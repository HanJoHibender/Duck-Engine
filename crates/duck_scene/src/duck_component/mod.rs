use duck_math::Transform;
use crate::duck_entity::Entity;

pub mod Drawable;

#[derive(Clone, Default)]
pub struct Components{
    drawables:Vec<Drawable::Drawable>,
}