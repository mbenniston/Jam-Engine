#pragma once
#include <string>

#include "vendor.h"

#include "../../Assets/AssetLoader.h"

namespace Jam
{
    enum class FilterType : int{
        LINEAR,
        NEAREST,
        NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR,
    };

    GLenum FilterTypeToEnum(FilterType);

    class Texture
    {
    private:
        GLuint m_id = 0;
        GLenum m_type;

        int m_width, m_height, m_channels;

        GLenum m_minFilter, m_magFilter;

    public:

        inline int getNumChannels() const {
            return m_channels;
        }

        inline int getWidth() const {
            return m_width;
        }

        inline int getHeight() const {
            return m_height;
        }

        void setParameter(GLenum penum, GLint value); //Requires bind
        void setParameter(GLenum penum, GLfloat value); //Requires bind

        void setMinFilter(GLenum minFilter); //Requires bind
        void setMagFilter(GLenum magFilter); //Requires bind

        inline GLenum getMinFilter() const {
            return m_minFilter;
        }

        inline GLenum getMagFilter() const {
            return m_magFilter;
        }

        void generateMipmaps(); //Requires bind

        void bind() const;
        void bind(int) const;
        void unbind() const;
        void release();

        void loadFromFile(const Jam::File& filePath, GLenum minFilter=GL_LINEAR, GLenum magFilter=GL_LINEAR);
        void loadFromArray(void* data, size_t width, size_t height, GLenum internalFormat, GLenum format, GLenum dataType, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);

        bool operator==(const Texture& other) const {
            return m_id == other.m_id;
        }

        Texture();
    };
}