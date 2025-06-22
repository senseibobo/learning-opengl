#include "../Inc/VAO.h"
#include "../Inc/VBO.h"

VAO::VAO() : ID(0)
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

VAO::~VAO()
{
	if (ID != 0) glDeleteVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type,GLsizei stride, GLvoid* offset)
{
	VBO.Bind();
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}
