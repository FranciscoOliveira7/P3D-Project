#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include "vertex_array.h"
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
	void Delete();

	void AttribPointer() const;

	VertexArray vao_;

	VertexBuffer* vertex_buffer_ = nullptr;
	VertexBuffer* color_buffer_  = nullptr;
	VertexBuffer* normal_buffer_ = nullptr;
	IndexBuffer* index_buffer_   = nullptr;
private:
	Material material;
};
