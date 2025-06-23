#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"
#include "RenderComponent.h"
#include "RenderingManager.h"
#include "Mesh.h"
#include "Node3D.h"
#include "stb_image.h"


Camera* camera;
double oldTime = 0.0f;
double deltaTime = 0.0001f;
double oldMouseX;
double oldMouseY;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow*, double mouseX, double mouseY)
{
	camera->RotateYaw((mouseX - oldMouseX)*0.005f);
	camera->RotatePitch(-(mouseY - oldMouseY)*0.005f);
	oldMouseX = mouseX;
	oldMouseY = mouseY;
}

void scroll_callback(GLFWwindow* window, double x, double y)
{
	camera->SetFov(camera->GetFov() - y*5.0f);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (camera != nullptr)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->Move(camera->GetForwardVector() * camera->GetSpeed() * (float)deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->Move(-camera->GetRightVector() * camera->GetSpeed() * (float)deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->Move(-camera->GetForwardVector() * camera->GetSpeed() * (float)deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->Move(camera->GetRightVector() * camera->GetSpeed() * (float)deltaTime);
		
		float rotationSpeed = 2.0f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			camera->RotateYaw(rotationSpeed * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			camera->Rotate(rotationSpeed * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camera->RotatePitch(rotationSpeed * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camera->Rotate(-rotationSpeed * deltaTime, camera->GetRightVector());
	}
}


int main() {


	stbi_set_flip_vertically_on_load(true);
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
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::vec3 cameraDirection = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - cameraPosition);
	camera = new Camera(cameraPosition, cameraDirection);
	std::shared_ptr<Shader> shader = std::make_shared<Shader>("./defaultVertex.glsl", "./defaultFragment.glsl");
	RenderingManager::SetCamera(camera);


	int width, height, nrChannels;
	unsigned char* imageData = stbi_load("./texture.png", &width, &height, &nrChannels, 0);

	std::shared_ptr<Texture2D> texture1 = std::make_shared<Texture2D>("./texture.png", GL_RGBA);
	std::shared_ptr<Texture2D> texture2 = std::make_shared<Texture2D>("./container.jpg", GL_RGB);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(cubeVertices, 36);
	std::shared_ptr<Material> material = std::make_shared<Material>();
	material->SetShader(shader);
	material->SetTexture("myTexture", texture1);
	material->SetTexture("otherTexture", texture2);
	Node3D cube;
	auto renderComponent = std::make_unique<RenderComponent>();
	renderComponent->SetMaterial(material);
	renderComponent->SetMesh(mesh);
	cube.AddComponent(std::move(renderComponent));




	// projection
	glEnable(GL_DEPTH_TEST);


	float fpsCap = 144.0f;

	while (!glfwWindowShouldClose(window)) {
	
		deltaTime = glfwGetTime() - oldTime;
		if (deltaTime < 1.0f / fpsCap) continue;
		processInput(window);

		glClearColor(0.1, 0.6, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderingManager::Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
		oldTime = glfwGetTime();
	}
	glfwTerminate();
	return 0;

}