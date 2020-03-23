#pragma once
#include <string>

#include "vendor.h"

namespace Jam
{
    class Texture
    {
    private:
        GLuint m_id;
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

        void loadFromFile(const std::string& filePath);

    };
}