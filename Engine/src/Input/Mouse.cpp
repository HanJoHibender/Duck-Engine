//
// Created by VrikkaDev on 31/10/2023.
//

#include "Mouse.h"

namespace DuckEngine {
    Mouse::Mouse(GLFWwindow* window) : m_Window(window){

    }

    glm::vec2 Mouse::GetPosition() const {
        return position;
    }

    glm::vec2 Mouse::GetVelocity() const {
        return velocity;
    }

    void Mouse::SetCursorMode(int cursor_mode) {

        if(GetCursorMode() == cursor_mode){
            return;
        }

        // Execite glfwSetInputMode on the main thread
        Executor::mainThreadExecutor.Submit(glfwSetInputMode, m_Window, GLFW_CURSOR, cursor_mode);
    }

    int Mouse::GetCursorMode() const {
        return glfwGetInputMode(m_Window, GLFW_CURSOR);
    }

    bool Mouse::IsPressing(int keycode) const {
        return glfwGetKey(m_Window, keycode);
    }

    void Mouse::SetPosition(double xpos, double ypos) {
            position.x = xpos;
            position.y = ypos;
    }

    void Mouse::Update() {
        // Calculate mouse velocity
        velocity.x = position.x - prevpos.x;
        velocity.y = position.y - prevpos.y;

        // Store the current position as the previous position for the next frame
        prevpos.x = position.x;
        prevpos.y = position.y;
    }
} // DuckEngine