use uuid;
use uuid::Uuid;


#[repr(C)]
#[derive(Clone, PartialEq, Debug, Copy, Default)]
pub struct Vec3f{
    pub x:f32,
    pub y:f32,
    pub z:f32,
}

impl Vec3f{
    pub const fn new(x:f32,y:f32,z:f32) -> Self{
        Self{x,y,z}
    }
}

impl Vec3f{
    fn add(self, other:Vec3f) -> Vec3f{
        Vec3f{
            x:self.x + other.x,
            y:self.y + other.y,
            z:self.z + other.z,
        }
    }
}

#[repr(C)]
#[derive(Clone, PartialEq, Debug, Copy, Default)]
pub struct Vec4f{
    pub x:f32,
    pub y:f32,
    pub z:f32,
    pub w:f32,
}

impl Vec4f{
    pub const fn new(x:f32,y:f32,z:f32,w:f32) -> Self{
        Self{x,y,z,w}
    }
}

impl Vec4f{
    fn add(self, other:Vec4f) -> Vec4f{
        Vec4f{
            x:self.x + other.x,
            y:self.y + other.y,
            z:self.z + other.z,
            w:self.w + other.w,
        }
    }
}


#[repr(C)]
#[derive(Clone, Debug, Copy, Default)]
pub struct Transform{
    pub position:Vec3f,
    pub rotation:Vec3f,
    pub scale:Vec3f,
}
impl Transform{
    pub const fn new(position:Vec3f, rotation:Vec3f, scale:Vec3f) -> Self{
        Self{
            position,
            rotation,
            scale
        }
    }
    pub const fn zero() -> Self{
        Self{
            position:Vec3f::new(0_f32, 0_f32, 0_f32),
            rotation:Vec3f::new(0_f32,0_f32,0_f32),
            scale:Vec3f::new(1_f32,1_f32,1_f32),
        }
    }
}

pub fn generate_uuid() -> u128 {
    Uuid::new_v4().as_u128()
}

use std::any::{Any, TypeId};

pub trait InstanceOf
    where
        Self: Any,
{
    fn instance_of<U: ?Sized + Any>(&self) -> bool {
        TypeId::of::<Self>() == TypeId::of::<U>()
    }
}

impl<T: ?Sized + Any> InstanceOf for T {}