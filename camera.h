#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

using namespace glm;

class Camera {
public:

    Camera(float ratio) : ratio_{ ratio } {
        center_ = vec3(0.0f, -5.0f, 0.0f);
        up_ = vec3(0.0f, 1.0f, 0.0f);

        view_ = lookAt(vec3(0.0f), center_, up_);
        projection_ = perspective(radians(45.0f), ratio, 1.0f, 100.0f);
    }

    void SetPosition(float x, float y, float z) {
        view_ = lookAt(vec3(x, y, z), center_, up_);
    }

    void SetFov(float fov) {
        fov_ = fov;
        UpdateProjection();
    }

    void SetRatio(float ratio) {
        ratio_ = ratio;
        UpdateProjection();
    }

    mat4 GetProjectionMatrix(void) const { return projection_; }
    mat4 GetViewMatrix(void) const { return view_; }

private:
    void UpdateProjection() { projection_ = perspective(radians(fov_), ratio_, 1.0f, 100.0f); }

    vec3 center_;
    vec3 up_;

    float ratio_, fov_;

    mat4 projection_, view_;
};