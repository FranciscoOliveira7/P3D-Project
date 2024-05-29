#include "physic_object.h"

void PhysicsObject::Update(std::vector<PhysicsObject>& others, float deltaTime) {

	if (velocity_ != vec3(0.0f)) {
		vec3 collision;
		bool collided = false;

		for (PhysicsObject& collider : others) {
			// So it doesn't collide to itself
			if (this == &collider) continue;

			// Funny
			if (collision_box_.ComputeCollision(collider.collision_box_, collision)) {
				collider.velocity_ += velocity_ * collision;
				collided = true;
			}
		}
	}

	const vec3 delta_vel = velocity_ * deltaTime;
	collision_box_.position_ += delta_vel;
	velocity_ -= delta_vel * k_friction_;
	rotation_.x += -delta_vel.z;
	rotation_.y += -delta_vel.x;
}