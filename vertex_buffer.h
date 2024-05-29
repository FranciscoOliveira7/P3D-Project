#pragma once

#include <GL/glew.h>

namespace objr {

	class VertexBuffer {
		unsigned int id_ = 0;

	public:
		void Create(const void* data, GLsizeiptr size) {
			glGenBuffers(1, &id_);
			glBindBuffer(GL_ARRAY_BUFFER, id_);
			glBufferStorage(GL_ARRAY_BUFFER, size, data, 0);
		}

		void Delete() const {
			glDeleteBuffers(1, &id_);
		}

		void Bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, id_);
		}
	};
}