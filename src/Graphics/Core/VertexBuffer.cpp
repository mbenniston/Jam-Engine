#include "jampch.h"
#include "VertexBuffer.hpp"

void Jam::VertexBuffer::bind() const
{
	glBindBuffer(m_target, m_id);
}

void Jam::VertexBuffer::unbind() const
{
	glBindBuffer(m_target, 0);
}

void Jam::VertexBuffer::gen()
{
	MISC_CHECK_GEN_ID(m_id);
	glGenBuffers(1, &m_id);
}

void Jam::VertexBuffer::release()
{
	MISC_CHECK_REM_ID(m_id);
	glDeleteBuffers(1, &m_id);
	m_id = 0;
}

void Jam::VertexBuffer::store(const void* const data, size_t length, GLenum usage)
{
	glBufferData(m_target, length, data, usage);
}

void Jam::VertexBuffer::reserve(size_t length, GLenum usage)
{
	glBufferData(m_target, length, nullptr, usage);
}

void Jam::VertexBuffer::fill(const void* const data, size_t length)
{
	glBufferSubData(m_target, 0, length, data);
}

