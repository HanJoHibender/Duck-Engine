//
// Created by VrikkaDev on 26/09/2023.
//

#include "Engine.h"
#include "Components/FpsComponent.h"

using namespace DuckEngine;

int main(){

    Window window = Window(640, 480, "Bread is good");
    window.SetVsync(true);


    Scene scene = Scene(window);

    auto& camera = scene.CreateCamera();
    Transform* cameraTransform = ((Transform*)camera.GetComponent<Transform>());
    cameraTransform->Position += cameraTransform->FORWARD() * 0.1f;

    SceneObject vobj = scene.CreateObject();
    vobj.AddComponent<Renderable3D>();

    FpsComponent* fpsComponent = (FpsComponent*)vobj.AddComponent<FpsComponent>();

    float speed = 0.001f;
    float yaw = 0.f, pitch = 0.f;

    // A test keybind that prints fps
    Keybind* fpsBind = new Keybind(GLFW_KEY_F, "fpsbind");
    window.keyboard->AddKeybind(fpsBind);


    // TODO make it so things like window swapbuffers or scene onupdate arent here.
    // TODO this shouldnt exist here.. use component/onupdate
    while (window.IsRunning){
        window.SwapBuffers();
        window.RenderBackground();

        scene.Render();

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

        if(fpsBind->IsPressed()){
            std::cout<<"Fps: "<< fpsComponent->GetFps()<< std::endl;
        }

    }

    window.Destroy();

    return 0;
}

