#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <iostream>
#include <algorithm>

using namespace glm;


/// <summary>
/// Collision detection for balls
/// </summary>
class CollisionSphere {
public:
	CollisionSphere(vec3 position) : position_{ position }, radius_{ 1.0f } {};
	
	CollisionSphere(vec3 position, float radius)
		: position_{ position }, radius_{ radius } {};

	bool ComputeCollision(CollisionSphere& other, vec3& collision_normal) {
		// É feito a diferença dos vetores de posição para saber a distância
		vec3 normal = position_ - other.position_;

		collision_normal = normalize(normal);

		float distance_in = (radius_ + other.radius_) - length(normal);

		// Caso a distância entre as duas bolas seja menor que a soma dos raios,
		// significa que elas estão a colidir
		if (distance_in >= 0) {
			// Para evitar a bola ficar dentro do objeto e colidir novamente,
			// ela é reposicionada para fora da bola a qual colidiu.
			position_ += collision_normal * distance_in;
			std::cout << "Alguem colou as bolas na mesa!" << std::endl;
			return true;
		}
		return false;
	}

	vec3 position_;

private:
	float radius_ = 1.0f;
};