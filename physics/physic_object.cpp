#include "physic_object.h"

void PhysicsObject::Update(std::vector<PhysicsObject>& others, float deltaTime) {

	if (velocity_ != vec3(0.0f)) {
		vec3 collision_normal;

		for (PhysicsObject& collider : others) {
			// So it doesn't collide to itself
			if (this == &collider) continue;

			if (collision_sphere_.ComputeCollision(collider.collision_sphere_, collision_normal)) {
				// Para que a bola faça a tragetoria "refletiva" à normal de colisão com a outra bola
				vec3 tragectory = reflect(normalize(velocity_), collision_normal) * length(velocity_);

				//collider.velocity_ -= collision_normal * 0.1f;
				velocity_ = tragectory;
			}
		}
		// Collision with table borders
		if ((collision_sphere_.position_.x < -15.9f && velocity_.x < 0) ||
			(collision_sphere_.position_.x > 15.9f && velocity_.x > 0)) {
			velocity_.x *= -1;
		}
		if ((collision_sphere_.position_.z < -6.7f && velocity_.z < 0) ||
			(collision_sphere_.position_.z > 6.7f && velocity_.z > 0)) {
			velocity_.z *= -1;
		}

		const vec3 delta_vel = velocity_ * deltaTime;
		collision_sphere_.position_ += delta_vel;
		velocity_ -= delta_vel * k_friction_;
		rotation_.x += delta_vel.z;
		rotation_.y += -delta_vel.x;
	}
}