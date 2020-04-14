#pragma once
#include "../Core/VertexBuffer.hpp"
#include "../Core/VertexArray.hpp"
#include "../Core/Shader.hpp"
#include "../Core/Camera2D.hpp"
#include "../Core/Texture.hpp"

namespace Jam
{
    class BatchRenderer2D 
    {
    public:
        struct Vertex
        {
            glm::vec2 position, texCoord;
            glm::vec3 color;
            GLfloat texUnit;
        };

    private:
        Shader m_batchShader;
        VertexArray m_vertexArray;
        VertexBuffer m_vertexBuffer;
        unsigned int m_maxVerts;
        std::vector<Vertex> m_vertices;
        std::vector<Texture> m_textures;

        bool m_dirtyBuffer = false;
        bool m_staticBatch = false;

    public:

        bool isBufferDirty() const {
            return m_dirtyBuffer;
        }

        void addVertex(Vertex v);
        void addQuad(glm::vec2 position, glm::vec2 size, glm::vec2 minTexCoord, glm::vec2 maxTexCoord, glm::vec3 color, Texture texture);
        void clear();

        void draw(glm::mat4 projViewMat = glm::mat4(1.0f));
        void draw(const Camera2D& cam);

        void refreshBuffer();

        void release();

        BatchRenderer2D(unsigned int initialNumVerts, bool staticBatch = false);
        virtual ~BatchRenderer2D();
    };

}