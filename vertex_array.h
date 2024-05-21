#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"

class VertexArray {
private:
	unsigned int id_;

public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();
	void AddBuffer(const VertexBuffer& vb);

	unsigned int GetId() { return id_; }
};