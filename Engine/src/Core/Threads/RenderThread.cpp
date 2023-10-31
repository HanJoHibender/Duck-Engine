//
// Created by VrikkaDev on 29/10/2023.
//

#include "RenderThread.h"

namespace DuckEngine {
    RenderThread::RenderThread(Window& window) : Thread("RenderThread"), m_Window(window){
    }

    void RenderThread::run() {
        while(m_Window.IsRunning){
            m_Window.SwapBuffers();
            m_Window.RenderBackground();

            // Loop through scenes of the window and render them
            for(const std::shared_ptr<Scene>& scene : m_Window.scenes){
                scene->Render();
            }

        }
        m_Window.Destroy();
    }
} // DuckEngine