#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

using namespace glm;

namespace objr {

    class WorldTrans {
    public:

        void SetScale(float scale) { scale_ = vec3(scale); }

        void SetRotation(vec3 rotation) { rotation_ = rotation; }

        void SetSpin(vec3 spin) { spin_ = spin; }

        void SetPosition(vec3 position) { pos_ = position; }

        mat4 GetMatrix(void);

    private:
        vec3 scale_ = vec3(1.0f);
        vec3 rotation_ = vec3(0.0f);
        vec3 spin_ = vec3(0.0f);
        vec3 pos_ = vec3(0.0f);
    };
}