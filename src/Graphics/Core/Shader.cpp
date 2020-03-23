#include "jampch.h"
#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Jam
{
    static std::string readShader(const std::string& path) {
        std::ifstream file(path);

        std::stringstream ss;
        ss << file.rdbuf();

        return ss.str();
    }

    static GLuint loadShader(const std::string& source, GLenum type)
    {
        GLuint shader = glCreateShader(type);
        GLint length = source.length();
        const char* string = source.c_str();
        glShaderSource(shader, 1, (const GLchar* const*)&string, &length);

        glCompileShader(shader);

        //CHANGE ME: Check compilation status

        return shader;
    }

    void Shader::use() const {
        glUseProgram(m_program);
    }

    void Shader::dispose() const {
        glUseProgram(0);
    }

    void Shader::release() {
        glDeleteProgram(m_program);
    }

    void Shader::loadFromFile(const File& vPath, const File& fPath) {
        loadFromString(
            readShader(std::string(vPath.getData().begin(), vPath.getData().end())), 
            readShader(std::string(fPath.getData().begin(), fPath.getData().end())));
    }

    void Shader::loadFromString(const std::string& vSource, const std::string& fSource) {
        m_program = glCreateProgram();
        GLuint vShader = loadShader(vSource, GL_VERTEX_SHADER), fShader = loadShader(fSource, GL_FRAGMENT_SHADER);

        glAttachShader(m_program, vShader);
        glAttachShader(m_program, fShader);
        glLinkProgram(m_program);
        glValidateProgram(m_program);

        glDeleteShader(vShader);
        glDeleteShader(fShader);
        std::cout << m_program << std::endl;

    }

    GLint Shader::getUniformLocation(const std::string& name) {
        if (m_uniforms.find(name) == m_uniforms.end()) {
            GLint id = glGetUniformLocation(m_program, name.c_str());
            m_uniforms[name] = id;
            return id;
            //CHANGE ME: Check for when it is not found
        }
        else {
            return m_uniforms.at(name);
        }
    }


    void Shader::loadUniform(const std::string& name, float f0) {
        glUniform1f(getUniformLocation(name), f0);
    }


    void Shader::loadUniform(const std::string& name, glm::vec2 vec) {
        glUniform2f(getUniformLocation(name), vec.x, vec.y);
    }


    void Shader::loadUniform(const std::string& name, glm::vec3 vec) {
        glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
    }


    void Shader::loadUniform(const std::string& name, glm::vec4 vec) {
        glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
    }

    void Shader::loadUniform(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(getUniformLocation(name), 1, false, &matrix[0][0]);
        //CHECK: Overhead of search for uniform
    }

}