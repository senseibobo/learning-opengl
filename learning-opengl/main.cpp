#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


const char* vertexShaderSource = "#version 330 core\n"
	"layout(location = 0) in vec3 aPos; \n"
	"layout(location = 1) in vec2 aUV;\n"
	"out vec2 UV;"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"	UV = aUV;\n"
	"}\n";


const char* fragmentShaderSource = "#version 330 core\n"
"in vec2 UV;\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"	FragColor = vec4(UV.x, UV.y, 0.9, 1.0); \n"
"}\n";


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, 800, 600);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


void checkShaderCompiled(GLuint shader)
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

void checkProgramLinked(GLuint program)
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


int main() {


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "IDEMO OPENGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Nije uspelo pravljenje windowa :(\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Nije uspelo iniciranje gladovanja :(\n";
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,0.0f,0.0f,
		0.5f, -0.5f, 0.0f,0.0f,1.0f,
		0.0f, 0.5f, 0.0f,1.0f,1.0f,
	};



	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	checkShaderCompiled(vertexShader);
	checkShaderCompiled(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkProgramLinked(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);



	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.1, 0.6, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}