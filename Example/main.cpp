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
    cameraTransform->Position += cameraTransform->FORWARD() * 0.1f;

    SceneObject vobj = scene.CreateObject();
    vobj.AddComponent<Renderable3D>();

    float speed = 0.001f;
    float yaw = 0.f, pitch = 0.f;


    // TODO make it so things like window swapbiffers or scene onupdate arent here.
    while (window.IsRunning){
        window.SwapBuffers();
        window.RenderBackground();

        scene.Render();

        scene.OnUpdate(0);

        if(window.keyboard->IsPressing(GLFW_KEY_RIGHT)){
            cameraTransform->Position += cameraTransform->RIGHT() * speed;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_LEFT)){
            cameraTransform->Position -= cameraTransform->RIGHT() * speed;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_UP)){
            cameraTransform->Position -= cameraTransform->FORWARD() * speed;
        }
        if(window.keyboard->IsPressing(GLFW_KEY_DOWN)){
            cameraTransform->Position += cameraTransform->FORWARD() * speed;
        }


        if(window.keyboard->IsPressing(GLFW_KEY_W)){
            pitch--;
            cameraTransform->Rotation.x = pitch;
        }else if(window.keyboard->IsPressing(GLFW_KEY_S)){
            pitch++;
            cameraTransform->Rotation.x = pitch;
        }

        if(window.keyboard->IsPressing(GLFW_KEY_A)){
            yaw--;
            cameraTransform->Rotation.y = yaw;
        }else if(window.keyboard->IsPressing(GLFW_KEY_D)){
            yaw++;
            cameraTransform->Rotation.y = yaw;
        }

    }

    window.Destroy();

    return 0;
}