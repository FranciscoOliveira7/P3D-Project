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
#include "world_transform.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"

using namespace glm;

namespace objr {

	typedef struct Material {
		vec3 ambient;    // Ka
		vec3 specular;   // ke
		float shininess; // Expoente de reflexão especular

		// default material
		Material() : ambient(vec3(0.0f)), specular(vec3(0.0f)), shininess(0.0f) {}
	} Material;

	class Model {
	public:
		void Delete() const;

		void SetShader(Shader shader) { shader_ = shader; }
		void SetCamera(Camera* camera) { camera_ = camera; }

		void Render(vec3 position, vec3 orientation);
		void Install();

		void Load(const std::string obj_model_filepath);

		void SetScale(float scale) { transform_.SetScale(scale); }
		void SetSpin(vec3 spin) { transform_.SetSpin(spin); }

	private:
		void LoadMaterial(const std::string mtl_model_path);
		void SetUniform();

		// Trata das transformações da matriz Model
		Transform transform_;

		Shader shader_;
		Material material_;

		// É usado um apontador em vez de um objeto para puder ser
		// reaproveitada a câmera ao inves de calcular a sua posição
		// por Model, como também, gasta menos memória visto que só há uma câmera
		Camera* camera_ = nullptr;

		// Utilizado apenas uma texture por objeto
		Texture texture_;

		VertexArray vao_;

		VertexBuffer vertex_buffer_;
		VertexBuffer uv_buffer_;
		VertexBuffer normal_buffer_;

		std::vector<vec3> vertices_;
		std::vector<vec2> uvs_;
		std::vector<vec3> normals_;
	};
}