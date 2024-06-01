#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include "collision_sphere.h"

using namespace glm;

class PhysicsObject {

    public:
        // Construtor que inicializa o objeto f�sico com uma posi��o e uma esfera de colis�o
        PhysicsObject(vec3 position) : initial_pos_{ position }, collision_sphere_{ CollisionSphere(position) } { }

        // Construtor que inicializa o objeto f�sico com uma posi��o e um raio para a esfera de colis�o
        PhysicsObject(vec3 position, float radius)
            : initial_pos_{ position }, collision_sphere_{ CollisionSphere(position, radius) } {}

        // Atualiza a f�sica do objeto com base no deltaTime e em outros objetos f�sicos para detec��o de colis�o
        void Update(std::vector<PhysicsObject>& others, float deltaTime);

        // Reinicia a posi��o do objeto para a posi��o inicial
        void ResetPosition() { collision_sphere_.position_ = initial_pos_; }

        // Para o movimento do objeto, definindo sua velocidade como zero
        void Stop() { velocity_ = vec3(0.0f); }

        // Define a posi��o do objeto
        void SetPosition(vec3 position) {
            initial_pos_ = position;
            collision_sphere_.position_ = position;
        }

        // Define a velocidade do objeto
        void SetVelocity(vec3 velocity) { velocity_ = velocity; }

        // Adiciona uma velocidade ao objeto
        void AddVelocity(vec3 velocity) { velocity_ += velocity; }

        // Obt�m a posi��o atual do objeto
        vec3 GetPosition() const { return collision_sphere_.position_; }

        // Obt�m a rota��o do objeto
        vec2 GetRotation() const { return rotation_; }

        // Esfera de colis�o associada ao objeto f�sico
        CollisionSphere collision_sphere_;

    private:
        vec2 rotation_ = vec3(0.0f); // Rota��o do objeto
        vec3 velocity_ = vec3(0.0f); // Velocidade do objeto
        vec3 initial_pos_; // Posi��o inicial do objeto

        const float k_friction_ = 0.0005f; // Coeficiente de atrito do objeto
 
};