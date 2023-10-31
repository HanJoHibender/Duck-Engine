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

    void Mouse::cursor_position_callback(double xpos, double ypos) {
            x = xpos;
            y = ypos;
    }

    bool Mouse::IsPressing(int keycode) const {
        return glfwGetKey(m_Window, keycode);
    }
} // DuckEngine