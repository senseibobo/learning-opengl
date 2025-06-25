#pragma once
#include <glad/glad.h>
#include <memory>
#include "stb_image.h"
class Texture2D
{
public:
	Texture2D(const char* imagePath, GLenum type);
	Texture2D(unsigned char* data, GLenum type, int width, int height);
	static GLuint GenerateTexture(unsigned char* data, GLenum type, int width, int height);
	static void InitWhiteFallbackTexture();
	static std::shared_ptr<Texture2D> WhiteFallbackTexture;
	GLuint ID;
	void SetWrap(GLenum wrapType);
};

