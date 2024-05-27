#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include "../shader.h"

using namespace glm;

class LightSource {
public:
	virtual void Update() = 0;
	virtual void Disable() = 0;

	void Toggle() {
		if (enabled_) Disable();
		else Update();
	}
	void SetShader(Shader shader) { shader_ = shader; }

	void SetPosition(vec3 position) { position_ = position; }
protected:
	Shader shader_;
	vec3 position_ = vec3(0.0f);
	vec3 direction_ = vec3(0.0f, -1.0f, 0.0f);

	vec3 ambient_;

	bool enabled_ = true;
};