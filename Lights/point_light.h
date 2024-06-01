#pragma once

#include "light_source.h"

namespace objr {

    class PointLight : public LightSource {
    public:
        // Construtor padr�o que inicializa os atributos da luz pontual
        PointLight() {
            position_ = vec3(0.0f); // Posi��o inicial da luz pontual
            ambient_ = vec3(0.1f); // Componente ambiental da luz pontual
            diffuse_ = vec3(1.0f); // Componente difusa da luz pontual
            specular_ = vec3(1.0f); // Componente especular da luz pontual
            constant_ = 1.0f; // Atenua��o constante
            linear_ = 0.06f; // Atenua��o linear
            quadratic_ = 0.02f; // Atenua��o quadr�tica
        }

        // Atualiza os par�metros da luz pontual no shader
        void Update() {
            enabled_ = true; // Habilita a luz pontual
            shader_.SetUniform3fv("pointLight.position", position_); // Define a posi��o da luz pontual no shader
            shader_.SetUniform3fv("pointLight.ambient", ambient_); // Define a componente ambiental no shader
            shader_.SetUniform3fv("pointLight.diffuse", diffuse_); // Define a componente difusa no shader
            shader_.SetUniform3fv("pointLight.specular", specular_); // Define a componente especular no shader
            shader_.SetUniform1f("pointLight.constant", constant_); // Define a atenua��o constante no shader
            shader_.SetUniform1f("pointLight.linear", linear_); // Define a atenua��o linear no shader
            shader_.SetUniform1f("pointLight.quadratic", quadratic_); // Define a atenua��o quadr�tica no shader
        }

        // Desabilita a luz pontual, definindo suas componentes de cor como zero
        void Disable() {
            enabled_ = false; // Desabilita a luz pontual
            shader_.SetUniform3fv("pointLight.ambient", vec3(0.0f)); // Define a componente ambiental como zero no shader
            shader_.SetUniform3fv("pointLight.diffuse", vec3(0.0f)); // Define a componente difusa como zero no shader
            shader_.SetUniform3fv("pointLight.specular", vec3(0.0f)); // Define a componente especular como zero no shader
        }

        // Define a posi��o da luz pontual
        void SetPosition(vec3 position) { position_ = position; }

    private:
        vec3 position_; // Posi��o da luz pontual
        vec3 ambient_; // Componente ambiental da luz pontual
        vec3 diffuse_; // Componente difusa da luz pontual
        vec3 specular_; // Componente especular da luz pontual
        float constant_; // Atenua��o constante
        float linear_; // Atenua��o linear
        float quadratic_; // Atenua��o quadr�tica
    };
}