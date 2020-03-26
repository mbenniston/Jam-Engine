#include "jampch.h"
#include "Quad.hpp"

namespace Jam
{

    void Quad::create(float width, float height, bool symetric)
    {
        float minWidth = symetric ? -width : 0;
        float minHeight = symetric ? -height : 0;

        float vertices[] = {
            minWidth,minHeight,
            width,minHeight,
            width,height,
            width,height,
            minWidth,height,
            minWidth,minHeight
        };

        static float texCoords[] = {
            0,0,
            1,0,
            1,1,
            1,1,
            0,1,
            0,0,
        };

        m_vbo.gen();
        m_vbo.setTarget(GL_ARRAY_BUFFER);
        m_vbo.bind();
        m_vbo.store(vertices, sizeof(vertices));
        m_vbo.unbind();
        attachBuffer(m_vbo, 0, 2, GL_FLOAT);

        m_tbo.gen();
        m_tbo.setTarget(GL_ARRAY_BUFFER);
        m_tbo.bind();
        m_tbo.store(texCoords, sizeof(texCoords));
        m_tbo.unbind();
        attachBuffer(m_tbo, 1, 2, GL_FLOAT);

        complete();

        setVertexCount(6);
        setPrimitiveType(GL_TRIANGLES);
    }

    void Quad::release()
    {
        m_vbo.release();
        m_tbo.release();
        Mesh::release();
    }

}