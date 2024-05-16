#pragma once

#include <vector>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "model.h"
#include "camera.h"

using namespace glm;

struct ObjectData {

	std::vector<vec3> vertices;
	std::vector<vec3> colors;
	std::vector<vec3> normals;
	std::vector<GLuint> indexes;
};

class Renderer {
public:
	void BindModel(Model* model);

	void Render(vec3 position, vec3 orientation);
	void Install(void);
	void Load(const std::string obj_model_filepath);

	void SetCameraPosition(float x, float y, float z) { camera_.SetPosition(x, y, z); }

	//void TestData(void) {
	//	for (int i = 0; i < 8 * 3; i += 3)
	//	{
	//		data_.vertices.push_back(vec3(vertices[i], vertices[i + 1], vertices[i + 2]));
	//	}
	//	for (int i = 0; i < 8 * 3; i += 3)
	//	{
	//		data_.colors.push_back(vec3(cores[i], cores[i + 1], cores[i + 2]));
	//	}
	//}

private:
	Model* model_;
	Camera camera_;

	ObjectData data_;

	mat4 projection = perspective(radians(45.0f), (float)(640 / 480), 1.0f, 100.0f);
};