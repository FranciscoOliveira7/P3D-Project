#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include "collision_box.h"

using namespace glm;

class PhysicsObject {
public:
	PhysicsObject() : position_{ vec3(0.0f) }, velocity_{ vec3(0.0f) }, rotation_{ vec2(0.0f) } {}

	PhysicsObject(vec3 position) : position_{ position }, velocity_{ vec3(0.0f) }, rotation_{ vec2(0.0f) } {}

	void Update(float deltaTime) {
		vec3 deltaVelocity = velocity_ * deltaTime;

		position_ += deltaVelocity;
		velocity_ -= velocity_ * k_friction_ * deltaTime;
		//rotation_.x += deltaVelocity.z;
		rotation_.y += -deltaVelocity.x;
	}
	vec3 position_;
	vec2 rotation_;
	vec3 velocity_;

private:
	CollisionBox collision_box_;
	const float k_friction_ = 0.0005f;
};