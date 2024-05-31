#pragma once

#include "light_source.h"

namespace objr {

    class SpotLight : public LightSource {
    public:
        SpotLight() {
            position_ = vec3(0.0f);
            direction_ = vec3(0.0f, 1.0f, 0.0f);
            ambient_ = vec3(0.2f);
            diffuse_ = vec3(1.0f);
            specular_ = vec3(1.0f);

            constant_ = 1.0f;
            linear_ = 0.006f;
            quadratic_ = 0.002f;

            spotCutoff_ = glm::radians(32.5f);
            spotExponent_ = 10.0f;
        }

        void Update() {
            enabled_ = true;
            shader_.SetUniform3fv("spotLight.position", position_);
            shader_.SetUniform3fv("spotLight.spotDirection", direction_);

            shader_.SetUniform3fv("spotLight.ambient", ambient_);
            shader_.SetUniform3fv("spotLight.diffuse", diffuse_);
            shader_.SetUniform3fv("spotLight.specular", specular_);

            shader_.SetUniform1f("spotLight.constant", constant_);
            shader_.SetUniform1f("spotLight.linear", linear_);
            shader_.SetUniform1f("spotLight.quadratic", quadratic_);

            shader_.SetUniform1f("spotLight.spotCutoff", spotCutoff_);
            shader_.SetUniform1f("spotLight.spotExponent", spotExponent_);
        }

        void Disable() {
            enabled_ = false;
            shader_.SetUniform3fv("spotLight.ambient", vec3(0.0f));
            shader_.SetUniform3fv("spotLight.diffuse", vec3(0.0f));
            shader_.SetUniform3fv("spotLight.specular", vec3(0.0f));
        }

    private:
        vec3 position_;
        vec3 direction_;

        vec3 diffuse_;
        vec3 specular_;

        float constant_;
        float linear_;
        float quadratic_;

        float spotCutoff_, spotExponent_;
    };
}