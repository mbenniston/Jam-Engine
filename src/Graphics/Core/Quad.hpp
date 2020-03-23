#pragma once

#include "Mesh.hpp"

namespace Jam
{
    class Quad : public Mesh
    {
    private:
        VertexBuffer m_vbo, m_tbo;

    public:

        void create(float width, float height, bool symetric = false);

        virtual void release() override;

        Quad() = default;
        ~Quad() = default;
    };

}