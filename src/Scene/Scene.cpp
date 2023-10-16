//
// Created by VrikkaDev on 26/09/2023.
//

#include "Scene.h"

#include "SceneObject.h"

namespace DuckEngine {
    Scene::Scene(Window& window) : window(window) {
    }

    void Scene::AddObject(SceneObject* sceneObject) {
        sceneObject->setupWithScene(this, objectRegistry.create());
    }

    void Scene::RemoveObject(SceneObject* sceneObject) {
        objectRegistry.destroy(sceneObject->operator entt::entity());
    }

    void Scene::OnUpdate(float dt) {

    }

    SceneObject Scene::CreateObject() {
        SceneObject obj = SceneObject{objectRegistry.create(), this};
        // Give object Transform component.
        auto tc = obj.AddComponent<Transform>();
        return obj;
    }
} // DuckEngine