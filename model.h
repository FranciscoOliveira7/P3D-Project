#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <string>

#include "world_transform.h"

struct {
	glm::vec3 emissive;
	glm::vec3 ambient; // Ka
	glm::vec3 diffuse; // kd
	glm::vec3 specular; // ke
	float shininess; // Expoente de reflexão especular
} typedef Material;

class Model {
public:
	~Model();

	void InitializeComponents(int num_buffers);

	bool BufferStorage(GLenum type, int buffer, const void* data, GLsizeiptr size);
	unsigned int GetInputLocation(int program, const std::string& name);
	void AttribPointer(int buffer, int size, unsigned int location);

	void Draw(void);

	void BindProgram(GLuint program);

	GLuint program_ = 0;
	GLuint vao_;         // Vertex array object

private:
	int num_buffers_ = 0;
	GLuint* buffers_ = nullptr; // Array dos VBOs / EBOs

	GLuint index_size_ = 0; // Numero de Indices
};
