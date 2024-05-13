#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

class Model {
public:
	Model(int num_vbos);
	~Model();

	bool BufferStorage(int buffer, GLfloat *data, GLsizeiptr size);

private:
	GLuint vao_;
	int num_buffers_;
	GLuint *buffers_; // Array dos VBOs / EBOs
};
