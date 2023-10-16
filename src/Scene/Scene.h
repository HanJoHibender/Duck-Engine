//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_SCENE_H
#define DUCKENGINE_SCENE_H

#include "entt/entt.hpp"
#include "Scene/Components/Component.h"
#include "Scene/Components/Transform.h"

namespace DuckEngine {

    class SceneObject;

    class Scene {
    public:
        Scene();

        SceneObject CreateObject();
        void AddObject(SceneObject* sceneObject);
        void RemoveObject(SceneObject* sceneObject);

        // Updates all SceneObjects in the scene
        void OnUpdate(float dt);

        // TODO make private
        entt::registry objectRegistry;
    };

} // DuckEngine

#endif //DUCKENGINE_SCENE_H
