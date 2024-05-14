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

	glBindBuffer(type, buffers_[buffer]);
	glBufferStorage(type, buffer==0 || buffer==1 ? sizeof(float) * 24 : sizeof(int) * 36, data, 0);

	return true;
}

unsigned int Model::GetInputLocation(int program, const std::string& name) {

	return glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, name.c_str());
}

void Model::AttribPointer(int buffer, unsigned int location, int size) {

	glBindBuffer(GL_ARRAY_BUFFER, buffers_[buffer]);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}

void Model::Draw(void) {
	glBindVertexArray(vao_);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}