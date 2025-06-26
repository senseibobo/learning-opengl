#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

class Mesh
{
public:
	Mesh(float* vertices, uint32_t* indices, int vertexCount, int indexCount);

	void SetVertices(float* vertices, uint32_t* indices, int vertexCount, int indexCount);
	void SetVAO(GLuint VAO);

	GLsizei GetVertexCount() const;
	GLsizei GetIndexCount() const;
	GLuint GetVAO() const;
private:
	GLuint VAO;
	GLsizei vertexCount;
	GLsizei indexCount;
};

