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
        glm::vec2 GetVelocity() const;

        bool IsPressing(int keycode) const;

        // Set cursor mode. GLFW_CURSOR_
        void SetCursorMode(int cursor_mode);
        int GetCursorMode() const;

        // Gets called from Input
        void Update();

        void SetPosition(double xpos, double ypos);
    private:
        GLFWwindow* m_Window;
        glm::vec2 position = glm::vec2(0.f, 0.f);
        glm::vec2 velocity = glm::vec2(0.f, 0.f);
        glm::vec2 prevpos = glm::vec2(0.f, 0.f);
    };

} // DuckEngine

#endif //DUCKEXAMPLE_MOUSE_H
