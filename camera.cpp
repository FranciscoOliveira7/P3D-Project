#include "camera.h"

Camera::Camera(GLfloat zoom, GLfloat fov) : zoom_{ zoom }, fov_{ fov }, near_{ 0.1f }, far_{ 100.0f } {}

Camera::Camera(GLfloat zoom, GLfloat fov, GLfloat near, GLfloat far) : zoom_{ zoom }, fov_{ fov }, near_{ near }, far_{ far } {}

mat4 Camera::UpdateProjectionMatrix(float ratio) const {

	return perspective(radians(fov_), ratio, 0.1f, 100.0f);
}

mat4 Camera::UpdateViewMatrix(vec3 eye, vec3 center, vec3 up) const {

	return lookAt(eye, center, up);
}

Camera::~Camera() {}