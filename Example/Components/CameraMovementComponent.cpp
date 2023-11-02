//
// Created by VrikkaDev on 31/10/2023.
//

#include "CameraMovementComponent.h"

CameraMovementComponent::CameraMovementComponent() : Component("CameraMovementComponent"){
    m_KeyForward = new DuckEngine::Keybind(GLFW_KEY_W, "forward");
    m_KeyBackward = new DuckEngine::Keybind(GLFW_KEY_S, "backward");
    m_KeyLeft = new DuckEngine::Keybind(GLFW_KEY_A, "left");
    m_KeyRight = new DuckEngine::Keybind(GLFW_KEY_D, "right");

    m_MouseKeyRight = new DuckEngine::Keybind(GLFW_MOUSE_BUTTON_RIGHT, "right mouse button");
}

void CameraMovementComponent::OnAttached(DuckEngine::SceneObject* object) {
    Component::OnAttached(object);

    input = object->GetScene()->window.input;

    input->AddKeybind(m_KeyForward);
    input->AddKeybind(m_KeyBackward);
    input->AddKeybind(m_KeyLeft);
    input->AddKeybind(m_KeyRight);

    input->AddKeybind(m_MouseKeyRight);
}

void CameraMovementComponent::OnFixedUpdate(float dt) {

    auto* cameraTransform = (DuckEngine::Components::Transform*)GetObject()->GetComponent<DuckEngine::Components::Transform>();

    if(m_KeyForward->IsPressed()){
        cameraTransform->Position -= cameraTransform->FORWARD() * speed;
    }
    if(m_KeyBackward->IsPressed()){
        cameraTransform->Position += cameraTransform->FORWARD() * speed;
    }
    if(m_KeyRight->IsPressed()){
        cameraTransform->Position += cameraTransform->RIGHT() * speed;
    }
    if(m_KeyLeft->IsPressed()){
        cameraTransform->Position -= cameraTransform->RIGHT() * speed;
    }

    if(m_MouseKeyRight->IsPressed()){
        input->mouse->SetCursorMode(GLFW_CURSOR_DISABLED);

        glm::vec2 mouseVelocity = input->mouse->GetVelocity();
        auto* trans = (DuckEngine::Components::Transform*)GetObject()->GetComponent<DuckEngine::Components::Transform>();

        trans->Rotation.x += mouseVelocity.y * rotationSpeed; // Pitch (up and down)
        trans->Rotation.y += mouseVelocity.x * rotationSpeed; // Yaw (left and right)

        const float maxPitchAngle = 80.0f;
        trans->Rotation.x = glm::clamp(trans->Rotation.x, -maxPitchAngle, maxPitchAngle);

    }else{
        input->mouse->SetCursorMode(GLFW_CURSOR_NORMAL);
    }
}