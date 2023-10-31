//
// Created by VrikkaDev on 26/09/2023.
//

#include "Keyboard.h"

namespace DuckEngine {
    Keyboard::Keyboard(GLFWwindow* window) {
        m_Window = window;
    }

    bool Keyboard::IsPressing(int keycode) {
        return glfwGetKey(m_Window, keycode);
    }

} // DuckEngine