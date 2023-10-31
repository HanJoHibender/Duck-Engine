//
// Created by VrikkaDev on 31/10/2023.
//

#include "Input.h"

namespace DuckEngine {
    Input::Input(GLFWwindow* window) : mouse(std::make_shared<Mouse>(window)), keyboard(std::make_shared<Keyboard>(window)){
    }

    void Input::AddKeybind(Keybind* keybind) {
        m_Keybinds.push_back(keybind);
    }

    void Input::RemoveKeybind(Keybind* keybind) {
        m_Keybinds.erase(std::find(m_Keybinds.begin(), m_Keybinds.end(), keybind));
    }

    std::vector<Keybind*> Input::GetKeybinds() {
        return m_Keybinds;
    }

    std::vector<Keybind*> Input::GetKeybindsOf(int keycode) {
        // Loops through all of the keybinds and adds them to the vector if they have same keycode. probably could do faster
        std::vector<Keybind*> r;
        std::for_each(m_Keybinds.begin(), m_Keybinds.end(), [&](Keybind* item) {
            if(item->GetKey() == keycode){
                r.push_back(item);
            }
        });
        return r;
    }

    void Input::OnKeyCallback(int key, int scancode, int action, int mods) {
        // Get keybindings with the keycode and set the status of it
        auto keys = GetKeybindsOf(key);
        std::for_each(keys.begin(), keys.end(), [&](Keybind* item) {
            item->SetPressed(action == GLFW_PRESS || action == GLFW_REPEAT);
            // Call the virtual method OnPress only on GLFW_PRESS function when
            if(action == GLFW_PRESS){
                item->OnPress();
            }
        });
    }

    void Input::mouse_button_callback(int button, int action, int mods) {
        // Get keybindings with the keycode and set the status of it
        auto keys = GetKeybindsOf(button);
        std::for_each(keys.begin(), keys.end(), [&](Keybind* item) {
            item->SetPressed(action == GLFW_PRESS || action == GLFW_REPEAT);
            // Call the virtual method OnPress only on GLFW_PRESS function when
            if(action == GLFW_PRESS){
                item->OnPress();
            }
        });
    }

    void Input::cursor_position_callback(double xpos, double ypos) {
        mouse->SetPosition(xpos, ypos);
    }
} // DuckEngine