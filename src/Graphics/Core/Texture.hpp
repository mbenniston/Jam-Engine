#pragma once
#include <string>

#include "vendor.h"

#include "../../Assets/AssetLoader.h"

namespace Jam
{
    class Texture
    {
    private:
        GLuint m_id = 0;
        GLenum m_type;

        int m_width, m_height, m_channels;

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

        void bind() const;
        void unbind() const;
        void release();

        void loadFromFile(const Jam::File& filePath);
        void loadFromArray(void* data, size_t width, size_t height, GLenum internalFormat, GLenum format, GLenum dataType);

    };
}