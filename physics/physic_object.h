#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include "collision_sphere.h"

using namespace glm;

class PhysicsObject {

    public:
        // Construtor que inicializa o objeto físico com uma posição e uma esfera de colisão
        PhysicsObject(vec3 position) : initial_pos_{ position }, collision_sphere_{ CollisionSphere(position) } { }

        // Construtor que inicializa o objeto físico com uma posição e um raio para a esfera de colisão
        PhysicsObject(vec3 position, float radius)
            : initial_pos_{ position }, collision_sphere_{ CollisionSphere(position, radius) } {}

        // Atualiza a física do objeto com base no deltaTime e em outros objetos físicos para detecção de colisão
        void Update(std::vector<PhysicsObject>& others, float deltaTime);

        // Reinicia a posição do objeto para a posição inicial
        void ResetPosition() { collision_sphere_.position_ = initial_pos_; }

        // Para o movimento do objeto, definindo sua velocidade como zero
        void Stop() { velocity_ = vec3(0.0f); }

        // Define a posição do objeto
        void SetPosition(vec3 position) {
            initial_pos_ = position;
            collision_sphere_.position_ = position;
        }

        // Define a velocidade do objeto
        void SetVelocity(vec3 velocity) { velocity_ = velocity; }

        // Adiciona uma velocidade ao objeto
        void AddVelocity(vec3 velocity) { velocity_ += velocity; }

        // Obtém a posição atual do objeto
        vec3 GetPosition() const { return collision_sphere_.position_; }

        // Obtém a rotação do objeto
        vec2 GetRotation() const { return rotation_; }

        // Esfera de colisão associada ao objeto físico
        CollisionSphere collision_sphere_;

    private:
        vec2 rotation_ = vec3(0.0f); // Rotação do objeto
        vec3 velocity_ = vec3(0.0f); // Velocidade do objeto
        vec3 initial_pos_; // Posição inicial do objeto

        const float k_friction_ = 0.0005f; // Coeficiente de atrito do objeto
 
};