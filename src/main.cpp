//
// Created by VrikkaDev on 26/09/2023.
//

#include "Engine.h"

using namespace DuckEngine;

int main(){

    Window window = Window(640, 480, "Bread is good");
    window.SetVsync(true);

    Scene scene = Scene(window);

    auto& camera = scene.CreateCamera();
    Transform* cameraTransform = ((Transform*)&camera.GetComponent<Transform>());
    cameraTransform->Position += cameraTransform->FORWARD() * 2.f;

    camera.GetComponents();
   // camera.AddComponent<Transform>();
    camera.GetComponents();

    SceneObject vobj = scene.CreateObject();
    vobj.AddComponent<Renderable3D>();

    vobj.GetComponents();

    while (window.IsRunning){
        window.SwapBuffers();

        scene.Render();

        scene.OnUpdate(0);

        if(window.keyboard->IsPressing(GLFW_KEY_RIGHT)){
            ((Transform*)&camera.GetComponent<Transform>())->Position ++;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_LEFT)){
            ((Transform*)&camera.GetComponent<Transform>())->Position --;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_UP)){
            ((Transform*)&camera.GetComponent<Transform>())->Position.x ++;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_DOWN)){
            ((Transform*)&camera.GetComponent<Transform>())->Position.x --;
        }

        if(window.keyboard->IsPressing(GLFW_KEY_D)){
            ((Transform*)&camera.GetComponent<Transform>())->Rotation ++;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_A)){
            ((Transform*)&camera.GetComponent<Transform>())->Rotation --;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_W)){
            ((Transform*)&camera.GetComponent<Transform>())->Rotation.x ++;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_S)){
            ((Transform*)&camera.GetComponent<Transform>())->Rotation.x --;
        }

    }

    window.Destroy();

    return 0;
}