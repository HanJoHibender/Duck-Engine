//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_SCENE_H
#define DUCKENGINE_SCENE_H

#include "entt/entt.hpp"
#include "Scene/Components/Component.h"
#include "Scene/Components/Transform.h"
#include "Graphics/Window.h"

namespace DuckEngine {

    class SceneObject;

    class Scene {
    public:
        explicit Scene(Window& window);

        SceneObject CreateObject();
        void AddObject(SceneObject* sceneObject);
        void RemoveObject(SceneObject* sceneObject);

        // Updates all SceneObjects in the scene
        void OnUpdate(float dt);

        // TODO make private
        entt::registry objectRegistry;
        Window& window;
    };

} // DuckEngine

#endif //DUCKENGINE_SCENE_H
