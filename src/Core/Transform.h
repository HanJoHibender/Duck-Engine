//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_TRANSFORM_H
#define DUCKENGINE_TRANSFORM_H

#include "pch.hxx"

namespace DuckEngine {

    class Transform {
    public:
        Transform() = default;
        glm::vec3 Position = {0,0,0};
        glm::vec3 Rotation = {0,0,0};
        glm::vec3 Scale = {1,1,1};

        glm::vec3 FORWARD() const;
        glm::vec3 RIGHT() const;
        static glm::vec3 UP;

        glm::quat GetQuat() const;
        glm::mat4 CreateTransformationMatrix() const;
    };

} // DuckEngine

#endif //DUCKENGINE_TRANSFORM_H
