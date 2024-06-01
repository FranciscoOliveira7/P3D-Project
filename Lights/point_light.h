#pragma once

#include "light_source.h"

namespace objr {

    class PointLight : public LightSource {
    public:
        // Construtor padrão que inicializa os atributos da luz pontual
        PointLight() {
            position_ = vec3(0.0f); // Posição inicial da luz pontual
            ambient_ = vec3(0.1f); // Componente ambiental da luz pontual
            diffuse_ = vec3(1.0f); // Componente difusa da luz pontual
            specular_ = vec3(1.0f); // Componente especular da luz pontual
            constant_ = 1.0f; // Atenuação constante
            linear_ = 0.06f; // Atenuação linear
            quadratic_ = 0.02f; // Atenuação quadrática
        }

        // Atualiza os parâmetros da luz pontual no shader
        void Update() {
            enabled_ = true; // Habilita a luz pontual
            shader_.SetUniform3fv("pointLight.position", position_); // Define a posição da luz pontual no shader
            shader_.SetUniform3fv("pointLight.ambient", ambient_); // Define a componente ambiental no shader
            shader_.SetUniform3fv("pointLight.diffuse", diffuse_); // Define a componente difusa no shader
            shader_.SetUniform3fv("pointLight.specular", specular_); // Define a componente especular no shader
            shader_.SetUniform1f("pointLight.constant", constant_); // Define a atenuação constante no shader
            shader_.SetUniform1f("pointLight.linear", linear_); // Define a atenuação linear no shader
            shader_.SetUniform1f("pointLight.quadratic", quadratic_); // Define a atenuação quadrática no shader
        }

        // Desabilita a luz pontual, definindo suas componentes de cor como zero
        void Disable() {
            enabled_ = false; // Desabilita a luz pontual
            shader_.SetUniform3fv("pointLight.ambient", vec3(0.0f)); // Define a componente ambiental como zero no shader
            shader_.SetUniform3fv("pointLight.diffuse", vec3(0.0f)); // Define a componente difusa como zero no shader
            shader_.SetUniform3fv("pointLight.specular", vec3(0.0f)); // Define a componente especular como zero no shader
        }

        // Define a posição da luz pontual
        void SetPosition(vec3 position) { position_ = position; }

    private:
        vec3 position_; // Posição da luz pontual
        vec3 ambient_; // Componente ambiental da luz pontual
        vec3 diffuse_; // Componente difusa da luz pontual
        vec3 specular_; // Componente especular da luz pontual
        float constant_; // Atenuação constante
        float linear_; // Atenuação linear
        float quadratic_; // Atenuação quadrática
    };
}