#include "Shader.h"

GLuint Shader::lastUsedProgram = -1;

void Shader::checkShaderCompiled(GLuint shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Nije uspelo kompajlovanje shadera :(\n" << infoLog << "\n";
	}
}


void Shader::checkProgramLinked(GLuint program)
{
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Nije uspelo linkovanje shader programa :(\n" << infoLog << "\n";
	}
}


Shader::Shader(const char* vertexSourcePath, const char* fragmentSourcePath)
{

	std::string vertexSource;
	std::string fragmentSource;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	std::stringstream vertexStream;
	std::stringstream fragmentStream;

	vertexFile.open(vertexSourcePath);
	fragmentFile.open(fragmentSourcePath);

	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	vertexFile.close();
	fragmentFile.close();
	
	vertexSource = vertexStream.str();
	fragmentSource = fragmentStream.str();

	const char* vertexSourceCstr = vertexSource.c_str();
	const char* fragmentSourceCstr = fragmentSource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexSourceCstr, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSourceCstr, NULL);
	
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	checkShaderCompiled(vertexShader);
	checkShaderCompiled(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	checkProgramLinked(ID);
}

void Shader::Use() 
{
	if (ID != lastUsedProgram)
	{
		glUseProgram(ID);
		lastUsedProgram = ID;
	}
}


void Shader::SetBool(const char* uniformName, bool value)
{
	GLint location = glGetUniformLocation(ID, uniformName);
	glUniform1i(location, value);
}

void Shader::SetFloat(const char* uniformName, float value)
{
	GLint location = glGetUniformLocation(ID, uniformName);
	glUniform1f(location, value);
}

void Shader::SetInt(const char* uniformName, int value)
{
	GLint location = glGetUniformLocation(ID, uniformName);
	glUniform1i(location, value);
}

void Shader::SetMat4(const char* uniformName, const glm::mat4& value)
{
	GLint location = glGetUniformLocation(ID, uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetTexture(const char* uniformName, GLuint textureID, int location)
{
	this->Use();
	glActiveTexture(GL_TEXTURE0+location);
	glBindTexture(GL_TEXTURE_2D, textureID);
	this->SetInt(uniformName, location);
}