#include "jampch.h"
#include "Texture.hpp"
#include <iostream>

#include "../../misc.hpp"

namespace Jam
{
	void Texture::setParameter(GLenum penum, GLint value)
	{
        glTexParameteri(m_type, penum, value);
	}

    void Texture::setParameter(GLenum penum, GLfloat value)
    {
        glTexParameterf(m_type, penum, value);
    }

    void Texture::setMinFilter(GLenum minFilter)
    {
        m_minFilter = minFilter;
        setParameter(GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
    }

    void Texture::setMagFilter(GLenum magFilter)
    {
        m_magFilter = magFilter;
        setParameter(GL_TEXTURE_MAG_FILTER, (GLint)magFilter);
    }

    void Texture::generateMipmaps()
    {
        glGenerateMipmap(m_type);
    }

	void Texture::bind() const {
        bind(0);
    }

    void Texture::bind(int textureUnit) const {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(m_type, m_id);
    }

    void Texture::unbind() const {
        glBindTexture(m_type, 0);
    }

    void Texture::release() {
        MISC_CHECK_REM_ID(m_id);
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }

    void Texture::loadFromFile(const Jam::File& file, GLenum minFilter, GLenum magFilter) {
        MISC_CHECK_GEN_ID(m_id);
        glGenTextures(1, &m_id);
        m_type = GL_TEXTURE_2D;

        unsigned char* data = stbi_load_from_memory(file.getData().data(), file.getData().size(), &m_width, &m_height, &m_channels, 0);
        assert(data != nullptr);
        if(!data) {
            PLOG_ERROR("could not load texture from file");
        }

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

        setMagFilter(minFilter);
        setMinFilter(magFilter);

        if (minFilter >= GL_NEAREST_MIPMAP_NEAREST) {
            generateMipmaps();
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        unbind();
        stbi_image_free(data);
    }

    void Texture::loadFromArray(void* data, size_t width, size_t height, GLenum internalFormat, GLenum format, GLenum dataType, GLenum minFilter, GLenum magFilter)
    {
        MISC_CHECK_GEN_ID(m_id);
        glGenTextures(1, &m_id);
        m_type = GL_TEXTURE_2D;
        m_width = width;
        m_height = height;
        bind();
        glTexImage2D(m_type, 0, internalFormat, width, height, 0, format, dataType, data);

        setMagFilter(minFilter);
        setMinFilter(magFilter);

        if (minFilter >= GL_NEAREST_MIPMAP_NEAREST) {
            generateMipmaps();
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        unbind();
    }

    Texture::Texture() : m_id(0), m_width(0), m_height(0), m_channels(0), m_type(GL_TEXTURE_2D), m_minFilter(GL_LINEAR), m_magFilter(GL_LINEAR)
    {
    }
}