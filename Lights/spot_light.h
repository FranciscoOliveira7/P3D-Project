#pragma once

#include "light_source.h"

namespace objr {

    class SpotLight : public LightSource {
    public:
        // Construtor padr�o que inicializa os atributos da luz spot
        SpotLight() {
            position_ = vec3(0.0f); // Posi��o inicial da luz
            direction_ = vec3(1.0f, 1.0f, 0.0f); // Dire��o inicial da luz
            ambient_ = vec3(0.2f); // Componente ambiental da luz
            diffuse_ = vec3(1.0f); // Componente difusa da luz
            specular_ = vec3(1.0f); // Componente especular da luz

            constant_ = 1.0f; // Atenua��o constante
            linear_ = 0.006f; // Atenua��o linear
            quadratic_ = 0.002f; // Atenua��o quadr�tica

            spotCutoff_ = glm::radians(30.0f); // �ngulo de corte do feixe da luz spot
            spotExponent_ = 30.0f; // Expoente do feixe da luz spot
        }

        // Atualiza os par�metros da luz spot no shader
        void Update() {
            enabled_ = true; // Habilita a luz spot
            shader_.SetUniform3fv("spotLight.position", position_); // Define a posi��o da luz spot no shader
            shader_.SetUniform3fv("spotLight.spotDirection", direction_); // Define a dire��o da luz spot no shader

            shader_.SetUniform3fv("spotLight.ambient", ambient_); // Define a componente ambiental no shader
            shader_.SetUniform3fv("spotLight.diffuse", diffuse_); // Define a componente difusa no shader
            shader_.SetUniform3fv("spotLight.specular", specular_); // Define a componente especular no shader

            shader_.SetUniform1f("spotLight.constant", constant_); // Define a atenua��o constante no shader
            shader_.SetUniform1f("spotLight.linear", linear_); // Define a atenua��o linear no shader
            shader_.SetUniform1f("spotLight.quadratic", quadratic_); // Define a atenua��o quadr�tica no shader

            shader_.SetUniform1f("spotLight.spotCutoff", spotCutoff_); // Define o �ngulo de corte do feixe no shader
            shader_.SetUniform1f("spotLight.spotExponent", spotExponent_); // Define o expoente do feixe no shader
        }

        // Desabilita a luz spot, definindo suas componentes de cor como zero
        void Disable() {
            enabled_ = false; // Desabilita a luz spot
            shader_.SetUniform3fv("spotLight.ambient", vec3(0.0f)); // Define a componente ambiental como zero no shader
            shader_.SetUniform3fv("spotLight.diffuse", vec3(0.0f)); // Define a componente difusa como zero no shader
            shader_.SetUniform3fv("spotLight.specular", vec3(0.0f)); // Define a componente especular como zero no shader
        }

    private:
        vec3 position_; // Posi��o da luz spot
        vec3 direction_; // Dire��o da luz spot

        vec3 ambient_; // Componente ambiental da luz spot
        vec3 diffuse_; // Componente difusa da luz spot
        vec3 specular_; // Componente especular da luz spot

        float constant_; // Atenua��o constante
        float linear_; // Atenua��o linear
        float quadratic_; // Atenua��o quadr�tica

        float spotCutoff_; // �ngulo de corte do feixe da luz spot
        float spotExponent_; // Expoente do feixe da luz spot
    };
}