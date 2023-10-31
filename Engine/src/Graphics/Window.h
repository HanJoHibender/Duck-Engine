//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_WINDOW_H
#define DUCKENGINE_WINDOW_H

#include "pch.hxx"
#include "Input/Keyboard.h"
#include "RenderStack.h"
#include "Input/Mouse.h"
#include "Input/Input.h"

namespace DuckEngine {

    class Scene;

    class Window {
    public:
        Window(uint32_t width, uint32_t height, const char* title);
        void SwapBuffers();
        void RenderBackground() const;
        void Destroy();

        bool IsRunning = false;
        bool IsFocused = false;

        void SetVsync(bool value){
            glfwSwapInterval(value);
        }

        glm::vec2 GetWindowSize();

        std::shared_ptr<Input> input;

        Color background_color{};
        // TODO probably should make private and add getter and setter or something. and a check so ther cant be multiple same
        std::vector<std::shared_ptr<Scene>> scenes{};

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
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        static void resize_callback(GLFWwindow* window, int w, int h);
    private:
        GLFWwindow* m_Window;
        glm::vec2 m_WindowSize;

        static std::vector<Window*> m_Windows;
    };

} // DuckEngine

#endif //DUCKENGINE_WINDOW_H
