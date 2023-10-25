//
// Created by VrikkaDev on 29/09/2023.
//

#include "Camera.h"

namespace DuckEngine {
    Camera::Camera() : SceneObject() {
        this->RegisterEvents();
    }

    Camera::Camera(SceneObject& object) : SceneObject(object) {
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
        CAMERA_ASSERT_NULL_TRANSFORM

        // Create rotation matrix from quaternion
        glm::mat4 matrix(1.f);
        glm::mat3 rot = glm::mat3_cast(m_Transform->GetQuat());

        // Translate matrix by the inverse of camera position
        matrix = glm::translate(matrix, -m_Transform->Position);

        // Compute view matrix by multiplying rotation and translation matrices
        m_ViewMatrix = glm::mat4(rot) * matrix;
    }

    glm::mat4 Camera::GetViewMatrix() {
        return m_ViewMatrix;
    }

    glm::mat4 Camera::GetProjectionMatrix() {
        return m_ProjectionMatrix;
    }

    glm::mat4 Camera::GetViewProjectionMatrix() {
        return m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::OnComponentAttached(const Component& component) {
        // Should probably use the input component
        if(this->HasComponent<Transform>()){
            this->m_Transform = &this->GetComponent<Transform>();
        }
    }

} // DuckEngine