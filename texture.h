#pragma once

#include <GL/glew.h>

class Texture {
private:
	unsigned int id_;

public:
	void Create();
	void Delete();

	void Bind() const;
};