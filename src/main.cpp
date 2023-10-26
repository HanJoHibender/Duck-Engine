//
// Created by VrikkaDev on 26/09/2023.
//

#include "Engine.h"

using namespace DuckEngine;

int main(){

    Window window = Window(640, 480, "Bread is tasty");
    window.SetVsync(true);

    Scene scene = Scene(window);

    SceneObject obj = scene.CreateObject();
    auto camera = Camera(obj);

    SceneObject vobj = scene.CreateObject();
    vobj.AddComponent<Renderable3D>();

    while (window.IsRunning){
        window.SwapBuffers();

        scene.Render();

        scene.OnUpdate(0);
    }

    window.Destroy();

    return 0;
}