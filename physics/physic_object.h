#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include "collision_sphere.h"

using namespace glm;

class PhysicsObject {
public:
	PhysicsObject(vec3 position) : initial_pos_{ position }, collision_sphere_{ CollisionSphere(position) } { }

	PhysicsObject(vec3 position, float radius)
		: initial_pos_{ position }, collision_sphere_{ CollisionSphere(position, radius) } {}

	void Update(std::vector<PhysicsObject>& others, float deltaTime);

	void ResetPosition() { collision_sphere_.position_ = initial_pos_; }
	void Stop() { velocity_ = vec3(0.0f); }
	void SetPosition(vec3 position) {
		initial_pos_ = position;
		collision_sphere_.position_ = position;
	}
	void SetVelocity(vec3 velocity) { velocity_ = velocity; }
	void AddVelocity(vec3 velocity) { velocity_ += velocity; }
	vec3 GetPosition() const { return collision_sphere_.position_; }
	vec2 GetRotation() const { return rotation_; }

	CollisionSphere collision_sphere_;

private:
	vec2 rotation_ = vec3(0.0f);
	vec3 velocity_ = vec3(0.0f);
	vec3 initial_pos_;

	const float k_friction_ = 0.0005f;
};