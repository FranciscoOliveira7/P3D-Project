#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

class VAO
{
public:
	VAO();
	~VAO();

private:
	GLint *VBOs;
};

VAO::VAO()
{
}

VAO::~VAO()
{
}