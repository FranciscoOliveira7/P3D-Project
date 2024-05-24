#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm\gtc\matrix_inverse.hpp> // glm::inverseTranspose()
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

	void SetScale(float scale) { transform_.SetScale(scale); }

private:

	WorldTrans transform_;

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
