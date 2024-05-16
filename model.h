#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include "vertex_buffer.h"
#include "index_buffer.h"

typedef struct {
	glm::vec3 emissive;
	glm::vec3 ambient;  // Ka
	glm::vec3 diffuse;  // kd
	glm::vec3 specular; // ke
	float shininess;    // Expoente de reflex�o especular
} Material;

class Model {
public:
	~Model();

	void InitializeComponents(int num_buffers);

	void AttribPointer(int buffer, int size, unsigned int location);

	void Draw(void);

	void BindProgram(GLuint program);

	GLuint vao_ = 0; // Vertex array object
	GLuint program_ = 0;

	VertexBuffer* vertex_buffer_ = nullptr;
	VertexBuffer* color_buffer_ = nullptr;
	VertexBuffer* normal_buffer_ = nullptr;
	IndexBuffer* index_buffer_ = nullptr;

private:
	int num_buffers_ = 0;
	GLuint* buffers_ = nullptr; // Array dos VBOs / EBOs

};
