//
// Created by VrikkaDev on 29/09/2023.
//

#include "Camera.h"

namespace DuckEngine {
    Camera::Camera(Transform& transform): {
        this->RegisterEvents();
    }

    void Camera::OnWindowResize(GLFWwindow* window, int width, int height) {
        UpdateProjection(width, height);
    }

    void Camera::UpdateProjection(uint32_t width, uint32_t height) {
        float aspect_ratio = width/height;

        // Compute projection matrix using perspective projection
        m_ProjectionMatrix = glm::perspective(glm::radians(Fov), aspect_ratio, NearPlane, FarPlane);
    }

    void Camera::UpdateView() {
        // Create rotation matrix from quaternion
        glm::mat4 matrix(1.f);
        glm::mat3 rot = glm::mat3_cast(m_Transform.GetQuat());

        // Translate matrix by the inverse of camera position
        matrix = glm::translate(matrix, -m_Transform.Position);

        // Compute view matrix by multiplying rotation and translation matrices
        m_ViewMatrix = glm::mat4(rot) * matrix;
    }
} // DuckEngine