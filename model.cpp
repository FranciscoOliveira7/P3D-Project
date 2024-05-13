#include "model.h"

Model::Model(void) { }
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

/// <summary>
///	Stores data to Buffer Object
/// </summary>
/// <returns>
/// data stored with success
/// </returns>
bool Model::BufferStorage(GLenum type, int buffer, const void* data, GLsizeiptr size) {
	// Check if the index is valid
	if (buffer < 0 || buffer > num_buffers_) return false;

	if (buffer == 0) {
		glBindBuffer(type, buffers_[0]);
		glBufferStorage(type, sizeof(vertices), vertices, 0);
	}
	else {
		glBindBuffer(type, buffers_[buffer]);
		glBufferStorage(type, size, data, 0);
	}

	return true;
}

unsigned int Model::GetInputLocation(int program, const std::string& name) {

	return glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, name.c_str());
}

void Model::AttribPointer(unsigned int location, int size) {

	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}

void Model::Draw(void) {
	glBindVertexArray(vao_);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}