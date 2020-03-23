#include "jampch.h"
#include "Mesh.hpp"

namespace Jam
{

    void Mesh::attachBuffer(const VertexBuffer& vbuffer, GLuint attribID, int size, GLenum dataType) {
        //when a buffer is attached these two operations must happen

        AttachPoint attachPoint{
            vbuffer,
            attribID,
            size,
            dataType
        };

        m_attachPoints.push_back(attachPoint);
    }

    void Mesh::complete() {
        m_vertexArray.gen();
        m_vertexArray.bind();

        for (AttachPoint point : m_attachPoints) {
            point.vbo.bind();
            glVertexAttribPointer(point.attribID, point.size, point.dataType, GL_FALSE, 0, nullptr);
            point.vbo.unbind();
        }
        m_vertexArray.unbind();
    }

    void Mesh::bind() const {
        m_vertexArray.bind();
        for (AttachPoint point : m_attachPoints) {
            glEnableVertexAttribArray(point.attribID);
        }
    }

    void Mesh::unbind() const {
        for (AttachPoint point : m_attachPoints) {
            glDisableVertexAttribArray(point.attribID);
        }

        m_vertexArray.unbind();
    }

    void Mesh::draw() const {
        bind();
        drawUnbound();
        unbind();
    }

    void Mesh::drawUnbound() const {
        glDrawArrays(m_primType, 0, m_vertexCount);
    }

    void Mesh::release() {
        m_vertexArray.release();
        m_attachPoints.clear();
    }

}