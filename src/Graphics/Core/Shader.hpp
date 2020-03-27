#pragma once
#include <string>
#include <map>
#include "vendor.h"

#include "../../Assets/AssetLoader.h"

namespace Jam
{
    class Shader
    {
    private:
        GLuint m_program = 0;
        std::map<std::string, GLint> m_uniforms;
        std::map<GLenum, std::map<std::string, GLuint>> m_subroutines;

    public:

        GLint getUniformLocation(const std::string& name);
        GLuint getSubroutineLocation(GLenum shaderType, const std::string& name);

        //all subroutines must be set at once for one shader type
        void loadSubroutines(GLenum shaderType, const std::vector<std::string>& names);

        void loadUniform(const std::string& name, int);
        void loadUniform(const std::string& name, float);
        void loadUniform(const std::string& name, glm::vec2);
        void loadUniform(const std::string& name, glm::vec3);
        void loadUniform(const std::string& name, glm::vec4);
        void loadUniform(const std::string& name, const glm::mat4&);

        void use() const;
        void dispose() const;
        void release();

        void loadFromFile(const File& vPath, const File& fPath);
        void loadFromString(const std::string& vSource, const std::string& fSource);
    };
}