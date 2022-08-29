use matrix::prelude::*;

pub fn world_gen() {
    let mut sparse = Compressed::zero((2, 4));
    sparse.set((0, 0), 42.0);
    sparse.set((1, 3), 69.0);

    let dense = Conventional::from(&sparse);
    assert!(
        &*dense
            == &*matrix![
                42.0, 0.0, 0.0,  0.0;
                 0.0, 0.0, 0.0, 69.0;
            ]
    );
}
