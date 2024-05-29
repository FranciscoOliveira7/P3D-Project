#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include "collision_box.h"

using namespace glm;

class PhysicsObject {
public:
	PhysicsObject(vec3 position) : initial_pos_{ position } { collision_box_.position_ = position; }

	PhysicsObject(vec3 position, vec2 size)
		: initial_pos_{ position }, rotation_{ vec2(0.0f) }, collision_box_{ CollisionBox(position, size) } {}

	void Update(std::vector<PhysicsObject>& others, float deltaTime) {

		if (velocity_ != vec3(0.0f)) {
			for (PhysicsObject& collider : others) {
				if (this == &collider) continue;

				vec3 collision;
				if (collision_box_.ComputeCollision(collider.collision_box_, collision)) {
					//velocity_ = vec3(0.0f);
					velocity_ *= collision;
				}
			}
		}

		const vec3 delta_vel = velocity_ * deltaTime;
		collision_box_.position_ += delta_vel;
		velocity_ -= delta_vel * k_friction_;
		rotation_.x += -delta_vel.z;
		rotation_.y += -delta_vel.x;
	}

	void ResetPosition() { collision_box_.position_ = initial_pos_; }
	void Stop() { velocity_ = vec3(0.0f); }
	void SetVelocity(vec3 velocity) { velocity_ = velocity; }
	void AddVelocity(vec3 velocity) { velocity_ += velocity; }
	vec3 GetPosition() { return collision_box_.position_; }
	vec2 GetRotation() { return rotation_; }

private:
	vec2 rotation_ = vec3(0.0f);
	vec3 velocity_ = vec3(0.0f);
	CollisionBox collision_box_;
	vec3 initial_pos_;

	const float k_friction_ = 0.0005f;
};