//
// Created by VrikkaDev on 29/10/2023.
//

#ifndef DUCKEXAMPLE_RENDERTHREAD_H
#define DUCKEXAMPLE_RENDERTHREAD_H

#include "Thread.h"
#include "Graphics/Window.h"
#include "Scene/Scene.h"

namespace DuckEngine {

    // TODO: the Thread functionality isnt even used currently so rendering is on main thread
    class RenderThread : public Thread {
    public:
        explicit RenderThread(Window& window);

        void run() override;
    private:
        Window& m_Window;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_RENDERTHREAD_H
