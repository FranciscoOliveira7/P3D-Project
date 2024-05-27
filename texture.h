#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

namespace AsBolasDoJose {

	class Texture {
	private: unsigned int id_ = 0;

	public:
		void Create();

		void Delete() const {
			glDeleteTextures(1, &id_);
		}

		void Load(const std::string& path) const;

		void Bind() const {
			glBindTexture(GL_TEXTURE_2D, id_);
		}
	};
}