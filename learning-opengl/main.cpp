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
#include "LightComponent.h"


Camera* camera;
bool firstMouse = true;
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
	if (firstMouse)
	{
		oldMouseX = mouseX;
		oldMouseY = mouseY;
		firstMouse = false;
	}
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Nije uspelo iniciranje gladovanja :(\n";
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "VERSION: " << version << "\n";
	std::cout << "GLSL VERSION: " << glslVersion << "\n";

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
		// positions           // normals			 // UVs

		// back face (-Z)
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

		// front face (+Z)
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

		// left face (-X)
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

		// right face (+X)
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

		 // bottom face (-Y)
		 -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

		 // top face (+Y)
		 -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f
	};


	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::vec3 cameraDirection = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - cameraPosition);
	camera = new Camera(cameraPosition, cameraDirection);

	RenderingManager::SetCamera(camera);


	int width, height, nrChannels;
	unsigned char* imageData = stbi_load("./texture.png", &width, &height, &nrChannels, 0);

	std::shared_ptr<Texture2D> texture1 = std::make_shared<Texture2D>("./texture.png", GL_RGBA);
	std::shared_ptr<Texture2D> texture2 = std::make_shared<Texture2D>("./container.jpg", GL_RGB);
	texture1->SetWrap(GL_CLAMP_TO_EDGE);
	texture2->SetWrap(GL_REPEAT);

	std::shared_ptr<Shader> shader = std::make_shared<Shader>("./litVertex.glsl", "./litFragment.glsl");
	std::shared_ptr<Material> material1 = std::make_shared<Material>();
	std::shared_ptr<Material> material2 = std::make_shared<Material>();

	material1->SetShader(shader);
	material1->SetTexture("myTexture", texture1);

	material2->SetShader(shader);
	material2->SetTexture("myTexture", texture2);

	std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>(cubeVertices, 36);

	Node3D cube1;
	auto renderComponent1 = std::make_unique<RenderComponent>();
	renderComponent1->SetMaterial(material1);
	renderComponent1->SetMesh(cubeMesh);
	cube1.AddComponent(std::move(renderComponent1));

	Node3D cube2;
	auto renderComponent2 = std::make_unique<RenderComponent>();
	renderComponent2->SetMaterial(material2);
	renderComponent2->SetMesh(cubeMesh);
	cube2.AddComponent(std::move(renderComponent2));
	cube2.transform.Translate(glm::vec3(2.0f, 0.0f, 0.0f));

	// Light
	Node3D lightCube;
	lightCube.transform.Translate(glm::vec3(1.0f, 2.0f, 1.0f));
	std::unique_ptr<LightComponent> lightComponent = std::make_unique<LightComponent>();
	lightComponent->SetColor(glm::vec3(1.0f, 0.8f, 1.0f));
	lightComponent->SetIntensity(1.0f);
	lightComponent->SetRadius(20.0f);
	lightCube.AddComponent(std::move(lightComponent));

	std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("./defaultVertex.glsl", "./lightFragment.glsl");
	std::shared_ptr<Material> lightMaterial = std::make_shared<Material>();
	lightMaterial->SetShader(lightShader);

	auto renderComponent = std::make_unique<RenderComponent>();
	renderComponent->SetMaterial(lightMaterial);
	renderComponent->SetMesh(cubeMesh);

	lightCube.AddComponent(std::move(renderComponent));

	glEnable(GL_DEPTH_TEST);
	RenderingManager::Init();


	float fpsCap = 144.0f;
	while (!glfwWindowShouldClose(window)) {
	
		deltaTime = glfwGetTime() - oldTime;
		if (deltaTime < 1.0f / fpsCap) continue;
		processInput(window);

		lightCube.transform.SetPosition(glm::vec3(cos(glfwGetTime()*1.2f)*3.0f, sin(glfwGetTime()*1.5f)*3.0f, sin(glfwGetTime()*2.0f)*3.0f));
		material1->SetVec3("viewPos", camera->GetPosition());
		material2->SetVec3("viewPos", camera->GetPosition());

		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderingManager::Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
		oldTime = glfwGetTime();
	}
	glfwTerminate();
	return 0;

}