#include "jampch.h"
#include "VertexArray.hpp"

void Jam::VertexArray::bind() const
{
	glBindVertexArray(m_id);
}

void Jam::VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void Jam::VertexArray::gen()
{
	MISC_CHECK_GEN_ID(m_id);
	glGenVertexArrays(1, &m_id);
}

void Jam::VertexArray::remove()
{
	MISC_CHECK_REM_ID(m_id);
	glDeleteVertexArrays(1, &m_id);
	m_id = 0;
}
