#pragma once
#include <glad/glad.h>
#include "stb_image.h"
class Texture2D
{
public:
	GLuint ID;
	Texture2D(const char* imagePath, GLenum type);
	void SetWrap(GLenum wrapType);
	
	void Bind();
	void Unbind();

	~Texture2D();
};

