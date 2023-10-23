//
// Created by VrikkaDev on 23/10/2023.
//

#ifndef DUCKENGINE_VERTEX_H
#define DUCKENGINE_VERTEX_H

#include "pch.hxx"

namespace DuckEngine {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };

} // DuckEngine

#endif //DUCKENGINE_VERTEX_H
