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

        void AddKeybind(Keybind* keybind);
        void RemoveKeybind(Keybind* keybind);

        std::vector<Keybind*> GetKeybinds();
        std::vector<Keybind*> GetKeybindsOf(int keycode);

        void OnKeyCallback(int key, int scancode, int action, int mods);
    private:
        std::vector<Keybind*> m_Keybinds;
        GLFWwindow* m_Window;
    };

} // DuckEngine

#endif //DUCKENGINE_KEYBOARD_H
