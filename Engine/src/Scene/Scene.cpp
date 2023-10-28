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

        obj.OnStart();
        // Give object Transform component.
        auto tc = obj.AddComponent<Transform>();
        return obj;
    }

    void Scene::Render() {

        for(auto cam : scenecameras){
            // Doesnt render if camera isnt enabled
            if(!cam->isEnabled){
                continue;
            }
            // Update viewmatrices
            cam->UpdateView();

            // Renders renderstack objects using camera
            renderstack.Render(cam);
        }
    }

    Camera& Scene::CreateCamera() {
        /*
         * Doesnt use CreateObject because it adds transform component
         * before adding the object to camera. so it messes things up.
         *
         * Probably should fix it somehow instead of this :D
         */
        auto* camera = new Camera();
        AddObject(camera);

        camera->OnStart();

        camera->AddComponent<Transform>();

        this->scenecameras.push_back(camera);

        return *camera;
    }
} // DuckEngine