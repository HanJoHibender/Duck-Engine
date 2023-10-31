//
// Created by VrikkaDev on 26/09/2023.
//

#include "Engine.h"
#include "Core/Threads/RenderThread.h"

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
                    RenderThread thread = RenderThread(*wind);
                    //TODO: run() so it doesnt make new thread but uses this current thread. Not good.
                    thread.run();
                }
            }
            if(windows.empty()){
                break;
            }
        }
    }
} // DuckEngine