//
// Created by VrikkaDev on 24/10/2023.
//

#include "Model.h"

namespace DuckEngine {
    Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
        m_Mesh = mesh;
        m_Material = material;
    }

    void Model::Draw(Camera* camera, const Transform& transform) {

        std::cout<<"Model :: Draw"<<std::endl;

        // Create transformation matrix
        glm::mat4 matrix = transform.CreateTransformationMatrix();
        // Get view projection matrix from camera
        glm::mat4 vp = camera->GetViewProjectionMatrix();

        // Calculate model-view-projection matrix
        glm::mat4 mvp = vp * matrix;

        auto view = camera->GetViewMatrix();
        auto proj = camera->GetProjectionMatrix();
        auto trans = matrix;

        glEnable(GL_LIGHTING);

        // Load the material variables to shader
        m_Material->UseMaterial();

        // Load the matrices to the shader
        m_Material->GetShader()->LoadUniform("viewMatrix", view);
        m_Material->GetShader()->LoadUniform("projectionMatrix", proj);
        m_Material->GetShader()->LoadUniform("transformationMatrix", trans);

        // Bind mesh and draw
        m_Mesh->Bind();

        glDrawElements(GL_TRIANGLES, m_Mesh->GetIndexCount(), GL_UNSIGNED_INT, (void*)nullptr);

        // UnBind mesh, shader program
        m_Mesh->UnBind();
        m_Material->GetShader()->UnBind();
    }
} // DuckEngine