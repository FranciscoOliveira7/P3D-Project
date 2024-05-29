#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <iostream>
#include <algorithm>

using namespace glm;


/// <summary>
/// Collision detection in a 2D place (y axis ignored)
/// </summary>
class CollisionBox {
public:
	CollisionBox() : position_{ vec3(0.0f) }, width_{ 1.0f }, depth_{ 1.0f } {};
	
	CollisionBox(vec3 position, vec2 size)
		: position_{ position }, width_{ size.x }, depth_{ size.y } {};

	bool ComputeCollision(CollisionBox& other, vec3& collision_vec) {
		float min_x = std::min<float>(position_.x - width_ / 2.0f,  other.position_.x - other.width_ / 2.0f);
		float max_x = std::max<float>(position_.x + width_ / 2.0f,  other.position_.x + other.width_ / 2.0f);
		float min_z = std::min<float>(position_.z - depth_ / 2.0f,  other.position_.z - other.depth_ / 2.0f);
		float max_z = std::max<float>(position_.z + depth_ / 2.0f,  other.position_.z + other.depth_ / 2.0f);

		if (((max_x - min_x) < (width_ + other.width_)) &&
			((max_z - min_z) < (depth_ + other.depth_))) {

			float collision_x = (width_ + other.width_) - (max_x - min_x);
			float collision_z = (depth_ + other.depth_) - (max_z - min_z);

			if (collision_x < collision_z) collision_vec = vec3(-1.0f, 0.0f, 0.0f);
			else collision_vec = vec3(0.0f, 0.0f, -1.0f);

			return true;
		}
		return false;

	}
	vec3 position_;

private:
	float width_;
	float depth_;
};