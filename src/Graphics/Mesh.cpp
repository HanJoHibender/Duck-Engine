//
// Created by VrikkaDev on 23/10/2023.
//

#include "Mesh.h"

namespace DuckEngine {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        // Generate a VAO and VBO
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        // Bind the VAO to configure it
        glBindVertexArray(m_VAO);

        // Bind the VBO to set the vertices data in it and allocate memory using glBufferData function with GL_STATIC_DRAW usage.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, (long)(vertices.size()*sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Store the number of vertices and indices in the vertex count variable
        m_VertexCount = (vertices.size()*sizeof(Vertex));
        m_IndexCount = indices.size();

        // Specify how the vertex data is stored in the VBO
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));

        // UnBind the VBO and VAO to prevent modification of their data outside this constructor
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Mesh::Bind() const {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }

    void Mesh::UnBind() const {
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Mesh Mesh::CUBE() {

        //TODO

        /*std::vector<Vertex> vertices = {
                -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f, 1.0f,  -1.0f, 1.0f, 1.0f, // Triangle 1
                1.0f, 1.0f,-1.0f,   -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f,-1.0f, // Triangle 2...
                1.0f,-1.0f, 1.0f,   -1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,
                1.0f, 1.0f,-1.0f,   1.0f,-1.0f,-1.0f,   -1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,-1.0f,
                1.0f,-1.0f, 1.0f,   -1.0f,-1.0f, 1.0f,  -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,   1.0f,-1.0f,-1.0f,   1.0f, 1.0f,-1.0f,
                1.0f,-1.0f,-1.0f,   1.0f, 1.0f, 1.0f,   1.0f,-1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,   1.0f, 1.0f,-1.0f,   -1.0f, 1.0f,-1.0f,
                1.0f, 1.0f, 1.0f,   -1.0f, 1.0f,-1.0f,  -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,   -1.0f, 1.0f, 1.0f,  1.0f,-1.0f, 1.0f
        };*/

        const std::vector<Vertex> vertices = {

                {{0.0, 0.5, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.0}},

                {{0.5, -0.5, 0.0}, {0.0, 1.0, 0.0}, {1.0, 1.0}},

                {{-0.5, -0.5, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0}},

        };

        std::vector<uint32_t> indices = {0};

        return Mesh(vertices, indices);
    }
} // DuckEngine