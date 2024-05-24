#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

class Texture {
private:
	static unsigned int unit_;
	unsigned int id_;

public:
	void Create();
	void Delete() const {
		glDeleteTextures(1, &id_);
	}

	void Load(const std::string& path);

	void Bind() const {
		glBindTexture(GL_TEXTURE_2D, id_);
	}

	unsigned int GetId() const { return id_; }
};