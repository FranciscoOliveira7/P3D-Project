#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include <string>
#include <sstream>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "world_transform.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"

// Library used for image loading

using namespace glm;

typedef struct Material {
	std::string name;

	glm::vec3 ambient;  // Ka
	glm::vec3 diffuse;  // kd
	glm::vec3 specular; // ke
	float shininess;    // Expoente de reflex�o especular

	Material() : name("N/A"), ambient(glm::vec3(0.0f)), diffuse(glm::vec3(0.0f)), specular(glm::vec3(0.0f)), shininess(0.0f) {}
} Material;

class Model {
public:
	void BindShader(Shader shader) { shader_ = shader; }
	void Delete();

	void Render(vec3 position, vec3 orientation);
	void Install(bool);
	void AttribPointer() const;

	void Load(const std::string& obj_model_filepath);

	void LoadMaterial(const std::string& mtl_model_path);

	void SetCameraPosition(float x, float y, float z) { camera_.SetPosition(x, y, z); }
	void SetCameraFov(float fov) { camera_.SetFov(fov); }

	void SetScale(float scale) { world_.SetScale(scale); }

	bool has_no_texture_;
private:

	WorldTrans world_;

	Shader shader_;
	Material material_;
	Camera camera_;

	Texture texture_;

	VertexArray vao_;

	VertexBuffer vertex_buffer_;
	VertexBuffer color_buffer_;
	VertexBuffer uv_buffer_;
	VertexBuffer normal_buffer_;
	IndexBuffer index_buffer_;

	std::vector<vec3> vertexes;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
};
