#include "texture.h"


void Texture::Create() {

	// Bind Texture Unit
	glActiveTexture(GL_TEXTURE0);

	// Create Texture Object
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_)
}

void Texture::Delete()
{
}