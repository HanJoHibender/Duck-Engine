//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_ENGINE_H
#define DUCKENGINE_ENGINE_H

#include "pch.hxx"

#include "Graphics/Window.h"

#include "Event/WindowEvent.h"
#include "Event/Event.h"

#include "Scene/Scene.h"
#include "Scene/SceneObject.h"
#include "Scene/Objects/Camera.h"

namespace DuckEngine {

    class Engine {
    public:
        void Setup();
    };

} // DuckEngine

#endif //DUCKENGINE_ENGINE_H
