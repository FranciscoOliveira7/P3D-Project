#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

using namespace glm;

class WorldTrans {
public:

    void SetScale(float scale) { scale_ = vec3(scale); }

    void SetRotation(vec3 rotation) { rotation_ = rotation; }

    void SetPosition(vec3 position) { pos_ = position; }

    void Rotate(float x, float y, float z) {
        rotation_.x += x;
        rotation_.y += y;
        rotation_.z += z;
    }

    mat4 GetMatrix(void);

private:
    vec3 scale_    = vec3(1.0f);
    vec3 rotation_ = vec3(0.0f);
    vec3 pos_      = vec3(0.0f);
};