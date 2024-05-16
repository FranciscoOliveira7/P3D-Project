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

    mat4 GetViewMatrix(void) { return view_mat; }

private:

    vec3 center_;
    vec3 up_;

    mat4 view_mat;
};