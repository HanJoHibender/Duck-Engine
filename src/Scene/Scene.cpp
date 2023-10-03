//
// Created by VrikkaDev on 26/09/2023.
//

#include "Scene.h"

#include "SceneObject.h"

namespace DuckEngine {
    Scene::Scene() {
    }

    void Scene::AddObject(SceneObject* sceneObject) {

    }

    void Scene::RemoveObject(SceneObject* sceneObject) {

    }

    void Scene::OnUpdate(float dt) {

    }

    SceneObject Scene::CreateObject() {
        SceneObject obj = SceneObject{static_cast<std::uint32_t>(objectRegistry.create()), this};



        return obj;
    }
} // DuckEngine