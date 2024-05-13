#include "model.h"

Model::Model(int num_vbos) : num_buffers_{ num_vbos } {

	// Creates vao for the Model
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	// Alocate space to store Buffer Object's names
	buffers_ = new GLuint[num_buffers_];

	// Generate Buffer Object names
	glGenBuffers(num_buffers_, buffers_);
}

Model::~Model() {
	delete[] buffers_;
}

/// <summary>
///	Stores data to Buffer Object
/// </summary>
/// <returns>
/// data stored with success
/// </returns>
bool Model::BufferStorage(int buffer, GLfloat* data, GLsizeiptr size) {
	// Check if the index is valid
	if (buffer < 0 || buffer > num_buffers_) return false;

	glBindBuffer(GL_ARRAY_BUFFER, buffers_[buffer]);
	glBufferStorage(GL_ARRAY_BUFFER, size, data, 0);

	return true;
}
