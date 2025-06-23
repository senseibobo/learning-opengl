#pragma once
#include <glad/glad.h>
#include <vector>
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
class RenderComponent;
static class RenderingManager
{
public:
	static struct RenderCommand {
		uint64_t sortKey;
		Shader* shader;
		Mesh* mesh;
		Material* material;
		glm::mat4 transform;
	};

	static void SetCamera(Camera* camera);
	static void Render();
	static void AddRenderComponent(RenderComponent* renderComponent);
	static void RemoveRenderComponent(RenderComponent* renderComponent);

private:
	static Camera* camera;
	static std::vector<RenderComponent*> renderComponents;
};

