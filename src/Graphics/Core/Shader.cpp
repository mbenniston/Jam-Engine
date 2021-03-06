#include "jampch.h"
#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

#include "PowerLogger.hpp"
#include "misc.hpp"

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
        GLint length = (GLint)source.length();
        const char* string = source.c_str();
        glShaderSource(shader, 1, (const GLchar* const*)&string, &length);

        glCompileShader(shader);

        GLint result = GL_FALSE;
        int logLength;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> shaderError(logLength);
            glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);

            PLOG_ERROR("Shader compilation failed: {}", std::string(shaderError.begin(), shaderError.end()));
            return 0;
        }

        return shader;
    }

    void Shader::use() const {
        glUseProgram(m_program);
    }

    void Shader::dispose() const {
        glUseProgram(0);
    }

    void Shader::release() {
        MISC_CHECK_REM_ID(m_program);
        glDeleteProgram(m_program);
        m_program = 0;
    }

    void Shader::loadFromFile(const File& vPath, const File& fPath) {
        loadFromString(
            std::string(vPath.getData().begin(), vPath.getData().end()),
            std::string(fPath.getData().begin(), fPath.getData().end()));
    }

    void Shader::loadFromString(const std::string& vSource, const std::string& fSource) {
        MISC_CHECK_GEN_ID(m_program);
        m_program = glCreateProgram();
        GLuint vShader = loadShader(vSource, GL_VERTEX_SHADER), fShader = loadShader(fSource, GL_FRAGMENT_SHADER);

        if (vShader != 0 && fShader != 0) {
            glAttachShader(m_program, vShader);
            glAttachShader(m_program, fShader);
            glLinkProgram(m_program);
            glValidateProgram(m_program);

            glDeleteShader(vShader);
            glDeleteShader(fShader);
        }
    }

    GLint Shader::getUniformLocation(const std::string& name) {
        if (m_uniforms.find(name) == m_uniforms.end()) {
            GLint id = glGetUniformLocation(m_program, name.c_str());
            if (id < 0) {
                PLOG_ERROR("Could not get uniform with name: {}", name);
            }

            m_uniforms[name] = id;
            return id;
        }
        else {
            return m_uniforms.at(name);
        }
    }


	void Shader::loadUniform(const std::string& name, int i0)
	{
        glUniform1i(getUniformLocation(name), i0);
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

    void Shader::loadSubroutines(GLenum shaderType, const std::vector<std::string>& names)
    {
        std::vector<GLuint> ids;
        ids.reserve(names.size());

        for(const auto& name : names) {
            ids.push_back(getSubroutineLocation(shaderType, name));
        } 
        glUniformSubroutinesuiv(shaderType, (GLsizei)ids.size(), ids.data());
    }

    GLuint Shader::getSubroutineLocation(GLenum shaderType, const std::string& name) {
        GLuint id = glGetSubroutineIndex(m_program, shaderType, name.c_str());

        if(id != GL_INVALID_INDEX) {
            m_subroutines[shaderType][name] = id;
        } else {
            PLOG_ERROR("Cannot find subroutine with name: {}", name);
        }

        return id;
    }

}