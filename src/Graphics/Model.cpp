//
// Created by VrikkaDev on 24/10/2023.
//

#include "Model.h"

namespace DuckEngine {
    Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
        m_Mesh = mesh;
        m_Material = material;
    }
} // DuckEngine