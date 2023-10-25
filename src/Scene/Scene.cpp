//
// Created by VrikkaDev on 26/09/2023.
//

#include "Scene.h"

#include "SceneObject.h"
#include "Scene/Objects/Camera.h"

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
        auto view = objectRegistry.view<SceneObject>();
        for(auto obj : view){
            auto c = view.get<SceneObject>(obj);
            c.OnUpdate(dt);
        }
    }

    SceneObject Scene::CreateObject() {
        SceneObject obj = SceneObject{objectRegistry.create(), this};
        // Give object Transform component.
        auto tc = obj.AddComponent<Transform>();
        return obj;
    }

    void Scene::Render() {
        auto view = objectRegistry.view<Camera>();
        for(auto obj : view){
            auto c = view.get<Camera>(obj);

            // Doesnt render if camera isnt enabled
            if(!c.isEnabled){
                continue;
            }
            // Update viewmatrices
            c.UpdateView();

            // Renders renderstack objects using camera
            renderstack.Render(&c);
        }
    }
} // DuckEngine