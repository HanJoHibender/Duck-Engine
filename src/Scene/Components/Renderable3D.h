//
// Created by VrikkaDev on 16/10/2023.
//

#ifndef DUCKENGINE_RENDERABLE3D_H
#define DUCKENGINE_RENDERABLE3D_H

#include "Component.h"
#include "Graphics/Model.h"

namespace DuckEngine {


    class Renderable3D : public Component {
    public:
        Renderable3D();

        void OnAttached(SceneObject* sceneObject) override;

        // Defaults to basic cube
        std::shared_ptr<Model> model;
    };

    namespace Components{
        using DuckEngine::Renderable3D;
    } // Components

} // DuckEngine

#endif //DUCKENGINE_RENDERABLE3D_H
