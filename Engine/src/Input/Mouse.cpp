//
// Created by VrikkaDev on 31/10/2023.
//

#include "Mouse.h"

namespace DuckEngine {
    Mouse::Mouse(GLFWwindow* window) : m_Window(window){

    }

    glm::vec2 Mouse::GetPosition() const {
        return {x, y};
    }

    void Mouse::SetCursorMode(int cursor_mode) {

        if(GetCursorMode() == cursor_mode){
            return;
        }

        // Execite glfwSetInputMode on the main
        Executor::mainThreadExecutor.Submit(glfwSetInputMode, m_Window, GLFW_CURSOR, cursor_mode);
    }

    int Mouse::GetCursorMode() const {
        return glfwGetInputMode(m_Window, GLFW_CURSOR);
    }

    bool Mouse::IsPressing(int keycode) const {
        return glfwGetKey(m_Window, keycode);
    }

    void Mouse::SetPosition(double xpos, double ypos) {
            x = xpos;
            y = ypos;
    }
} // DuckEngine