//
// Created by VrikkaDev on 26/09/2023.
//

#include "Engine.h"
#include "Components/FpsComponent.h"
#include "Components/CameraMovementComponent.h"

using namespace DuckEngine;

int main(){

    Engine::Setup();

    Window window = Window(640, 480, "Bread is good");
    window.SetVsync(true);

    std::shared_ptr<Scene> scene = Scene::CreateScene(window);

    auto& camera = scene->CreateCamera();
    Transform* cameraTransform = ((Transform*)camera.GetComponent<Transform>());
    cameraTransform->Position += cameraTransform->FORWARD() * 0.1f;

    camera.AddComponent<CameraMovementComponent>();

    SceneObject vobj = scene->CreateObject();
    vobj.AddComponent<Renderable3D>();

    (FpsComponent*)vobj.AddComponent<FpsComponent>();

    Engine::Start();

    return 0;
}

