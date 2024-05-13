#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <string>

const GLfloat vertices[8 * 3] = {
	-9.0f,  0.5f,  5.5f,  9.0f,  0.5f,  5.5f,
	-9.0f, -0.5f,  5.5f,  9.0f, -0.5f,  5.5f,

	-9.0f,  0.5f, -5.5f,  9.0f,  0.5f, -5.5f,
	-9.0f, -0.5f, -5.5f,  9.0f, -0.5f, -5.5f
};

typedef struct {
	GLenum type;
	GLuint shader;
} BufferInfo;

class Model {
public:
	Model(void);
	Model(int num_vbos);
	~Model();

	void InitializeComponents(int num_buffers);

	bool BufferStorage(GLenum type, int buffer, const void* data, GLsizeiptr size);
	unsigned int GetInputLocation(int program, const std::string& name);
	void AttribPointer(unsigned int location, int size);

	void Draw(void);

private:
	GLuint vao_ = 0;
	int num_buffers_ = 0;
	GLuint *buffers_ = nullptr; // Array dos VBOs / EBOs
};
