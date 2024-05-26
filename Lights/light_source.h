#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include "../shader.h"

using namespace glm;

class LightSource {
public:
	void SetPosition(vec3 position) { position_ = position; }
private:
	vec3 position_ = vec3(0.0f);
	vec3 direction_ = vec3(0.0f, -1.0f, 0.0f);
};