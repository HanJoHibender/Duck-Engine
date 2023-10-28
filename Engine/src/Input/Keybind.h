//
// Created by VrikkaDev on 13/10/2023.
//

#ifndef DUCKENGINE_KEYBIND_H
#define DUCKENGINE_KEYBIND_H

namespace DuckEngine {

    class Keybind {
    public:
        explicit Keybind(int keycode, std::string keyname = "");

        void SetKey(int keycode);
        int GetKey() const;
        int GetDefaultKey() const;
        std::string GetKeyName();

        void SetPressed(bool value);

        bool IsPressed();
    private:
        bool m_Pressed = false;
        int m_DefaultKey = 0;
        int m_Keycode = 0;
        std::string m_Keyname;
    };

} // DuckEngine

#endif //DUCKENGINE_KEYBIND_H
