#include "vertex_buffer.h"

void VertexBuffer::Create(const void* data, GLsizeiptr size)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, id_);
	glBufferStorage(GL_ARRAY_BUFFER, size, data, 0);
}

void VertexBuffer::Delete()
{
	glDeleteBuffers(1, &id_);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id_);
}
