//
// Created by VrikkaDev on 23/10/2023.
//

#ifndef DUCKENGINE_MESH_H
#define DUCKENGINE_MESH_H

#include "pch.hxx"
#include "Vertex.h"

namespace DuckEngine {

    class Mesh {
    public:
        explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        uint32_t GetVertexCount() const {return m_VertexCount;}
        uint32_t GetIndexCount() const {return m_IndexCount;}
        uint32_t getVAO() const{return m_VAO;}

        // Binds the buffers
        void Bind() const;
        // Unbinds the buffers
        void UnBind() const;

        // Returns Mesh of basic cube
        static Mesh CUBE();
    private:
        uint32_t m_VAO = 0, m_VBO = 0, m_EBO = 0;
        uint32_t m_VertexCount = 0, m_IndexCount = 0;
    };

} // DuckEngine

#endif //DUCKENGINE_MESH_H
