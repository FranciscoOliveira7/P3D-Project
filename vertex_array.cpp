#include "vertex_array.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id_);
	glBindVertexArray(id_);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id_);
}

void VertexArray::Bind()
{
	glBindVertexArray(id_);
}

void VertexArray::AddBuffer(const VertexBuffer& vb)
{
	vb.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
