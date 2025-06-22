#include "Texture2D.h"
#include <iostream>
Texture2D::Texture2D(const char* imagePath, GLenum format)
{

	int width, height, nrChannels;
	unsigned char* imageData = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	if (imageData) {
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData);
	}
	else {
		std::cout << "Failed to create texture" << std::endl;
	}
}

void Texture2D::SetWrap(GLenum wrapType)
{
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}
