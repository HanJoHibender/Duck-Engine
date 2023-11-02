//
// Created by VrikkaDev on 31/10/2023.
//

#ifndef DUCKEXAMPLE_CAMERAMOVEMENTCOMPONENT_H
#define DUCKEXAMPLE_CAMERAMOVEMENTCOMPONENT_H

#include "Engine.h"

class CameraMovementComponent : public DuckEngine::Component {
public:
    CameraMovementComponent();

    void OnAttached(DuckEngine::SceneObject* object) override;
    void OnFixedUpdate(float dt) override;

    float speed = 0.001f;
    float rotationSpeed = 0.1f;
private:
    DuckEngine::Keybind* m_KeyForward;
    DuckEngine::Keybind* m_KeyBackward;
    DuckEngine::Keybind* m_KeyRight;
    DuckEngine::Keybind* m_KeyLeft;

    DuckEngine::Keybind* m_MouseKeyRight;

    std::shared_ptr<DuckEngine::Input> input;
};


#endif //DUCKEXAMPLE_CAMERAMOVEMENTCOMPONENT_H
