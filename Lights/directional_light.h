#pragma once

#include "light_source.h"

namespace objr {

    class DirectionalLight : public LightSource {
    public:
        // Construtor que inicializa os parâmetros da luz direcional
        DirectionalLight() {
            direction_ = vec3(0.894427f, -0.447214f, 0.0f);
            ambient_ = vec3(0.2f);
            diffuse_ = vec3(1.0f);
            specular_ = vec3(1.0f);
        }

        // Atualiza os parâmetros da luz direcional
        void Update() {
            enabled_ = true;
            shader_.SetUniform3fv("directionalLight.direction", direction_);
            shader_.SetUniform3fv("directionalLight.ambient", ambient_);
            shader_.SetUniform3fv("directionalLight.diffuse", diffuse_);
            shader_.SetUniform3fv("directionalLight.specular", specular_);
        }

        // Desativa a luz direcional
        void Disable() {
            enabled_ = false;
            shader_.SetUniform3fv("directionalLight.ambient", vec3(0.0f));
            shader_.SetUniform3fv("directionalLight.diffuse", vec3(0.0f));
            shader_.SetUniform3fv("directionalLight.specular", vec3(0.0f));
        }

    private:
        vec3 direction_;  // Direção da luz direcional
        vec3 diffuse_;    // Componente difusa da luz direcional
        vec3 specular_;   // Componente especular da luz direcional
    };
}