//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_WINDOWEVENT_H
#define DUCKENGINE_WINDOWEVENT_H

#include "Event.h"

namespace DuckEngine {

    class WindowEvent : public Event{
    public:
        WindowEvent() {
            m_Window = nullptr;
            m_Width = 800;
            m_Height = 600;
        }

        WindowEvent(GLFWwindow* window, int width, int height) {
            m_Window = window;
            m_Width = width;
            m_Height = height;
        }

        ~WindowEvent() = default;

        void HandleEvent(Event* event) override {
            if (auto* windowEvent = dynamic_cast<WindowEvent*>(event)) {
                OnWindowResize(windowEvent->m_Window, windowEvent->m_Width, windowEvent->m_Height);
            }
        }
    private:
        GLFWwindow* m_Window;
        int m_Width, m_Height;
    protected:
        void RegisterEvents() override {EventDispatcher::AddReceiver(this);}
        virtual void OnWindowResize(GLFWwindow* window, int width, int height) {}
    };

} // DuckEngine

#endif //DUCKENGINE_WINDOWEVENT_H
