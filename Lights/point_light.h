#pragma once

#include "light_source.h"

namespace objr {

    class PointLight : public LightSource {
    public:
        PointLight() {
            position_ = vec3(0.0f);
            ambient_ = vec3(0.1f);
            diffuse_ = vec3(1.0f);
            specular_ = vec3(1.0f);
            constant_ = 1.0f;
            linear_ = 0.06f;
            quadratic_ = 0.02f;
        }

        void Update() {
            enabled_ = true;
            shader_.SetUniform3fv("pointLight.position", position_);
            shader_.SetUniform3fv("pointLight.ambient", ambient_);
            shader_.SetUniform3fv("pointLight.diffuse", diffuse_);
            shader_.SetUniform3fv("pointLight.specular", specular_);
            shader_.SetUniform1f("pointLight.constant", constant_);
            shader_.SetUniform1f("pointLight.linear", linear_);
            shader_.SetUniform1f("pointLight.quadratic", quadratic_);
        }

        void Disable() {
            enabled_ = false;
            shader_.SetUniform3fv("pointLight.ambient", vec3(0.0f));
            shader_.SetUniform3fv("pointLight.diffuse", vec3(0.0f));
            shader_.SetUniform3fv("pointLight.specular", vec3(0.0f));
        }

        void SetPosition(vec3 position) { position_ = position; }

    private:
        vec3  position_;
        vec3  diffuse_;
        vec3  specular_;
        float constant_;
        float linear_;
        float quadratic_;
    };
}