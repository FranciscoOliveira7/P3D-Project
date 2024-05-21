#include "index_buffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : count_{ count }
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id_);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}