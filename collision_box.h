#pragma once

#include <iostream>
#include <algorithm>

class CollisionBox {
public:
	CollisionBox() : center_x_{ 0.0f },	center_y_{ 0.0f }, center_z_{ 0.0f },
					 width_{ 1.0f },	height_{ 1.0f },   depth_{ 1.0f } {};
	
	CollisionBox(float x, float y, float z, float w, float h, float d)
		: center_x_{ x }, center_y_{ y }, center_z_{ z }, width_{ w }, height_{ h }, depth_{ z } {};

	bool ComputeCollision(CollisionBox& other) {
		float min_x = std::min<float>(center_x_ - width_ / 2.0f, other.center_x_ - other.width_ / 2.0f);
		float max_x = std::max<float>(center_x_ + width_ / 2.0f, other.center_x_ + other.width_ / 2.0f);
		float min_y = std::min<float>(center_y_ - height_ / 2.0f, other.center_y_ - other.height_ / 2.0f);
		float max_y = std::max<float>(center_y_ + height_ / 2.0f, other.center_y_ + other.height_ / 2.0f);
		float min_z = std::min<float>(center_z_ - depth_ / 2.0f, other.center_z_ - other.depth_ / 2.0f);
		float max_z = std::max<float>(center_z_ + depth_ / 2.0f, other.center_z_ + other.depth_ / 2.0f);

		if (((min_x - max_x) < (width_ - other.width_)) ||
			((min_y - max_y) < (height_ - other.height_)) ||
			((min_z - max_z) < (depth_ - other.depth_))) {
			hit_ = true;
			other.hit_ = true;

			std::cout << "Collision Detected!";
		}
		else {
			hit_ |= false;
		}

		return hit_;
	}

private:
	float center_x_;
	float center_y_;
	float center_z_;
	float width_;
	float height_;
	float depth_;

	bool hit_ = false;
};