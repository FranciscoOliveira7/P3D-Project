#pragma once

#include <GL/glew.h>

class IndexBuffer {
private:
	unsigned int id_ = 0;
	unsigned int count_ = 0;

public:
	void Create(const void* data, unsigned int count);
	void Delete();

	void Bind() const;

	unsigned int Count() const { return count_; }
};