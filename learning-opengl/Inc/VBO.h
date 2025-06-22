#pragma once
#include <glad/glad.h>

class VBO {
public:
	VBO(GLsizeiptr size, GLvoid* data);
	~VBO();

	void Bind();
	void Unbind();

private:
	GLuint ID;
};