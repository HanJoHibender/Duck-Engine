//
// Created by VrikkaDev on 16/10/2023.
//

#include "Renderable3D.h"
#include "Scene/SceneObject.h"

namespace DuckEngine {
    Renderable3D::Renderable3D()
            : model(Model(Mesh::CUBE(), std::make_shared<Material>())){
        // Send pointer of THIS to renderstack.
        this->m_ParentObject->GetScene()->renderstack.AddRenderable3D(this);
    }
} // DuckEngine