#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

namespace objr {

	class Texture {
		unsigned int id_ = 0;

	public:
		void Create() {
			// I'll just use the unit 0, f### it we ball
			//glActiveTexture(GL_TEXTURE0 + unit_++);

			// Create Texture Object
			glGenTextures(1, &id_);
			glBindTexture(GL_TEXTURE_2D, id_);
		}

		void Delete() const {
			glDeleteTextures(1, &id_);
		}

		void Bind() const {
			glBindTexture(GL_TEXTURE_2D, id_);
		}

		void Load(const std::string& path) const;
	};
}