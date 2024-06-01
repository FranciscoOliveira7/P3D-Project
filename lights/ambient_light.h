#pragma once

#include "light_source.h"

namespace objr {

    class AmbientLight : public LightSource {
    public:
        // Construtor que define o componente ambiente da luz ambiente
        AmbientLight() {
            ambient_ = vec3(0.5f);
        }

        // Define o componente ambiente da luz ambiente
        void SetAmbient(vec3 ambient) { ambient_ = ambient; }

        // Atualiza os parâmetros da luz ambiente
        void Update() {
            enabled_ = true;
            shader_.SetUniform3fv("ambientLight.ambient", ambient_);
        }

        // Desativa a luz ambiente
        void Disable() {
            enabled_ = false;
            shader_.SetUniform3fv("ambientLight.ambient", vec3(0.0f));
        }
    };
}