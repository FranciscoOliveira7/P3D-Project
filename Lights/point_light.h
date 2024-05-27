#pragma once

#include "light_source.h"

class PointLight : public LightSource {
public:
    PointLight() {
        position_ = vec3(0.0f);
        ambient_ = vec3(0.1f);
        diffuse = vec3(1.0f);
        specular = vec3(1.0f);
        constant = 1.0f;
        linear = 0.06f;
        quadratic = 0.02f;
    }

	void Update() {
        shader_.SetUniform3fv("pointLight.position", position_);
        shader_.SetUniform3fv("pointLight.ambient", ambient_);
        shader_.SetUniform3fv("pointLight.diffuse", diffuse);
        shader_.SetUniform3fv("pointLight.specular", specular);
        shader_.SetUniform1f("pointLight.constant", constant);
        shader_.SetUniform1f("pointLight.linear", linear);
        shader_.SetUniform1f("pointLight.quadratic", quadratic);
	}
private:
    vec3  diffuse;
    vec3  specular;
    float constant;
    float linear;
    float quadratic;
};