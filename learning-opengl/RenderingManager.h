#pragma once
#include <glad/glad.h>
#include <vector>
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
class RenderComponent;
static class RenderingManager
{
public:
	static void SetCamera(Camera* camera);
	static void Render();
	static void AddRenderComponent(RenderComponent* renderComponent);
	static void RemoveRenderComponent(RenderComponent* renderComponent);

private:
	static Camera* camera;
	static std::vector<RenderComponent*> renderComponents;
};

