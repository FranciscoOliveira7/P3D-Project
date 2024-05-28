#pragma once

#include "vertex_buffer.h"

namespace objr {

	class VertexArray {
	private: unsigned int id_ = 0;

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
	};
}