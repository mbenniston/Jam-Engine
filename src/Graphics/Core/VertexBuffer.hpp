#pragma once

#include "vendor.h"
#include "../../misc.hpp"

namespace Jam
{
	class VertexBuffer
	{
	private:
		GLuint m_id = 0;
		GLenum m_target = GL_ARRAY_BUFFER;
	public:

		inline GLenum getTarget() const { return m_target; }
		inline void setTarget(GLenum target) { m_target = target; }

		void bind() const;
		void unbind() const;
		void gen();
		void release();

		void store(const void* const data, size_t length, GLenum usage = GL_STATIC_DRAW);
		void reserve(size_t length, GLenum usage = GL_STATIC_DRAW);
		void fill(const void* const data, size_t length);

		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;
	};

}