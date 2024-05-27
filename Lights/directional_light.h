#pragma once

#include "light_source.h"

class DirectionalLight : public LightSource {
public:
	DirectionalLight() {
        direction_ = vec3(0.894427f, -0.447214f, 0.0f);
        ambient_ = vec3(0.2f);
        diffuse_ = vec3(1.0f);
        specular_ = vec3(1.0f);
	}


    void Update() {
        shader_.SetUniform3fv("directionalLight.direction", direction_);
        shader_.SetUniform3fv("directionalLight.ambient", ambient_);
        shader_.SetUniform3fv("directionalLight.diffuse", diffuse_);
        shader_.SetUniform3fv("directionalLight.specular", specular_);
    }

private:
    vec3 diffuse_;
    vec3 specular_;
};