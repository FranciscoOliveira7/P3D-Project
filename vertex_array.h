#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"

class VertexArray {
private:
	unsigned int id_ = 0;

public:
	void Create() {
		glGenVertexArrays(1, &id_);
		glBindVertexArray(id_);
	}

	void Delete() const {
		glDeleteVertexArrays(1, &id_);
	}

	void Bind() const {
		glBindVertexArray(id_);
	}

	void AddBuffer(const VertexBuffer& buffer) {
		buffer.Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}
};