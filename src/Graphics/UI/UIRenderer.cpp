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
    }

    void UIRenderer::renderFrame(Frame* frame) {
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

        m_texture.bind();

        m_shader.use();
        m_shader.loadUniform("u_vp", m_cam.getProjectionMatrix());
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
    }

    void UIRenderer::release() {
        m_shader.release();
        m_quad.release();
    }
}