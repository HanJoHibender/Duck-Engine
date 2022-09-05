use duck_math::Vec4f;
use crate::duck_entity::Entity;

#[derive(Clone,Copy, Default)]
pub struct Drawable{
    pub entity:Entity,
    pub enabled:bool,
    pub color:Vec4f,
}

impl Drawable{
    pub const fn new(entity:Entity, color:Vec4f) -> Self {
        Self{
            entity,
            enabled:true,
            color,
        }
    }
    fn render(){
    }
}