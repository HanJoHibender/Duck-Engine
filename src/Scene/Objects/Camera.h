//
// Created by VrikkaDev on 29/09/2023.
//

#ifndef DUCKENGINE_CAMERA_H
#define DUCKENGINE_CAMERA_H

#include "Event/WindowEvent.h"
#include "pch.hxx"
#include "Scene/Components/Transform.h"
#include "Scene/SceneObject.h"

// Returns if camera doesnt have Transform component
#define CAMERA_ASSERT_NULL_TRANSFORM if(m_Transform == nullptr){std::cerr<<"Camera doesn't have Transform component. Please fix :)"<<std::endl; return;}

namespace DuckEngine {


    class Camera : public WindowEvent, public SceneObject {
    public:
        float Fov = 80, NearPlane = 0.00001, FarPlane = 1000;

        Camera();
        Camera(SceneObject& object);

        void UpdateView();
        void UpdateProjection(uint32_t width, uint32_t height);

        void OnComponentAttached(const Component& component) override;
        void OnWindowResize(GLFWwindow* window, int width, int height) override;
    private:
        Transform* m_Transform = nullptr;
        glm::mat4 m_ViewMatrix{};
        glm::mat4 m_ProjectionMatrix{};
    };

    namespace SceneObjects{
        using DuckEngine::Camera;
    } // SceneObjects
} // DuckEngine

#endif //DUCKENGINE_CAMERA_H
