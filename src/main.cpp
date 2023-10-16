//
// Created by VrikkaDev on 26/09/2023.
//

#include "Engine.h"

using namespace DuckEngine;

int main(){

    Window window = Window(640, 480, "Bread is tasty");

    Scene scene = Scene();
    SceneObject obj = scene.CreateObject();
    auto camera = Camera(obj);

    camera.AddComponent<Transform>();

    DuckEngine::Components::Transform a = DuckEngine::Transform();

    return 0;
}