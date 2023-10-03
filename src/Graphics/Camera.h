//
// Created by VrikkaDev on 29/09/2023.
//

#ifndef DUCKENGINE_CAMERA_H
#define DUCKENGINE_CAMERA_H

#include "Event/WindowEvent.h"
#include "pch.hxx"

namespace DuckEngine {

    class Camera : public WindowEvent{
    public:
        explicit Camera(Transform& transform);

        float Fov = 80, NearPlane = 0.00001, FarPlane = 1000;

        void UpdateView();
        void UpdateProjection(uint32_t width, uint32_t height);

        void OnWindowResize(GLFWwindow* window, int width, int height) override;
    private:
        Transform& m_Transform;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
    };

} // DuckEngine

#endif //DUCKENGINE_CAMERA_H
