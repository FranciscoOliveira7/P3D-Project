#pragma once

#include <GL/glew.h>

class IndexBuffer {
private:
	unsigned int id_;
	unsigned int count_;

public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;

	void Unbind() const;

	unsigned int Count() const { return count_; }
};