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
    class Camera;

    class Scene {
    public:
        explicit Scene(Window& window);

        // Creates sceneobject with Transform componnt
        SceneObject CreateObject();
        // Creates camera obect with Transform component
        Camera& CreateCamera();

        // TODO need to make this cleaner..

        // If used Scene::CreateObject this is not necessary
        void AddObject(SceneObject* sceneObject);
        void RemoveObject(SceneObject* sceneObject);

        void Render();

        // Updates all SceneObjects in the scene
        void OnUpdate(float dt);

        // TODO make private?
        entt::registry objectRegistry;
        Window& window;
        RenderStack renderstack;

        // TODO better camera handling to scene
        std::vector<Camera*> scenecameras{};
    };

} // DuckEngine

#endif //DUCKENGINE_SCENE_H
