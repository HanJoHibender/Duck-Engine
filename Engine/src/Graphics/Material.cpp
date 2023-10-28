//
// Created by VrikkaDev on 24/10/2023.
//

#include "Material.h"

namespace DuckEngine {
    Material::Material()
            : m_Shader(std::make_shared<Shader>("./Assets/Shaders/default.vert", "./Assets/Shaders/default.frag")),
            m_Ambient{0.1f,0.1f,0.1f}, m_Diffuse{0.8f, 0.8f, 0.8f}, m_Specular{1.0f, 1.0f, 1.0f}, m_Shininess{32.0f} {
    }

    Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
            : m_Shader(std::make_shared<Shader>("./Assets/Shaders/default.vert", "./Assets/Shaders/default.frag")),
            m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess) {
    }

    void Material::SetAmbient(const glm::vec3& ambient) {
        m_Ambient = ambient;
    }

    void Material::SetDiffuse(const glm::vec3& diffuse) {
        m_Diffuse = diffuse;
    }

    void Material::SetSpecular(const glm::vec3& specular) {
        m_Specular = specular;
    }

    void Material::SetShininess(float shininess) {
        m_Shininess = shininess;
    }

    void Material::SetShader(std::shared_ptr<Shader> shader) {
        m_Shader = shader;
    }

    std::shared_ptr<Shader> Material::GetShader() {
        return m_Shader;
    }

    void Material::UseMaterial() {

        m_Shader->Bind(); // Activate the shader program

        // Send the material properties as uniforms to the shader
        /*m_Shader->LoadVector3(m_Shader->GetLocation("material.ambient"), m_Ambient);
        m_Shader->LoadVector3(m_Shader->GetLocation("material.diffuse"), m_Diffuse);
        m_Shader->LoadVector3(m_Shader->GetLocation("material.specular"), m_Specular);
        m_Shader->LoadFloat(m_Shader->GetLocation("material.shininess"), m_Shininess);*/

    }
} // DuckEngine