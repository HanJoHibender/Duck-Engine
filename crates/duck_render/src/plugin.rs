use crate::mesher::generate_chunk_mesh;
use bevy::prelude::*;
use duck_world::VoxelWorld;
use std::collections::HashMap;

#[derive(Component)]
pub struct ChunkMeshEntity {
    pub chunk_pos: IVec3,
}

#[derive(Resource, Default)]
pub struct ChunkEntities {
    pub map: HashMap<IVec3, Entity>,
}

#[derive(Resource)]
pub struct VoxelMaterialHandle {
    pub handle: Handle<StandardMaterial>,
}

pub struct DuckRenderPlugin;

impl Plugin for DuckRenderPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<ChunkEntities>()
            .add_systems(Startup, setup_voxel_materials)
            .add_systems(Update, update_chunk_meshes);
    }
}

fn setup_voxel_materials(
    mut commands: Commands,
    mut materials: ResMut<Assets<StandardMaterial>>,
) {
    let material = materials.add(StandardMaterial {
        base_color: Color::WHITE,
        perceptual_roughness: 0.85,
        metallic: 0.05,
        reflectance: 0.2,
        ..default()
    });

    commands.insert_resource(VoxelMaterialHandle { handle: material });
}

fn update_chunk_meshes(
    mut commands: Commands,
    mut world: ResMut<VoxelWorld>,
    mut chunk_entities: ResMut<ChunkEntities>,
    mut meshes: ResMut<Assets<Mesh>>,
    mat_res: Option<Res<VoxelMaterialHandle>>,
) {
    let Some(mat_res) = mat_res else {
        return;
    };

    // Collect dirty chunk positions to avoid borrowing conflict
    let dirty_keys: Vec<IVec3> = world
        .chunks
        .iter()
        .filter(|(_, c)| c.dirty)
        .map(|(pos, _)| *pos)
        .collect();

    if dirty_keys.is_empty() {
        return;
    }

    // Clear dirty flags first
    for pos in &dirty_keys {
        if let Some(c) = world.chunks.get_mut(pos) {
            c.dirty = false;
        }
    }

    for pos in dirty_keys {
        let (mesh_opt, world_origin) = {
            let Some(chunk) = world.chunks.get(&pos) else {
                continue;
            };
            let origin = chunk.world_origin();
            let m = generate_chunk_mesh(pos, &world);
            (m, origin)
        };

        let existing_entity = chunk_entities.map.get(&pos).copied();

        match (mesh_opt, existing_entity) {
            (Some(mesh), Some(entity)) => {
                // Update existing mesh
                commands.entity(entity).insert(Mesh3d(meshes.add(mesh)));
            }
            (Some(mesh), None) => {
                // Spawn new chunk entity
                let mesh_handle = meshes.add(mesh);
                let entity = commands
                    .spawn((
                        Mesh3d(mesh_handle),
                        MeshMaterial3d(mat_res.handle.clone()),
                        Transform::from_translation(world_origin),
                        ChunkMeshEntity { chunk_pos: pos },
                    ))
                    .id();
                chunk_entities.map.insert(pos, entity);
            }
            (None, Some(entity)) => {
                // Chunk became empty, despawn mesh
                commands.entity(entity).despawn();
                chunk_entities.map.remove(&pos);
            }
            (None, None) => {}
        }
    }
}
