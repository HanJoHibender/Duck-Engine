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

    void Keyboard::OnKeyCallback(int key, int scancode, int action, int mods) {
        // Get keybindings with the keycode and set the status of it
        auto keys = GetKeybindsOf(key);
        std::for_each(keys.begin(), keys.end(), [&](Keybind* item) {
            item->SetPressed(action == GLFW_PRESS || action == GLFW_REPEAT);
        });
    }

    void Keyboard::AddKeybind(Keybind* keybind) {
        m_Keybinds.push_back(keybind);
    }

    void Keyboard::RemoveKeybind(Keybind* keybind) {
        m_Keybinds.erase(std::find(m_Keybinds.begin(), m_Keybinds.end(), keybind));
    }

    std::vector<Keybind*> Keyboard::GetKeybinds() {
        return m_Keybinds;
    }

    std::vector<Keybind*> Keyboard::GetKeybindsOf(int keycode) {
        // Loops through all of the keybinds and adds them to the vector if they have same keycode. probably could do faster
        std::vector<Keybind*> r;
        std::for_each(m_Keybinds.begin(), m_Keybinds.end(), [&](Keybind* item) {
            if(item->GetKey() == keycode){
                r.push_back(item);
            }
        });
        return r;
    }

} // DuckEngine