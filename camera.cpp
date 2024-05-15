#include "camera.h"

Camera::Camera()
{
    eye_ = vec3(0.0f, 0.0f, 10.0f);
    center_ = vec3(0.0f, 0.0f, -1.0f);
    up_ = vec3(0.0f, 1.0f, 0.0f);
}


void Camera::SetPosition(float x, float y, float z)
{
    eye_.x = x;
    eye_.y = y;
    eye_.z = z;
}


mat4 Camera::GetViewMatrix() {
    mat4 ViewTransformation;
    ViewTransformation = lookAt(eye_, center_, up_);

    return ViewTransformation;
}
