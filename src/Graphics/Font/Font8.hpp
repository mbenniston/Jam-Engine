#pragma once

#include "../Core/Texture.hpp"
#include "../Core/TextureAtlas.hpp"
#include "../Core/Quad.hpp"
#include "../Core/Shader.hpp"
#include "../Core/Camera2D.hpp"

/*
    Very simple to use 8-bit bitmap font renderer
*/

namespace Jam
{
    class Font8 final
    {
    private:
        Texture m_texture;
        TextureAtlas m_fontAtlas;
    public:

        const Texture& getTexture() const {
            return m_texture;
        }

        const TextureAtlas& getAtlas() const {
            return m_fontAtlas;
        }

        void init();
        void release();

        Font8();
        ~Font8();
    };

    class Font8Renderer final
    {
    private:
        Quad m_quad;
        Font8 m_font;
        Shader m_fontShader;

    public:

        void start(const Camera2D& view);
        void setColor(glm::vec3 color);
        void drawChar(char c, int x, int y, int w, int h);
        void drawText(const std::string& str, int x, int y, int w, int h);
        void stop();

        void init();
        void release();

        Font8Renderer();
        ~Font8Renderer();

    };
}