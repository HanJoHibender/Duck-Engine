//
// Created by VrikkaDev on 24/10/2023.
//

#ifndef DUCKENGINE_SHADER_H
#define DUCKENGINE_SHADER_H

#include "pch.hxx"
#include "Utils/FileUtils.h"

namespace DuckEngine {

    class Shader {
    public:

        // Initializes the shader with vertex and fragment sources
        Shader(std::string_view vertex, std::string_view fragment);
        // Initializes the shader with vertex and fragment paths absolute or relative
        Shader(const char* vertexPath, const char* fragmentPath);

        ~Shader();

        void Bind();
        void UnBind() const;

        int GetLocation(const char* name);

        void LoadInt(int location, GLint value);
        void LoadFloat(int location, GLfloat value);

        void LoadVector2(int location, glm::vec2& vec);
        void LoadVector3(int location, glm::vec3& vec);
        void LoadVector4(int location, glm::vec4& vec);
        void LoadMatrix(int location, glm::mat4& matrix);

        // Updates m_Locations. is called on every bind
        virtual void UpdateLocations();
        virtual std::map<std::string, int> GetLocations();

        virtual void LoadUniform(const std::string& name, glm::mat4& matrix);

    protected:
        std::map<std::string, int> m_Locations{};
        uint32_t m_ShaderProgram;
    };

} // DuckEngine

#endif //DUCKENGINE_SHADER_H
