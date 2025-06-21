#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "Texture2D.h"
#include "stb_image.h"


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


	float vertices[] = {
		0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	   -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
	   -0.5f,  0.5f, 0.0f, 1.0f, 0.0f
	};

	int indices[] = {
		0,1,3,
		1,2,3
	};

	float cubeVertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
	};

	Shader shader("./defaultVertex.glsl", "./defaultFragment.glsl");



	// cube
	GLuint cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	GLuint cubeVBO;
	glGenBuffers(1, &cubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);



	// plane
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	int width, height, nrChannels;
	unsigned char* imageData = stbi_load("./texture.png", &width, &height, &nrChannels, 0);

	Texture2D texture1("./texture.png", GL_RGBA);
	Texture2D texture2("./container.jpg", GL_RGB);

	shader.Use();
	shader.SetTexture("myTexture", texture1.ID, 0);
	shader.SetTexture("otherTexture", texture2.ID, 1);



	// projection
	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.1, 0.6, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -5.0f);
		glm::vec3 cameraRotation = glm::vec3(cos(glfwGetTime()*5.0f)/3.0f, 0.0f, 0.0f);

		glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::normalize(glm::vec3(1.0f,1.0f,0.0f)));
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, -cameraRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		view = glm::rotate(view, -cameraRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, -cameraRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, cameraPosition);
		glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.01f, 100.0f);



		shader.Use();
		//shader.SetFloat("time", glfwGetTime());
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		//glm::mat4 transform = glm::mat4(1.0f);
		//transform = glm::translate(transform, glm::vec3(-0.5f, -0.2f, 0.0f));
		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//transform = glm::scale(transform, glm::vec3(2.0f, 0.5f, 1.0f));
		//shader.SetMat4("model", transform);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glm::mat4 transform2 = glm::mat4(1.0f);
		//transform2 = glm::scale(transform2, glm::vec3(sin(glfwGetTime()), (cos(glfwGetTime())+3.0f)/4.0f, 1.0f));
		//transform2 = glm::translate(transform2, glm::vec3(0.5f, 0.0f, 1.0f));
		//shader.SetMat4("model", transform2);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}