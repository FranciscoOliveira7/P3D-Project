#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Texture::Create() {

	// I'll just use the unit 0, f### it we ball
	//glActiveTexture(GL_TEXTURE0 + unit_++);

	// Create Texture Object
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Load(const std::string& path) const {

    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!imageData) {
        std::cerr << "Failed to load texture: " << path << " - " << stbi_failure_reason() << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    // Set texture parameters here
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    std::cout << "Loaded texture: " << path << " with ID: " << id_ << std::endl;
    stbi_image_free(imageData);
}
