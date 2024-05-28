#pragma once

#include "light_source.h"

namespace objr {

    class AmbientLight : public LightSource {
    public:
        AmbientLight() {
            ambient_ = vec3(0.5f);
        }

        void SetAmbient(vec3 ambient) { ambient_ = ambient; }

        void Update() {
            enabled_ = true;
            shader_.SetUniform3fv("ambientLight.ambient", ambient_);
        }

        void Disable() {
            enabled_ = false;
            shader_.SetUniform3fv("ambientLight.ambient", vec3(0.0f));
        }
    };
}