#include "model.h"

Model::~Model() {
	delete[] buffers_;
}

/// <summary>
///	Initializes the VAO and the Buffer Objects
/// </summary>
void Model::InitializeComponents(int num_buffers) {
	if (num_buffers_ != 0) return;

	num_buffers_ = num_buffers;

	// Creates vao for the Model
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	// Alocate space to store Buffer Object's names
	buffers_ = new GLuint[num_buffers_];

	// Generate Buffer Object names
	glGenBuffers(num_buffers_, buffers_);
}

void Model::AttribPointer(int buffer, int size, unsigned int location) {

	//glBindBuffer(GL_ARRAY_BUFFER, buffers_[buffer]);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}