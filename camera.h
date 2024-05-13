#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

#define GLEW_STATIC
#include <GL\glew.h>

using namespace glm;

class Camera {
public:
	Camera(GLfloat zoom, GLfloat fov);
	Camera(GLfloat zoom, GLfloat fov, GLfloat far, GLfloat near);

	mat4 UpdateProjectionMatrix(float ratio) const;
	mat4 UpdateViewMatrix() const;
	~Camera();
	GLfloat zoom_;

private:
	float fov_;

	float far_, near_;

	mat4 projection, view;
};