#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

#define GLEW_STATIC
#include <GL\glew.h>

using namespace glm;

class Camera {
public:

    Camera();

    void SetPosition(float x, float y, float z);

    void OnKeyboard(unsigned char key);

    mat4 GetViewMatrix();

private:

    vec3 eye_;
    vec3 center_;
    vec3 up_;
    float m_speed = 1.0f;
};