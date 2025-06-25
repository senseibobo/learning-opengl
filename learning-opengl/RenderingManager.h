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
	struct alignas(16) Light {
		glm::vec4 position;
		glm::vec4 color;
		glm::vec4 direction;
		glm::vec4 params;
	};

	struct alignas(16) LightBlock {
		alignas(16) int lightCount;
		alignas(16) Light lights[16];
	};

	struct alignas(16) CameraBlock {
		glm::vec4 position;
		glm::vec4 direction;
		glm::mat4 view;
		glm::mat4 projection;
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
	static GLuint cameraUBO;
	static Camera* camera;
	static std::vector<RenderComponent*> renderComponents;
	static std::vector<LightComponent*> lightComponents;

	static void uploadLightData();
	static void uploadCameraData();
	static std::vector<RenderCommand> getRenderCommands();
};

