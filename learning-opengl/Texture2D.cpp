#include "Texture2D.h"

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

Texture2D::Texture2D(const char* imagePath, GLenum type)
{

	int width, height, nrChannels;
	unsigned char* imageData = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	ID = GenerateTexture(imageData, type, width, height);
	stbi_image_free(imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture2D::Texture2D(unsigned char* data, GLenum type, int width, int height)
{
	ID = GenerateTexture(data, type, width, height);
}

GLuint Texture2D::GenerateTexture(unsigned char* data, GLenum type, int width, int height)
{
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
	return id;
}

void Texture2D::SetWrap(GLenum wrapType)
{
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
}
