//
// Created by VrikkaDev on 31/10/2023.
//

#ifndef DUCKEXAMPLE_MOUSE_H
#define DUCKEXAMPLE_MOUSE_H

namespace DuckEngine {

    class Mouse {
    public:
        explicit Mouse(GLFWwindow* window);

        glm::vec2 GetPosition() const;

        bool IsPressing(int keycode) const;

        void cursor_position_callback(double xpos, double ypos);
    private:
        GLFWwindow* m_Window;
        double x = 0, y = 0;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_MOUSE_H
