#pragma once
#include <glad/glad.h>

class EBO {
public:
	EBO(GLsizeiptr size, GLvoid* data);
	~EBO();

	void Bind();
	void Unbind();

private:
	GLuint ID;
};