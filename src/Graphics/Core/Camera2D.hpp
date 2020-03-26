#pragma once
#include "vendor.h"
#include <iostream>

#include "../../misc.hpp"

namespace Jam
{

    class Camera2D
    {
    protected:
        glm::vec2 m_position;
        int m_width, m_height;

    public:

        bool inView(float x, float y, float w, float h) const {
            return rectInRect(x, y, w, h, m_position.x, m_position.y, m_width, m_height);
        }

        inline void setWidth(float width) {
            m_width = width;
        }

        inline void setHeight(float height) {
            m_height = height;
        }

        inline float getWidth() const {
            return m_width;
        }

        inline float getHeight() const {
            return m_height;
        }

        inline void setPosition(const glm::vec2& pos) {
            m_position = pos;
        }

        inline glm::vec2 getPosition() const {
            return m_position;
        }

        glm::mat4 getViewMatrix() const {
            return glm::translate(glm::mat4(1.0f), -glm::vec3(m_position, 0));
        }

        glm::mat4 getProjectionMatrix() const {
            return glm::ortho<float>(0, (float)m_width, (float)m_height, 0);
        }
    };

}