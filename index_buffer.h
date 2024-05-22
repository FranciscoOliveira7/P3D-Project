#pragma once

#include <GL/glew.h>

class IndexBuffer {
private:
	unsigned int id_ = 0;
	unsigned int count_ = 0;

public:
	void Create(const void* data, unsigned int count) {
		glGenBuffers(1, &id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, 0);
		count_ = count;
	}

	void Delete() {
		glDeleteBuffers(1, &id_);
	}

	void Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
	}

	unsigned int Count() const { return count_; }
};