#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <iostream>
#include <algorithm>

using namespace glm;

class CollisionBox {
public:
	CollisionBox() : position_{ vec3(0.0f) }, width_{ 1.0f }, height_{ 1.0f }, depth_{ 1.0f } {};
	
	CollisionBox(vec3 position, float w, float h, float d)
		: position_{ position }, width_{ w }, height_{ h }, depth_{ d } {};

	bool ComputeCollision(CollisionBox& other) {
		float min_x = std::min<float>(position_.x - width_ / 2.0f, other.position_.x - other.width_ / 2.0f);
		float max_x = std::max<float>(position_.x + width_ / 2.0f, other.position_.x + other.width_ / 2.0f);
		float min_y = std::min<float>(position_.y - height_ / 2.0f,other.position_.y - other.height_ / 2.0f);
		float max_y = std::max<float>(position_.y + height_ / 2.0f,other.position_.y + other.height_ / 2.0f);
		float min_z = std::min<float>(position_.z - depth_ / 2.0f, other.position_.z - other.depth_ / 2.0f);
		float max_z = std::max<float>(position_.z + depth_ / 2.0f, other.position_.z + other.depth_ / 2.0f);

		if (((min_x - max_x) < (width_ - other.width_)) ||
			((min_y - max_y) < (height_ - other.height_)) ||
			((min_z - max_z) < (depth_ - other.depth_))) {
			hit_ = true;
			other.hit_ = true;

			std::cout << "Collision Detected!" << position_.x << " | " << other.position_.x << std::endl;
		}
		else hit_ == false;

		return hit_;
	}
	vec3 position_;

private:
	float width_;
	float height_;
	float depth_;

	bool hit_ = false;
};