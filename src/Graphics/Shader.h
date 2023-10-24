//
// Created by VrikkaDev on 24/10/2023.
//

#ifndef DUCKENGINE_SHADER_H
#define DUCKENGINE_SHADER_H

#include "pch.hxx"

namespace DuckEngine {

    class Shader {
    public:
        Shader(std::string_view vertex, std::string* fragment);
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        int GetLocation(const char* name) const;

        void LoadInt(int location, GLint value);
        void LoadFloat(int location, GLfloat value);

        void LoadVector2(int location, glm::vec2& vec);
        void LoadVector3(int location, glm::vec3& vec);
        void LoadVector4(int location, glm::vec4& vec);
        void LoadMatrix(int location, glm::mat4& matrix);

        // LoadUniform uses GetLocations. so if use LoadUniform override the GetLocaitnos
        virtual void LoadUniform(const std::string& name, glm::mat4& matrix);
        virtual std::map<std::string, int> GetLocations();
    protected:
        uint32_t m_ShaderProgram;
    };

} // DuckEngine

#endif //DUCKENGINE_SHADER_H
