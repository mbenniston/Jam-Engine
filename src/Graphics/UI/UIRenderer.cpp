#include "jampch.h"
#include "UIRenderer.hpp"

static constexpr const char* VSOURCE_NAME = "shaders/ui.vert";
static constexpr const char* FSOURCE_NAME = "shaders/ui.frag";
static constexpr const char* TESTTEX_NAME = "test.png";

namespace Jam
{
    void UIRenderer::renderWidget(WidgetPtr widget) {
        m_shader.loadUniform("u_m", widget->getTransform());
        m_quad.drawUnbound();

        //TODO: ALL of this should be changed as it is in-efficient and ugly, replace with freetype / proper bitmaps
        auto text = std::dynamic_pointer_cast<LabelWidget>(widget);
        if(text) {
            //draw text
            m_shader.loadSubroutines(GL_VERTEX_SHADER, { "TexAtlasMethod" });
            m_shader.loadSubroutines(GL_FRAGMENT_SHADER, { "GrayScaleSample" });
            m_shader.loadUniform("u_color", text->getTextColor());
            
            int xi = widget->getPixelPos().x;
            int yi = widget->getPixelPos().y;
            for(char c : text->getText()) {
                if(c != '\n'){
                    m_shader.loadUniform("u_texTrans", glm::vec2{(float)c, 0});
                    m_shader.loadUniform("u_m", glm::translate<float>(glm::mat4(1.0f), {xi,yi,0}) * glm::scale<float>(glm::mat4(1.0f), {32,32,1}));
                    m_quad.drawUnbound();

                    xi += 32;
                } else {
                    yi+=32;
                    xi = widget->getPixelPos().x;
                }
            }
            
            m_shader.loadSubroutines(GL_FRAGMENT_SHADER, { "DefaultTexSample" });
            m_shader.loadSubroutines(GL_VERTEX_SHADER, { "DefaultTexMethod" });
        }
    }

    void UIRenderer::renderFrame(Frame* frame) {
        if(!frame->visible()) return;

        for(WidgetPtr child : frame->getChildren()) {
            FramePtr fp = std::dynamic_pointer_cast<Frame>(child);
            if(fp) {
                renderFrame(fp.get());
            } else {
                renderWidget(child);
            }
        }
    }

    void UIRenderer::renderUI(Frame* root) {
        m_cam.setWidth(root->getPixelSize().x);
        m_cam.setHeight(root->getPixelSize().y);

        m_shader.use();
        
        m_shader.loadUniform("texture0", (int)0);
        m_shader.loadUniform("fontAtlas", (int)1);
        m_texture.bind(0);
        m_font.getTexture().bind(1);

        m_shader.loadUniform("u_texScale", m_font.getAtlas().scale);
        m_shader.loadUniform("u_vp", m_cam.getProjectionMatrix());
        m_shader.loadSubroutines(GL_VERTEX_SHADER, { "DefaultTexMethod" });
        m_shader.loadSubroutines(GL_FRAGMENT_SHADER, { "DefaultTexSample" });

        m_quad.bind();

        renderFrame(root);

        m_texture.unbind();

        m_quad.unbind();
        m_shader.dispose();
    }

    UIRenderer::UIRenderer() {
        m_shader.loadFromFile(Jam::DEFAULT_ASSETS.openFile(VSOURCE_NAME), Jam::DEFAULT_ASSETS.openFile(FSOURCE_NAME));
        m_quad.create(1,1,false);
        m_cam.setPosition({0,0});
        m_texture.loadFromFile(Jam::DEFAULT_ASSETS.openFile(TESTTEX_NAME));
        m_font.init();
    }

    void UIRenderer::release() {
        m_shader.release();
        m_quad.release();
        m_texture.release();
        m_font.release();
    }
}