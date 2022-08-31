use std::sync::Arc;
use duck_math::{Transform};
use crate::duck_component::Component;


pub struct Entity{
    pub transform:Transform,
    pub components:Arc<Component>,
    pub id: u128,
}

impl Entity{

    pub fn new(transform:Transform) -> Self {
        Self{
            transform,
            components:Arc::new(Component {}),
            id: duck_math::generate_uuid(),
        }
    }
}