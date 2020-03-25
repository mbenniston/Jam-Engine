#pragma once

#include "vendor.h"
#include "../../misc.hpp"

namespace Jam
{
	class VertexArray
	{
	private:
		GLuint m_id = 0;
	public:

		void bind() const;
		void unbind() const;
		void gen();
		void release();

		VertexArray() = default;
		virtual ~VertexArray() = default;
	};

}