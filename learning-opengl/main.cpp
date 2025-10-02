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
#include "SpotLightComponent.h"
#include "DirectionalLightComponent.h"
#include "UnitySpawnerComponent.h"
#include "UnityComponent.h"
#include "assimp/Importer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GUIManager.h"
#include "Game.h"


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
	if (Game::over) return;
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (Game::over) return;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		if (GunComponent::gun)
		{
			GunComponent::gun->Shoot();
		}
	}
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
	if (Game::over) return;
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Nije uspelo iniciranje gladovanja :(\n";
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "VERSION: " << version << "\n";
	std::cout << "GLSL VERSION: " << glslVersion << "\n";


	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.5f, -10.0f);
	glm::vec3 cameraDirection = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - cameraPosition);
	camera = new Camera(cameraPosition, cameraDirection);

	Material::InitDefaultMaterial();
	Texture2D::InitWhiteFallbackTexture();
	RenderingManager::SetCamera(camera);
	RenderingManager::Init();
	GUIManager::Init();
	Game::Init();

	float fpsCap = 144.0f;
	while (!glfwWindowShouldClose(window)) {
	
		deltaTime = glfwGetTime() - oldTime;
		if (deltaTime < 1.0f / fpsCap) continue;
		processInput(window);
		Game::Process(deltaTime);


		//spotLightCube->transform.SetPosition(glm::vec3(cos(glfwGetTime()*1.2f)*3.0f, sin(glfwGetTime()*1.5f)*3.0f, sin(glfwGetTime()*2.0f)*3.0f));
		//spotLightCube->transform.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		RenderingManager::Render();
		GUIManager::Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
		oldTime = glfwGetTime();
	}
	glfwTerminate();
	return 0;

}