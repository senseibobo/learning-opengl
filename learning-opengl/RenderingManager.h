#pragma once
#include <glad/glad.h>
#include <vector>
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
class LightComponent;
class RenderComponent;
class RenderingManager
{
public:
	static struct alignas(16) Light {
		glm::vec4 position; // 16
		glm::vec4 color; // 16
		float radius; // 4
		float intensity; // 4
		float padding[2]; // 8
	};
	static struct alignas(16) LightBlock {
		int lightCount;
		int padding[3];
		Light lights[32];
	};
	static struct RenderCommand {
		uint64_t sortKey;
		Shader* shader;
		Mesh* mesh;
		Material* material;
		glm::mat4 transform;
	};

	static void Init();
	static void SetCamera(Camera* camera);
	static void Render();
	static void AddRenderComponent(RenderComponent* renderComponent);
	static void AddLightComponent(LightComponent* lightComponent);
	static void RemoveRenderComponent(RenderComponent* renderComponent);
	static void RemoveLightComponent(LightComponent* lightComponent);

private:
	static GLuint lightUBO;
	static Camera* camera;
	static std::vector<RenderComponent*> renderComponents;
	static std::vector<LightComponent*> lightComponents;
};

