#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"

class VertexArray {
private:
	unsigned int id_ = 0;

public:
	void Create();
	void Delete();

	void Bind();
	void Unbind();
	void AddBuffer(const VertexBuffer& vb);

	unsigned int GetId() const { return id_; }
};