#include "index_buffer.h"

void IndexBuffer::Create(const void* data, unsigned int count)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, 0);
	count_ = count;
}

void IndexBuffer::Delete()
{
	glDeleteBuffers(1, &id_);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}
