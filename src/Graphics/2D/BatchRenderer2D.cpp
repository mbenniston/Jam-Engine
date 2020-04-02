#include "jampch.h"
#include "BatchRenderer2D.hpp"

namespace Jam
{
    void BatchRenderer2D::addQuad(glm::vec2 position, glm::vec2 size, glm::vec2 minTexCoord, glm::vec2 maxTexCoord, glm::vec3 color, GLuint texUnit)
    {
        addVertex(BatchRenderer2D::Vertex{ position, minTexCoord, color, texUnit });
        addVertex(BatchRenderer2D::Vertex{ position + glm::vec2(size.x, 0), glm::vec2(maxTexCoord.x, minTexCoord.y), color, texUnit });
        addVertex(BatchRenderer2D::Vertex{ position + size, maxTexCoord, color, texUnit });
        addVertex(BatchRenderer2D::Vertex{ position + size, maxTexCoord, color, texUnit });
        addVertex(BatchRenderer2D::Vertex{ position + glm::vec2(0, size.y), glm::vec2(minTexCoord.x, maxTexCoord.y), color, texUnit });
        addVertex(BatchRenderer2D::Vertex{ position, minTexCoord, color, texUnit });
    }

    void BatchRenderer2D::addVertex(BatchRenderer2D::Vertex v)
    {
        m_vertices.push_back(v);
        if(m_vertices.size() > m_maxVerts) {
            exit(1); //handle this later
        }
        m_dirtyBuffer = true;
    }
    
    void BatchRenderer2D::clear()
    {
        m_vertices.clear();
        m_dirtyBuffer = true;
    }

    void BatchRenderer2D::refreshBuffer()
    {
        m_vertexBuffer.bind();
        m_vertexBuffer.fill(m_vertices.data(), m_vertices.size() * sizeof(BatchRenderer2D::Vertex));
        m_vertexBuffer.unbind();

        m_dirtyBuffer = false;
    }

    void BatchRenderer2D::draw(const Camera2D& cam)
    {
        m_batchShader.use();
        m_batchShader.loadUniform("u_vp", cam.getProjectionMatrix() * cam.getViewMatrix());
        m_vertexArray.bind();
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        m_vertexArray.unbind();
        m_batchShader.dispose();
    }

    BatchRenderer2D::BatchRenderer2D(unsigned int initialNumVerts, bool staticBatch) : m_maxVerts(initialNumVerts), m_staticBatch(staticBatch)
    {
        m_vertexArray.gen();
        m_vertexArray.bind();

        m_vertexBuffer.gen();
        m_vertexBuffer.bind();
        m_vertexBuffer.setTarget(GL_ARRAY_BUFFER);
        m_vertexBuffer.reserve(initialNumVerts * sizeof(BatchRenderer2D::Vertex), staticBatch ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(BatchRenderer2D::Vertex, position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(BatchRenderer2D::Vertex, texCoord));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(BatchRenderer2D::Vertex, color));
        glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(BatchRenderer2D::Vertex, texUnit));

        m_vertexBuffer.unbind();

        m_vertexArray.unbind();

        m_batchShader.loadFromFile(DEFAULT_ASSETS.openFile("shaders/batch2d.vert"), DEFAULT_ASSETS.openFile("shaders/batch2d.frag"));
    }

    BatchRenderer2D::~BatchRenderer2D() 
    {

    }

    void BatchRenderer2D::release()
    {
        m_vertexArray.release();
        m_vertexBuffer.release();
        m_batchShader.release();
    }
}