#pragma once

#include "vertex_buffer.h"

namespace objr {

	class VertexArray {
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

		void AddBuffer(VertexBuffer buffer, int size, int location) const {

			// Neither stride nor initial offset is used for reading .obj files so I'll keep it simple
			buffer.Bind();
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, (void*) 0);
			glEnableVertexAttribArray(location);
		}
	};
}