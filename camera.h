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
	~Camera();

	mat4 UpdateProjectionMatrix(float ratio) const;
	mat4 UpdateViewMatrix(vec3 eye, vec3 center, vec3 up) const;
	GLfloat zoom_;

private:
	float fov_;

	float far_, near_;

	mat4 projection, view;
};