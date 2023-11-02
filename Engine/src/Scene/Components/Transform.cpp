//
// Created by VrikkaDev on 26/09/2023.
//

#include "Transform.h"

namespace DuckEngine {
    glm::vec3 Transform::UP = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 Transform::FORWARD() const {
        auto Quaternion = GetQuat();
        // Compute the forward direction vector using quaternion rotation
        glm::vec3 forward = glm::vec3(-(2 * (Quaternion.x * Quaternion.z + Quaternion.w * Quaternion.y)),
                                      glm::radians(Rotation.x),
                                      1 - 2 * (Quaternion.x * Quaternion.x + Quaternion.y * Quaternion.y));
        return forward;
    }

    glm::vec3 Transform::RIGHT() const {
        auto Quaternion = GetQuat();
        // Compute the right direction vector using quaternion rotation
        glm::vec3 right = glm::vec3(1 - 2 * (Quaternion.y * Quaternion.y + Quaternion.z * Quaternion.z),
                                    0.f,
                                    -(2 * (Quaternion.x * Quaternion.z - Quaternion.w * Quaternion.y)));
        return right;
    }

    glm::mat4 Transform::CreateTransformationMatrix() const {
        // Create a 4x4 identity matrix
        glm::mat4 unit = glm::mat4(1.0f);

        // Create a translation matrix with the Position vector
        glm::mat4 t = glm::translate(unit, Position);
        // Create a rotation matrix for each axis (X, Y, Z) using quaternion rotation
        glm::mat4 rotx = glm::rotate(unit, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 roty = glm::rotate(unit, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotz = glm::rotate(unit, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        // Combine the rotation matrices into a single rotation matrix
        glm::mat4 r = rotx * roty * rotz;
        // Create a scaling matrix with a uniform scale factor of 0.1
        glm::mat4 s = glm::scale(unit, glm::vec3(0.1f));
        // Combine the translation, rotation, and scaling matrices into a single transformation matrix
        glm::mat4 matrix = t * r * s;
        // Return the computed transformation matrix
        return matrix;
    }

    glm::quat Transform::GetQuat() const {
        // Construct a rotation matrix from the rotation vector
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        // Extract the quaternion from the rotation matrix
        return glm::quat_cast(rotationMatrix);
    }

} // DuckEngine