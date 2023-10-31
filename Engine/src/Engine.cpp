//
// Created by VrikkaDev on 26/09/2023.
//

#include "Engine.h"

namespace DuckEngine {

    void Engine::Setup() {
        //todo
    }

    void Engine::Start() {


        std::vector<Window*> windows{};

        while(true){
            windows = Window::WindowInstances();

            for(auto wind : windows){
                while(wind->IsRunning){

                    wind->SwapBuffers();
                    wind->RenderBackground();

                    // Loop through scenes of the window and render them
                    for(const std::shared_ptr<Scene>& scene : wind->scenes){
                        scene->Render();
                    }

                    Executor::mainThreadExecutor.Execute();
                }
                wind->Destroy();
            }
            if(windows.empty()){
                break;
            }
        }
    }
} // DuckEngine