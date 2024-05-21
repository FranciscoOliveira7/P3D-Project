#pragma once

#include <GL/glew.h>

class VertexBuffer {
private:
	unsigned int id_;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};