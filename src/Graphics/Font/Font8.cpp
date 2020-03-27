#include "jampch.h"
#include <array>
#include <algorithm>

#include "Font8.hpp"

static constexpr const char* FONT_VSOURCE_PATH = "shaders/font8.vert";
static constexpr const char* FONT_FSOURCE_PATH = "shaders/font8.frag";

extern "C"
{
    #include "font8x8_basic.h"
}

namespace Jam
{
    std::array<unsigned char, 64> decodeChar(unsigned char* encodedChar)
    {
        std::array<unsigned char, 64> texture_data;

        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(encodedChar[i] & (1 << j)) {
                    texture_data[j + i * 8] = 255;
                } else {
                    texture_data[j + i * 8] = 0;
                }
            }
        }
        return texture_data;
    }

    void Font8::init() 
    {
        std::array<std::array<unsigned char, 64>, 128> char_maps;

        for(int i = 0; i < 128; i++) {
            char_maps[i] = decodeChar(font8x8_basic[i]);
        }

        std::array<unsigned char, 128 * 64> font_texture_data;

        //stitch texture together
        for(int r = 0; r < 8; r++) {
            for(int i = 0; i < 128; i++) {
                auto char_data = char_maps[i];
                for(int j = 0; j < 8; j++){
                    font_texture_data[j + (i * 8) + r * 128*8] = char_data[j + r * 8];
                }
            }
        }

        m_texture.loadFromArray(font_texture_data.data(), 128 * 8, 8, GL_RED, GL_RED, GL_UNSIGNED_BYTE);
        m_fontAtlas = TextureAtlas(128 * 8, 8, 8, 8);
    }

    void Font8::release() 
    {
        m_texture.release();
    }

    Font8::Font8()
    {

    }

    Font8::~Font8()
    {

    }

    void Font8Renderer::start(const Camera2D& view) 
    {
        m_fontShader.use();
        m_quad.bind();
        m_font.getTexture().bind();
        m_fontShader.loadUniform("u_vp", view.getProjectionMatrix() * view.getViewMatrix());
        m_fontShader.loadUniform("u_texScale", m_font.getAtlas().scale);
        m_fontShader.loadUniform("texture0", (int)0);
        setColor({1,1,1});
    } 

    void Font8Renderer::drawChar(char c, int x, int y, int w, int h) 
    {
        m_fontShader.loadUniform("u_texTrans", glm::vec2{(float)c, 0});
        m_fontShader.loadUniform("u_m", glm::translate<float>(glm::mat4(1.0f), {x,y,0}) * glm::scale<float>(glm::mat4(1.0f), {w,h,1}));
        m_quad.drawUnbound();
    } 

    void Font8Renderer::setColor(glm::vec3 color)
    {
        m_fontShader.loadUniform("u_color", color);
    }

    void Font8Renderer::drawText(const std::string& str, int x, int y, int w, int h) 
    {
        int xi = x;
        int yi = y;
        for(char c : str) {
            if(c != '\n'){
                drawChar(c, xi, yi, w, h);
                xi += w;
            } else {
                yi+=h;
                xi = x;
            }
        }
    } 

    void Font8Renderer::stop() 
    {
        m_fontShader.dispose();
        m_quad.unbind();
        m_font.getTexture().unbind();
    } 

    void Font8Renderer::init() 
    {
        m_fontShader.loadFromFile(Jam::DEFAULT_ASSETS.openFile(FONT_VSOURCE_PATH), Jam::DEFAULT_ASSETS.openFile(FONT_FSOURCE_PATH));
        m_quad.create(1,1);
        m_font.init();
    } 

    void Font8Renderer::release() 
    {
        m_font.release();
        m_quad.release();
        m_fontShader.release();
    } 

    Font8Renderer::Font8Renderer() 
    {

    } 

    Font8Renderer::~Font8Renderer() 
    {

    } 

}