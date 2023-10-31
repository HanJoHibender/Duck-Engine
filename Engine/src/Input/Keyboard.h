//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_KEYBOARD_H
#define DUCKENGINE_KEYBOARD_H

#include "pch.hxx"
#include "Keybind.h"

namespace DuckEngine {

    class Keyboard {
    public:
        explicit Keyboard(GLFWwindow* window);
        bool IsPressing(int keycode);
    private:
        GLFWwindow* m_Window;
    };

} // DuckEngine

#endif //DUCKENGINE_KEYBOARD_H
