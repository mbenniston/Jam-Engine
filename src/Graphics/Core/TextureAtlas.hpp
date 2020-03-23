#pragma once
#include "vendor.h"

/* struct to calculate OpenGL texture coordinates of tiles in a tile atlas */
namespace Jam
{
    struct TextureAtlas
    {
        glm::vec2 scale;
        glm::vec2 texelSize;

        TextureAtlas() {}

        TextureAtlas(int width, int height, int widthPerImage, int heightPerImage)
        {
            scale.x = widthPerImage / (float)width;
            scale.y = heightPerImage / (float)height;
            texelSize.x = 1.0f / width;
            texelSize.y = 1.0f / height;
        }

        glm::vec2 getCoord(int i, int j) const
        {
            return scale * glm::vec2((float)i, (float)j);
        }

        glm::vec2 getNumSubTextures() {
            return glm::vec2(1.0f / scale.x, 1.0f / scale.y);
        }
    };
}