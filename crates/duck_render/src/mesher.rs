use bevy::prelude::*;
use bevy::render::mesh::{Indices, Mesh, PrimitiveTopology};
use bevy::render::render_asset::RenderAssetUsages;
use duck_world::{Chunk, VoxelWorld, CHUNK_SIZE_I32};

struct FaceDefinition {
    normal: Vec3,
    int_normal: IVec3,
    // (u_dir, v_dir) in 3D for face corners
    u: IVec3,
    v: IVec3,
    corners: [Vec3; 4],
}

const FACES: [FaceDefinition; 6] = [
    // Top (+Y)
    FaceDefinition {
        normal: Vec3::Y,
        int_normal: IVec3::Y,
        u: IVec3::X,
        v: IVec3::Z,
        corners: [
            Vec3::new(0.0, 1.0, 0.0),
            Vec3::new(0.0, 1.0, 1.0),
            Vec3::new(1.0, 1.0, 1.0),
            Vec3::new(1.0, 1.0, 0.0),
        ],
    },
    // Bottom (-Y)
    FaceDefinition {
        normal: Vec3::NEG_Y,
        int_normal: IVec3::NEG_Y,
        u: IVec3::X,
        v: IVec3::NEG_Z,
        corners: [
            Vec3::new(0.0, 0.0, 1.0),
            Vec3::new(0.0, 0.0, 0.0),
            Vec3::new(1.0, 0.0, 0.0),
            Vec3::new(1.0, 0.0, 1.0),
        ],
    },
    // North (-Z)
    FaceDefinition {
        normal: Vec3::NEG_Z,
        int_normal: IVec3::NEG_Z,
        u: IVec3::NEG_X,
        v: IVec3::Y,
        corners: [
            Vec3::new(1.0, 0.0, 0.0),
            Vec3::new(0.0, 0.0, 0.0),
            Vec3::new(0.0, 1.0, 0.0),
            Vec3::new(1.0, 1.0, 0.0),
        ],
    },
    // South (+Z)
    FaceDefinition {
        normal: Vec3::Z,
        int_normal: IVec3::Z,
        u: IVec3::X,
        v: IVec3::Y,
        corners: [
            Vec3::new(0.0, 0.0, 1.0),
            Vec3::new(1.0, 0.0, 1.0),
            Vec3::new(1.0, 1.0, 1.0),
            Vec3::new(0.0, 1.0, 1.0),
        ],
    },
    // West (-X)
    FaceDefinition {
        normal: Vec3::NEG_X,
        int_normal: IVec3::NEG_X,
        u: IVec3::Z,
        v: IVec3::Y,
        corners: [
            Vec3::new(0.0, 0.0, 0.0),
            Vec3::new(0.0, 0.0, 1.0),
            Vec3::new(0.0, 1.0, 1.0),
            Vec3::new(0.0, 1.0, 0.0),
        ],
    },
    // East (+X)
    FaceDefinition {
        normal: Vec3::X,
        int_normal: IVec3::X,
        u: IVec3::NEG_Z,
        v: IVec3::Y,
        corners: [
            Vec3::new(1.0, 0.0, 1.0),
            Vec3::new(1.0, 0.0, 0.0),
            Vec3::new(1.0, 1.0, 0.0),
            Vec3::new(1.0, 1.0, 1.0),
        ],
    },
];

/// Helper to check if a block at local/neighbor coords is opaque.
fn is_solid_at(
    chunk: &Chunk,
    world: &VoxelWorld,
    pos: IVec3,
) -> bool {
    if pos.x >= 0
        && pos.x < CHUNK_SIZE_I32
        && pos.y >= 0
        && pos.y < CHUNK_SIZE_I32
        && pos.z >= 0
        && pos.z < CHUNK_SIZE_I32
    {
        chunk.get_voxel(pos.x, pos.y, pos.z).block.is_opaque()
    } else {
        let global_pos = IVec3::new(
            chunk.position.x * CHUNK_SIZE_I32 + pos.x,
            chunk.position.y * CHUNK_SIZE_I32 + pos.y,
            chunk.position.z * CHUNK_SIZE_I32 + pos.z,
        );
        world.get_voxel(global_pos).block.is_opaque()
    }
}

/// Calculate vertex ambient occlusion level (0 to 3).
fn vertex_ao(side1: bool, side2: bool, corner: bool) -> u8 {
    if side1 && side2 {
        0
    } else {
        3 - (side1 as u8 + side2 as u8 + corner as u8)
    }
}

fn ao_multiplier(ao: u8) -> f32 {
    match ao {
        0 => 0.45,
        1 => 0.65,
        2 => 0.85,
        _ => 1.0,
    }
}

pub fn generate_chunk_mesh(chunk_pos: IVec3, world: &VoxelWorld) -> Option<Mesh> {
    let chunk = world.chunks.get(&chunk_pos)?;
    if chunk.is_empty {
        return None;
    }

    let mut positions: Vec<[f32; 3]> = Vec::with_capacity(512);
    let mut normals: Vec<[f32; 3]> = Vec::with_capacity(512);
    let mut uvs: Vec<[f32; 2]> = Vec::with_capacity(512);
    let mut colors: Vec<[f32; 4]> = Vec::with_capacity(512);
    let mut indices: Vec<u32> = Vec::with_capacity(768);

    for x in 0..CHUNK_SIZE_I32 {
        for y in 0..CHUNK_SIZE_I32 {
            for z in 0..CHUNK_SIZE_I32 {
                let voxel = chunk.get_voxel(x, y, z);
                if voxel.block.is_air() {
                    continue;
                }

                let block_pos = IVec3::new(x, y, z);
                let block_base = Vec3::new(x as f32, y as f32, z as f32);

                for face in &FACES {
                    let neighbor_pos = block_pos + face.int_normal;
                    // Only generate face if neighbor is not opaque (visible surface)
                    if is_solid_at(chunk, world, neighbor_pos) {
                        continue;
                    }

                    let base_color = voxel.block.face_color(face.int_normal);
                    let [r, g, b, a] = base_color.to_srgba().to_f32_array();

                    // Calculate ambient occlusion for 4 corners of this face quad
                    let u = face.u;
                    let v = face.v;
                    let n = face.int_normal;

                    // Corner 0: (-u, -v)
                    let s1_0 = is_solid_at(chunk, world, block_pos + n - u);
                    let s2_0 = is_solid_at(chunk, world, block_pos + n - v);
                    let c_0 = is_solid_at(chunk, world, block_pos + n - u - v);
                    let ao0 = vertex_ao(s1_0, s2_0, c_0);

                    // Corner 1: (+u, -v)
                    let s1_1 = is_solid_at(chunk, world, block_pos + n + u);
                    let s2_1 = is_solid_at(chunk, world, block_pos + n - v);
                    let c_1 = is_solid_at(chunk, world, block_pos + n + u - v);
                    let ao1 = vertex_ao(s1_1, s2_1, c_1);

                    // Corner 2: (+u, +v)
                    let s1_2 = is_solid_at(chunk, world, block_pos + n + u);
                    let s2_2 = is_solid_at(chunk, world, block_pos + n + v);
                    let c_2 = is_solid_at(chunk, world, block_pos + n + u + v);
                    let ao2 = vertex_ao(s1_2, s2_2, c_2);

                    // Corner 3: (-u, +v)
                    let s1_3 = is_solid_at(chunk, world, block_pos + n - u);
                    let s2_3 = is_solid_at(chunk, world, block_pos + n + v);
                    let c_3 = is_solid_at(chunk, world, block_pos + n - u + v);
                    let ao3 = vertex_ao(s1_3, s2_3, c_3);

                    let start_idx = positions.len() as u32;

                    // Add 4 vertices
                    let corner_aos = [ao0, ao1, ao2, ao3];
                    for i in 0..4 {
                        let vert = block_base + face.corners[i];
                        positions.push([vert.x, vert.y, vert.z]);
                        normals.push([face.normal.x, face.normal.y, face.normal.z]);
                        let factor = ao_multiplier(corner_aos[i]);
                        colors.push([r * factor, g * factor, b * factor, a]);
                    }

                    uvs.push([0.0, 0.0]);
                    uvs.push([1.0, 0.0]);
                    uvs.push([1.0, 1.0]);
                    uvs.push([0.0, 1.0]);

                    // Quad triangulation flip check for consistent AO gradient
                    if ao0 + ao2 > ao1 + ao3 {
                        // Triangulate 0-1-2 and 0-2-3
                        indices.extend_from_slice(&[
                            start_idx,
                            start_idx + 1,
                            start_idx + 2,
                            start_idx,
                            start_idx + 2,
                            start_idx + 3,
                        ]);
                    } else {
                        // Triangulate 1-2-3 and 1-3-0
                        indices.extend_from_slice(&[
                            start_idx + 1,
                            start_idx + 2,
                            start_idx + 3,
                            start_idx + 1,
                            start_idx + 3,
                            start_idx,
                        ]);
                    }
                }
            }
        }
    }

    if positions.is_empty() {
        return None;
    }

    let mut mesh = Mesh::new(
        PrimitiveTopology::TriangleList,
        RenderAssetUsages::default(),
    );
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, positions);
    mesh.insert_attribute(Mesh::ATTRIBUTE_NORMAL, normals);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uvs);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, colors);
    mesh.insert_indices(Indices::U32(indices));

    Some(mesh)
}
