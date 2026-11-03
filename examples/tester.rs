use duck_world::{BlockType, VoxelWorld};

fn main() {
    println!("Testing Duck Engine World & Voxel Generation...");
    let mut world = VoxelWorld::new(1337, 2);
    world.generate_chunk(bevy::math::IVec3::ZERO);

    let chunk = world.chunks.get(&bevy::math::IVec3::ZERO).expect("Chunk (0,0,0) should exist");
    println!("Chunk (0,0,0) generated with dirty = {}, is_empty = {}", chunk.dirty, chunk.is_empty);

    // Test block manipulation
    let test_pos = bevy::math::IVec3::new(5, 5, 5);
    world.set_voxel(test_pos, BlockType::Glass);
    assert_eq!(world.get_voxel(test_pos).block, BlockType::Glass);
    println!("Voxel set/get test at {:?} succeeded: Glass verified!", test_pos);

    // Test meshing
    let mesh = duck_render::generate_chunk_mesh(bevy::math::IVec3::ZERO, &world);
    assert!(mesh.is_some(), "Mesh should be generated for terrain chunk");
    println!("Mesh generated successfully with {} vertices!", mesh.unwrap().count_vertices());

    println!("All Duck Engine tests passed successfully!");
}
