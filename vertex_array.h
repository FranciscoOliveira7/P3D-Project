#pragma once

#include "vertex_buffer.h"

namespace objr {

	// VAO
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

			// Visto que estão a ser utilizados o std::vector posições, uvs e normais separadamente
			// na leitura dos ficheiros .obj,
			// o stride e o offset inicial (pointer) vão ser sempre 0.
			buffer.Bind();
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, (void*) 0);
			glEnableVertexAttribArray(location);
		}
	};
}