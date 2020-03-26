#pragma once
#include "vendor.h"
#include "Widget.hpp"
#include "../Core/Shader.hpp"
#include "../Core/Quad.hpp"
#include "../Core/Camera2D.hpp"
#include "../Core/Texture.hpp"

namespace Jam
{
    class UIRenderer final
    {
    private:
        Shader m_shader;
        Quad m_quad;
        Camera2D m_cam;
        Texture m_texture;

        void renderWidget(WidgetPtr widget);
        void renderFrame(Frame* frame);

    public:

        void renderUI(Frame* root);

        UIRenderer();
        void release();
        ~UIRenderer() = default;

    };


}