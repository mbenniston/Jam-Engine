#pragma once
#include "../Core/VertexBuffer.hpp"
#include "../Core/VertexArray.hpp"
#include "../Core/Shader.hpp"
#include "../Core/Camera2D.hpp"

namespace Jam
{
    class BatchRenderer2D 
    {
    public:
        struct Vertex
        {
            glm::vec2 position, texCoord;
            glm::vec3 color;
            GLuint texUnit;
        };

    private:
        Shader m_batchShader;
        VertexArray m_vertexArray;
        VertexBuffer m_vertexBuffer;
        unsigned int m_maxVerts, m_numVerts = 0;
        std::vector<Vertex> m_vertices;
        bool m_dirtyBuffer = false;

    public:

        bool isBufferDirty() const {
            return m_dirtyBuffer;
        }

        void addVertex(Vertex v);
        void addQuad(glm::vec2 position, glm::vec2 size, glm::vec2 minTexCoord, glm::vec2 maxTexCoord, glm::vec3 color, GLuint texUnit);
        void clear();

        void draw(const Camera2D& cam);

        void refreshBuffer();

        void release();

        BatchRenderer2D(unsigned int initialNumVerts);
        virtual ~BatchRenderer2D();
    };

}