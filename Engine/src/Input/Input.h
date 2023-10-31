//
// Created by VrikkaDev on 31/10/2023.
//

#ifndef DUCKEXAMPLE_INPUT_H
#define DUCKEXAMPLE_INPUT_H

#include "Keyboard.h"
#include "Mouse.h"

namespace DuckEngine {

    class Input {
    public:
        explicit Input(GLFWwindow* window);

        std::shared_ptr<Keyboard> keyboard;
        std::shared_ptr<Mouse> mouse;


        void AddKeybind(Keybind* keybind);
        void RemoveKeybind(Keybind* keybind);

        std::vector<Keybind*> GetKeybinds();
        std::vector<Keybind*> GetKeybindsOf(int keycode);

        void OnKeyCallback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void cursor_position_callback(double xpos, double ypos);
    private:
        std::vector<Keybind*> m_Keybinds;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_INPUT_H
