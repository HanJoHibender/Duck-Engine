//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_SCENE_H
#define DUCKENGINE_SCENE_H

#include "Scene/Components/Component.h"
#include "Scene/Components/Transform.h"
#include "Graphics/Window.h"
#include "Core/Threads/Thread.h"

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

        // Calls OnUpdate on all SceneObjects in the scene
        void OnUpdate(float dt);
        // Calls OnFixedUpdates on all SceneObjects in the scene 60 times a second
        void OnFixedUpdate(float dt);

        bool IsEnabled = true;

        // TODO make private?
        Window& window;
        RenderStack renderstack;
        DuckEngine::Thread* scenethread;

        std::vector<Camera*> scenecameras{};
        std::vector<SceneObject*> sceneobjects{};
    };

} // DuckEngine

#endif //DUCKENGINE_SCENE_H
