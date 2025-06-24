#pragma once
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexSourcePath, const char* fragmentSourcePath);
	void Use();
	void SetBool(const char* uniformName, bool value);
	void SetFloat(const char* uniformName, float value);
	void SetInt(const char* uniformName, int value);
	void SetMat4(const char* uniformName, const glm::mat4& value);
	void SetVec3(const char* uniformName, const glm::vec3& value);
	void SetTexture(const char* uniformName, GLuint textureID, int location);

	GLuint GetLightBindingPoint() const;
private:
	static GLuint lastUsedProgram;
	void checkShaderCompiled(GLuint shader);
	void checkProgramLinked(GLuint program);
};

