//
// Created by VrikkaDev on 26/09/2023.
//

#include "Scene.h"

#include "SceneObject.h"
#include "Scene/Objects/Camera.h"
#include "Core/Threads/SceneThread.h"

namespace DuckEngine {

    Scene::Scene(Window& window) : window(window){
    }

    std::shared_ptr<Scene> Scene::CreateScene(Window& window) {
        std::shared_ptr<Scene> r = std::make_shared<Scene>(window);
        window.scenes.push_back(r);
        r->scenethread = new SceneThread(*r);
        r->scenethread->Start();
        return r;
    }

    void Scene::AddObject(SceneObject* sceneObject) {
        sceneObject->SetScene(this);
        sceneobjects.push_back(sceneObject);
    }

    void Scene::RemoveObject(SceneObject* sceneObject) {
        sceneobjects.erase(std::find(sceneobjects.begin(), sceneobjects.end(), sceneObject));
    }

    void Scene::OnUpdate(float dt) {
        for(auto obj : sceneobjects){
            obj->OnUpdate(dt);
        }
    }

    void Scene::OnFixedUpdate(float dt) {
        for(auto obj : sceneobjects){
            obj->OnFixedUpdate(dt);
        }
    }

    SceneObject Scene::CreateObject() {
        SceneObject obj = SceneObject{this};

        obj.OnStart();
        // Give object Transform component.
        auto tc = obj.AddComponent<Transform>();

        sceneobjects.push_back(&obj);

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