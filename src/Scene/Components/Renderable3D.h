//
// Created by VrikkaDev on 16/10/2023.
//

#ifndef DUCKENGINE_RENDERABLE3D_H
#define DUCKENGINE_RENDERABLE3D_H

#include "Component.h"
#include "Graphics/RenderStack.h"

namespace DuckEngine {


    class Renderable3D : public Component {
    public:
        Renderable3D();

        Color color = Color();
    };

    namespace Components{
        using DuckEngine::Renderable3D;
    } // Components

} // DuckEngine

#endif //DUCKENGINE_RENDERABLE3D_H
