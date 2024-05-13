#include "camera.h"

Camera::Camera(GLfloat zoom, GLfloat fov) : zoom_{ zoom }, fov_{ fov }, near_{ 0.1f }, far_{ 100.0f } {}

Camera::Camera(GLfloat zoom, GLfloat fov, GLfloat near, GLfloat far) : zoom_{ zoom }, fov_{ fov }, near_{ near }, far_{ far } {}

mat4 Camera::UpdateProjectionMatrix(float ratio) const {

	return perspective(radians(fov_), ratio, 0.1f, 100.0f);
}

mat4 Camera::UpdateViewMatrix() const
{
	return lookAt(
		glm::vec3(0, 0, zoom_),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 1, 0)
    );
}

Camera::~Camera() {}