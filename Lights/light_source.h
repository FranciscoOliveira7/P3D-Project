#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include "../shader.h"

using namespace glm;

namespace AsBolasDoJose {

	class LightSource {
	public:
		virtual void Update() = 0;
		virtual void Disable() = 0;

		void Toggle() {
			if (enabled_) Disable();
			else Update();
		}
		void SetShader(Shader shader) { shader_ = shader; }

	protected:
		Shader shader_;

		vec3 ambient_ = vec3(0.0f, 0.0f, 0.0f);

		bool enabled_ = true;
	};
}