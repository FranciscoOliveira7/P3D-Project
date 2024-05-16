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
	float shininess;    // Expoente de reflexão especular
} Material;

class Model {
public:
	void AttribPointer(int size, unsigned int location);

	GLuint vao_ = 0; // Vertex array object

	VertexBuffer* vertex_buffer_ = nullptr;
	VertexBuffer* color_buffer_ = nullptr;
	VertexBuffer* normal_buffer_ = nullptr;
	IndexBuffer* index_buffer_ = nullptr;

private:

};
