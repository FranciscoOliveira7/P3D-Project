#pragma once

#include <GL/glew.h>

class VertexBuffer {
private:
	unsigned int id_;

public:
	void Create(const void* data, GLsizeiptr size);
	void Delete();

	void Bind() const;
};