#include "physic_object.h"

void PhysicsObject::Update(std::vector<PhysicsObject>& others, float deltaTime) {

	if (velocity_ != vec3(0.0f)) {
		vec3 collision;

		for (PhysicsObject& collider : others) {
			// So it doesn't collide to itself
			if (this == &collider) continue;

			// Funny
			if (collision_box_.ComputeCollision(collider.collision_box_, collision)) {
				collider.velocity_ += velocity_ * collision;
			}
		}
		// Collision with table borders
		if ((collision_box_.position_.x < -15.9f && velocity_.x < 0) ||
			(collision_box_.position_.x > 15.9f && velocity_.x > 0) ||
			(collision_box_.position_.z < -6.7f && velocity_.z < 0) ||
			(collision_box_.position_.z > 6.7f && velocity_.z > 0)) {
			velocity_ = vec3(0.0f);
		}
	}

	const vec3 delta_vel = velocity_ * deltaTime;
	collision_box_.position_ += delta_vel;
	velocity_ -= delta_vel * k_friction_;
	rotation_.x += delta_vel.z;
	rotation_.y += -delta_vel.x;
}