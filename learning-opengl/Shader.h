#pragma once
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexSourcePath, const char* fragmentSourcePath);
	void Use();
	void SetBool(const char* uniformName, bool value);
	void SetFloat(const char* uniformName, float value);
	void SetInt(const char* uniformName, int value);
	void SetTexture(const char* uniformName, GLuint textureID, int location);
private:
	static GLuint lastUsedProgram;
	void checkShaderCompiled(GLuint shader);
	void checkProgramLinked(GLuint program);
};

