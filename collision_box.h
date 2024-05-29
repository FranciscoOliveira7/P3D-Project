#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <iostream>
#include <algorithm>

using namespace glm;

class CollisionBox {
public:
	CollisionBox() : position_{ vec3(0.0f) }, width_{ 1.0f }, height_{ 1.0f }, depth_{ 1.0f } {};
	
	CollisionBox(vec3 position, vec3 size)
		: position_{ position }, width_{ size.x }, height_{ size.y }, depth_{ size.z } {};

	bool ComputeCollision(CollisionBox& other) {
		float min_x = std::min<float>(position_.x - width_ / 2.0f,  other.position_.x - other.width_ / 2.0f);
		float max_x = std::max<float>(position_.x + width_ / 2.0f,  other.position_.x + other.width_ / 2.0f);
		float min_y = std::min<float>(position_.y - height_ / 2.0f, other.position_.y - other.height_ / 2.0f);
		float max_y = std::max<float>(position_.y + height_ / 2.0f, other.position_.y + other.height_ / 2.0f);
		float min_z = std::min<float>(position_.z - depth_ / 2.0f,  other.position_.z - other.depth_ / 2.0f);
		float max_z = std::max<float>(position_.z + depth_ / 2.0f,  other.position_.z + other.depth_ / 2.0f);

		return (((max_x - min_x) < (width_  + other.width_)) &&
				((max_y - min_y) < (height_ + other.height_)) &&
				((max_z - min_z) < (depth_  + other.depth_)));
	}
	vec3 position_;

private:
	float width_;
	float height_;
	float depth_;
};