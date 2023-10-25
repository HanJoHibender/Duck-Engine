//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_WINDOW_H
#define DUCKENGINE_WINDOW_H

#include "pch.hxx"
#include "Input/Keyboard.h"
#include "RenderStack.h"

namespace DuckEngine {

    class Window {
    public:
        Window(uint32_t width, uint32_t height, const char* title);
        void SwapBuffers();
        void Destroy();

        bool IsRunning = false;
        bool IsFocused = false;

        void SetVsync(bool value){
            glfwSwapInterval(value);
        }

        glm::vec2 GetWindowSize();

        Keyboard* keyboard;

        static std::vector<Window*> WindowInstances(){
            return m_Windows;
        }

        static Window* GetWindowOf(GLFWwindow* window){
            for(Window* w : m_Windows){
                if (w->m_Window == window){
                    return w;
                }
            }
            return nullptr;
        }


        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void resize_callback(GLFWwindow* window, int w, int h);
    private:
        GLFWwindow* m_Window;
        glm::vec2 m_WindowSize;

        static std::vector<Window*> m_Windows;
    };

} // DuckEngine

#endif //DUCKENGINE_WINDOW_H
