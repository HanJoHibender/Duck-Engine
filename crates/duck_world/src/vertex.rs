pub struct Matrix {
    pub matrix: Vec<i32>,
    pub width: i32,
    pub height: i32,
}

impl Matrix {
    pub fn new(matrix: Vec<i32>, width: i32, height: i32) -> Self {
        Self {
            matrix,
            width,
            height,
        }
    }
}

pub struct World {
    pub name: String,
    pub world: Matrix,
}

impl World {
    pub fn new(name: String, world: Matrix) -> Self {
        Self { name, world }
    }
}

pub fn world_gen() {
    let Matrix {
        matrix,
        width,
        height,
    };
}

fn generate_matrix() {}

fn generate_data() {}
