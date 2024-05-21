#pragma once

#include <vector>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include "shader.h"
#include "model.h"
#include "camera.h"
#include "world_transform.h"

using namespace glm;

class Renderer {
public:
	//void Install(bool);
	void Load(const std::string &obj_model_filepath);

private:
	std::vector<vec3> vertexes;
	std::vector<vec3> colors;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
};