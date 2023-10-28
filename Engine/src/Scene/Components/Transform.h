//
// Created by VrikkaDev on 02/10/2023.
//

#ifndef DUCKENGINE_TRANSFORM_H
#define DUCKENGINE_TRANSFORM_H

#include "pch.hxx"
#include "Component.h"

namespace DuckEngine {

    class Transform : public Component{
    public:
        Transform() : Component("Transform") {}
        glm::vec3 Position = {0,0,0};
        glm::vec3 Rotation = {0,0,0};
        glm::vec3 Scale = {1,1,1};

        glm::vec3 FORWARD() const;
        glm::vec3 RIGHT() const;
        static glm::vec3 UP;

        glm::quat GetQuat() const;
        glm::mat4 CreateTransformationMatrix() const;
    };

    namespace Components{
        using DuckEngine::Transform;
    } // Components

} // DuckEngine

#endif //DUCKENGINE_TRANSFORM_H
