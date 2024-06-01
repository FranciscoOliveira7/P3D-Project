#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include "../shader.h"

using namespace glm;

namespace objr {

    class LightSource {
    public:
        // Atualiza os parâmetros da fonte de luz
        virtual void Update() = 0;

        // Desativa a fonte de luz
        virtual void Disable() = 0;

        // Alterna o estado da fonte de luz entre ativado e desativado
        void Toggle() {
            if (enabled_)
                Disable();
            else
                Update();
        }

        // Define o shader utilizado pela fonte de luz
        void SetShader(Shader shader) { shader_ = shader; }

    protected:
        Shader shader_; // Shader utilizado pela fonte de luz

        vec3 ambient_ = vec3(0.0f, 0.0f, 0.0f); // Componente ambiente da luz

        bool enabled_ = true; // Estado de atividade da fonte de luz
    };
}