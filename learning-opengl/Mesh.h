#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
class Mesh
{
public:
	Mesh(float* vertices, int vertexCount);
	
	void SetVertices(float* vertices, int count);
	void SetVAO(GLuint VAO);

	GLsizei GetVertexCount() const;
	GLuint GetVAO() const;
private:
	GLuint VAO;
	GLsizei vertexCount;
};

