#pragma once
#include <glad/glad.h>


class VBO; // forward declaration

class VAO {
public:
	VAO();
	~VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type,GLsizei stride, GLvoid* offset);

	void Bind();
	void Unbind();
private:
	GLuint ID;
};