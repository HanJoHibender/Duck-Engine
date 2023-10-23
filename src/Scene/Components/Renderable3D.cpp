//
// Created by VrikkaDev on 16/10/2023.
//

#include "Renderable3D.h"
#include "Scene/SceneObject.h"

namespace DuckEngine {
    Renderable3D::Renderable3D() {
        // Send unique pointer of THIS to renderstack.
        this->m_ParentObject->GetScene()->window.renderstack->AddRenderable3D(std::unique_ptr<Renderable3D> (this));
    }
} // DuckEngine