#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include <string>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_inverse.hpp> // inverseTranspose()

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
	vec3 ambient;  // Ka
	vec3 diffuse;  // kd
	vec3 specular; // ke
	float shininess;    // Expoente de reflexão especular

	// default material
	//Material() : ambient(vec3(0.0f)), diffuse(vec3(0.0f)), specular(vec3(0.0f)), shininess(0.0f) {}
} Material;

class Model {
public:
	void Delete() const;

	void SetShader(Shader shader) { shader_ = shader; }

	void Render(vec3 position, vec3 orientation);
	void Install();

	void Load(const std::string obj_model_filepath);

	void SetCameraPosition(float x, float y, float z) { camera_.SetPosition(x, y, z); }
	void SetCameraFov(float fov) { camera_.SetFov(fov); }

	void SetScale(float scale) { world_.SetScale(scale); }
private:
	void SetMaterialUniforms();
	void AttribPointer() const;

	void LoadMaterial(const std::string mtl_model_path);

	WorldTrans world_;

	Shader shader_;
	Material material_;
	Camera camera_;

	Texture texture_;

	VertexArray vao_;

	VertexBuffer vertex_buffer_;
	VertexBuffer uv_buffer_;
	VertexBuffer normal_buffer_;

	std::vector<vec3> vertices_;
	std::vector<vec2> uvs_;
	std::vector<vec3> normals_;
};
