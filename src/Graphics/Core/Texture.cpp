#include "jampch.h"
#include "Texture.hpp"
#include <iostream>

namespace Jam
{
    void Texture::bind() const {
        glBindTexture(m_type, m_id);
    }

    void Texture::unbind() const {
        glBindTexture(m_type, 0);
    }

    void Texture::release() {
        glDeleteTextures(1, &m_id);
    }

    void Texture::loadFromFile(const std::string& filePath) {
        glGenTextures(1, &m_id);
        m_type = GL_TEXTURE_2D;

        unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_channels, 0);
        assert(data != nullptr);

        bind();
        switch (m_channels)
        {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        default:
            std::cout << m_channels << " channels not supported" << std::endl;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        unbind();
    }
}