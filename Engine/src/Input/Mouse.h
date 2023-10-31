//
// Created by VrikkaDev on 31/10/2023.
//

#ifndef DUCKEXAMPLE_MOUSE_H
#define DUCKEXAMPLE_MOUSE_H

#include "Core/Threads/Executor.h"

namespace DuckEngine {

    class Mouse {
    public:
        explicit Mouse(GLFWwindow* window);

        glm::vec2 GetPosition() const;

        bool IsPressing(int keycode) const;

        // Set cursor mode. GLFW_CURSOR_
        void SetCursorMode(int cursor_mode);
        int GetCursorMode() const;

        void SetPosition(double xpos, double ypos);
    private:
        GLFWwindow* m_Window;
        double x = 0, y = 0;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_MOUSE_H
