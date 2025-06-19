#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
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


	float vertices1[] = {
		-0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		-0.0f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.25f, 0.5f, 0.0f, 0.0f, 0.0f,
	};

	float vertices2[] = {
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.25f, 0.5f, 0.0f, 0.0f, 0.0f,
	};

	//int indices[] = {
	//	0,1,2,
	//	3,4,5
	//};

	Shader shader("./defaultVertex.glsl", "./defaultFragment.glsl");

	GLuint VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);

	GLuint VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.1, 0.6, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO1);
		shader.Use();
		shader.SetFloat("time", glfwGetTime());
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}