#include "vertex_array.h"

void VertexArray::Create()
{
	glGenVertexArrays(1, &id_);
	glBindVertexArray(id_);
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &id_);
}

void VertexArray::Bind()
{
	glBindVertexArray(id_);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb)
{
	vb.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
