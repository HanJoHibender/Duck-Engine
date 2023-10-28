//
// Created by VrikkaDev on 24/10/2023.
//

#ifndef DUCKENGINE_MATERIAL_H
#define DUCKENGINE_MATERIAL_H


#include "Shader.h"

namespace DuckEngine {

    class Material {
    public:
        Material();
        Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);

        void SetAmbient(const glm::vec3& ambient);
        void SetDiffuse(const glm::vec3& diffuse);
        void SetSpecular(const glm::vec3& specular);
        void SetShininess(float shininess);

        void SetShader(std::shared_ptr<Shader> shader); // Set the shader for this material
        std::shared_ptr<Shader> GetShader();

        void UseMaterial(); // Activate this material's shader program and set uniform values

    private:
        glm::vec3 m_Ambient;
        glm::vec3 m_Diffuse;
        glm::vec3 m_Specular;
        float m_Shininess;
        std::shared_ptr<Shader> m_Shader; // The shader associated with this material
    };

} // DuckEngine

#endif //DUCKENGINE_MATERIAL_H
