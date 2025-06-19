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
private:
	void checkShaderCompiled(GLuint shader);
	void checkProgramLinked(GLuint program);
};

