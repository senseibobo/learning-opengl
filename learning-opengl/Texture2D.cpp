#include "Texture2D.h"
#include <iostream>

std::shared_ptr<Texture2D> Texture2D::WhiteFallbackTexture = nullptr;

void Texture2D::InitWhiteFallbackTexture()
{
	unsigned char whitePixel[4] = { 255,255,255,255 };
	WhiteFallbackTexture = std::make_shared<Texture2D>(whitePixel, GL_RGBA, 1, 1);
	glBindTexture(GL_TEXTURE_2D, WhiteFallbackTexture->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Texture2D::Texture2D(const char* imagePath)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	if (!data) {
		std::cerr << "Failed to load texture: " << imagePath << "\n";
		ID = 0;
		return;
	}

	GLenum format = GL_RGB;
	if (nrChannels == 4) format = GL_RGBA;
	else if (nrChannels == 1) format = GL_RED;

	ID = GenerateTexture(data, format, width, height);

	stbi_image_free(data);
}


Texture2D::Texture2D(unsigned char* data, GLenum type, int width, int height)
{
	ID = GenerateTexture(data, type, width, height);
}

GLuint Texture2D::GenerateTexture(unsigned char* data, GLenum format, int width, int height)
{
	if (!data)
	{
		std::cerr << "Data is invalid.\n";
		return 0;
	}

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);


	GLenum internalFormat = GL_RGBA8;
	if (format == GL_RGB) internalFormat = GL_RGB8;
	else if (format == GL_RED) internalFormat = GL_R8;
	
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	return id;
}

void Texture2D::SetWrap(GLenum wrapType)
{
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
}
