#pragma once
#include "Shader.h"
#include "Camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
class Mesh
{
public:
	Mesh(float* vertices, int vertexCount, Shader* shader, Camera* camera);
	glm::mat4 GetModelMatrix() const;

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	GLuint GetVAO() const;
	void SetVAO(GLuint VAO);

	void SetVertices(float* vertices, int count);
	
	Shader* GetShader();
	void SetShader(Shader* shader);
	void SetCamera(Camera* camera);

	void Draw() const;
private:
	void updateModelMatrix();

	GLuint VAO;
	GLsizei vertexCount;

	Shader* shader;
	Camera* camera;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 modelMatrix;
};

