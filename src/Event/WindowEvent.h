//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_WINDOWEVENT_H
#define DUCKENGINE_WINDOWEVENT_H

#include "Event.h"

namespace DuckEngine {

    class WindowEvent : Event{
    public:
        WindowEvent() {
            EventDispatcher::AddReceiver(this);
        }

        WindowEvent(GLFWwindow* window, int width, int height) {
        }

        void HandleEvent(Event* event) override {
            if (auto* windowEvent = dynamic_cast<WindowEvent*>(event)) {
                OnWindowResize(nullptr, 800, 600);
            }
        }
    protected:
        virtual void OnWindowResize(GLFWwindow* window, int width, int height) {}
    };

} // DuckEngine

#endif //DUCKENGINE_WINDOWEVENT_H
