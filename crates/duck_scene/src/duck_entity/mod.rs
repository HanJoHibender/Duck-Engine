use std::sync::Arc;
use duck_math::{Transform};


#[repr(C)]
#[derive(Clone,Copy, Default)]
pub struct Entity{
    pub transform:Transform,
    pub id: u128,
}

impl Entity{

    pub fn new(transform:Transform) -> Self {
        Self{
            transform,
            id: duck_math::generate_uuid(),
        }
    }
}