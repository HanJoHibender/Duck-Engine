//
// Created by VrikkaDev on 13/10/2023.
//

#include "Keybind.h"

#include <utility>

namespace DuckEngine {

    Keybind::Keybind(int keycode, std::string keyname) {
        this->m_Keycode = keycode;
        this->m_DefaultKey = keycode;
        this->m_Keyname = std::move(keyname);
    }

    void Keybind::SetKey(int keycode) {
        this->m_Keycode = keycode;
    }

    int Keybind::GetKey() const {
        return this->m_Keycode;
    }

    int Keybind::GetDefaultKey() const {
        return this->m_DefaultKey;
    }

    void Keybind::SetPressed(bool value) {
        m_Pressed = value;
    }

    bool Keybind::IsPressed() {
        return m_Pressed;
    }

    std::string Keybind::GetKeyName() {
        return m_Keyname;
    }
} // DuckEngine