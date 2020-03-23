#pragma once
#include <vector>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

namespace Jam
{

    class Mesh
    {
    public:
        struct AttachPoint {
            VertexBuffer vbo;
            GLuint attribID;
            int size;
            GLenum dataType;
            //stride
            //offset
        };

    private:
        VertexArray m_vertexArray;

        std::vector<AttachPoint> m_attachPoints;
        unsigned int m_vertexCount;
        GLenum m_primType;

    public:

        inline const std::vector<AttachPoint>& getAttachPoints() {
            return m_attachPoints;
        }

        inline void setPrimitiveType(GLenum type) {
            m_primType = type;
        }

        inline GLenum getPrimitiveType() const {
            return m_primType;
        }

        inline void setVertexCount(unsigned int v) {
            m_vertexCount = v;
        }

        inline unsigned int getVertexCount() const {
            return m_vertexCount;
        }

        void attachBuffer(const VertexBuffer& vbuffer, GLuint attribID, int size, GLenum dataType);
        void complete();

        virtual void bind() const;
        virtual void unbind() const;
        virtual void draw() const;
        virtual void drawUnbound() const;
        virtual void release();
    };
}