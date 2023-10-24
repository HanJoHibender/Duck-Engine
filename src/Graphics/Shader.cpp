//
// Created by VrikkaDev on 24/10/2023.
//

#include "Shader.h"

namespace DuckEngine {
    // Shader constructor that takes in two string pointers representing vertex and fragment shader code
    Shader::Shader(std::string* vertex, std::string* fragment) {

        // Convert the string pointers to const char pointers
        const char* vertex_source = vertex->c_str();
        const char* fragment_source = fragment->c_str();

        // Create and compile vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex_source, NULL);
        glCompileShader(vertexShader);

        GLint v_length;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &v_length);

        if(v_length > 0){
            GLchar v_log[1024];
            glGetShaderInfoLog(vertexShader, 1024, &v_length, v_log);
            std::cout<<v_log<<std::endl;
        }


        // Check for vertex shader compilation errors and log them
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout<<"Error: Vertex Shaders compilation failed"<<std::endl;
        }

        // Create and compile fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment_source, NULL);

        glCompileShader(fragmentShader);

        GLint f_length;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &f_length);

        if(f_length > 0){
            GLchar f_log[1024];
            glGetShaderInfoLog(fragmentShader, 1024, &f_length, f_log);
            std::cout<<f_log<<std::endl;
        }

        // Check for fragment shader compilation errors and log them
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout<<"Error: Fragment Shaders compilation failed"<<std::endl;
        }

        // Create a shader program, attach the shaders, and link the program
        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, vertexShader);
        glAttachShader(m_ShaderProgram, fragmentShader);
        glLinkProgram(m_ShaderProgram);

        // Check for program linking errors and log them
        glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
            std::cout<<"Error: Program linking failed"<<std::endl;
        }

        // Delete the shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

// Shader constructor that takes in the file paths for the vertex and fragment shaders and reads the code from the files
    Shader::Shader(const char* vertexPath, const char* fragmentPath) : Shader(FileUtils::ReadFileString(vertexPath), FileUtils::ReadFileString(fragmentPath)){
    }

    Shader::~Shader() {
        // Delete the shader program from OpenGL
        glDeleteProgram(m_ShaderProgram);
    }

    void Shader::Bind() const {
        // Use this shader program for subsequent rendering commands
        glUseProgram(m_ShaderProgram);
    }

    void Shader::UnBind() const {
        // Use the default shader program (none)
        glUseProgram(0);
    }

    void Shader::LoadInt(int location, GLint value) {
        // Load an integer value into a uniform variable in the shader
        glUniform1i(location, value);
    }

    void Shader::LoadFloat(int location, GLfloat value) {
        // Load a float value into a uniform variable in the shader
        glUniform1f(location, value);
    }

    void Shader::LoadVector2(int location, glm::vec2& vec) {
        // Load a 2D vector into a uniform variable in the shader
        glUniform2f(location, vec.x, vec.y);
    }

    void Shader::LoadVector3(int location, glm::vec3& vec) {
        // Load a 3D vector into a uniform variable in the shader
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void Shader::LoadVector4(int location, glm::vec4& vec) {
        // Load a 4D vector into a uniform variable in the shader
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }

    void Shader::LoadMatrix(int location, glm::mat4& matrix) {
        // Load a 4x4 matrix into a uniform variable in the shader
        glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
    }

    void Shader::LoadUniform(const std::string& name, glm::mat4& matrix) {
        // Find the location of a uniform variable by name and load the matrix into it
        if(!GetLocations().count(name)) return; // The uniform variable was not found
        LoadMatrix(GetLocations().at(name), matrix);
    }

    std::map<std::string, int> Shader::GetLocations() {
        return {{"", 0}};
    }

    int Shader::GetLocation(const char* name) const {
        return glGetUniformLocation(m_ShaderProgram ,name);
    }
} // DuckEngine