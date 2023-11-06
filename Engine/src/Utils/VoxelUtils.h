//
// Created by VrikkaDev on 04/11/2023.
//

#ifndef DUCKEXAMPLE_VOXELUTILS_H
#define DUCKEXAMPLE_VOXELUTILS_H

#include "Graphics/Mesh.h"

namespace DuckEngine {

    class VoxelUtils {
    public:
        static void Voxelize(Mesh* mesh, double voxelsize);
    };

} // DuckEngine

#endif //DUCKEXAMPLE_VOXELUTILS_H
