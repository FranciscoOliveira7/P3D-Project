#include "camera.h"

Camera::Camera()
{
    center_ = vec3(0.0f, -5.0f, -1.0f);
    up_ = vec3(0.0f, 1.0f, 0.0f);

    SetPosition(0.0f, 0.0f, 10.0f);
}

void Camera::SetPosition(float x, float y, float z)
{
    vec3 position = vec3(x, y, z);

    view_mat = lookAt(position, center_, up_);
}