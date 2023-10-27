//
// Created by VrikkaDev on 16/10/2023.
//

#include "Renderable3D.h"
#include "Scene/SceneObject.h"
#include "Graphics/RenderStack.h"

namespace DuckEngine {
    Renderable3D::Renderable3D()
            : Component("Renderable3D"), model(std::make_shared<Model>(Mesh::CUBE(), std::make_shared<Material>())){
    }

    void Renderable3D::OnAttached(SceneObject* sceneObject) {
        m_ParentObject = sceneObject;

        // Send pointer of THIS to renderstack.
        m_ParentObject->GetScene()->renderstack.AddRenderable3D(this);
    }
} // DuckEngine