#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include "collision_box.h"

using namespace glm;

class PhysicsObject {
public:
	PhysicsObject(vec3 position) { collision_box_.position_ = position; }

	PhysicsObject(vec3 position, vec3 size)
		: rotation_{ vec2(0.0f) }, collision_box_{ CollisionBox(position, size) } {}

	void Update(std::vector<PhysicsObject>& others, float deltaTime) {

		if (velocity_ != vec3(0.0f)) {
			for (PhysicsObject& collider : others) {
				if (this == &collider) continue;

				if (collision_box_.ComputeCollision(collider.collision_box_)) {
					//velocity_ = vec3(0.0f);
					velocity_.x = -velocity_.x;
				}
			}
		}

		collision_box_.position_ += velocity_ * deltaTime;
		velocity_ -= velocity_ * k_friction_ * deltaTime;
		rotation_.x += (-velocity_ * deltaTime).z;
		rotation_.y += (-velocity_ * deltaTime).x;
	}
	vec2 rotation_ = vec3(0.0f);
	vec3 velocity_ = vec3(0.0f);
	CollisionBox collision_box_;

private:
	const float k_friction_ = 0.0005f;
};