#include <algorithm>
#include "RenderComponent.h"
#include "LightComponent.h"
#include "RenderingManager.h"

std::vector<RenderComponent*> RenderingManager::renderComponents = std::vector<RenderComponent*>();
std::vector<LightComponent*> RenderingManager::lightComponents = std::vector<LightComponent*>();
GLuint RenderingManager::lightUBO = 0;
Camera* RenderingManager::camera = nullptr;

void RenderingManager::Init()
{
	glGenBuffers(1, &lightUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBlock), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void RenderingManager::SetCamera(Camera* newCamera)
{
	camera = newCamera;
}

void RenderingManager::Render()
{
	LightBlock lightBlock = {};
	lightBlock.lightCount = static_cast<int>(lightComponents.size());

	int i = 0;
	for (LightComponent* lightComponent : lightComponents)
	{
		Node* owner = lightComponent->GetOwner();
		Node3D* node3d = dynamic_cast<Node3D*>(owner);
		if (!node3d) continue;

		const Transform* lightTransform = &(node3d->transform);
		Light light = {};
		light.position = glm::vec4(lightTransform->GetPosition(), 1.0f);
		light.color = glm::vec4(lightComponent->GetColor(), 1.0f);
		light.intensity = lightComponent->GetIntensity();
		light.radius = lightComponent->GetRadius();
		light.padding[0] = 0.0f;
		light.padding[1] = 0.0f;
		lightBlock.lights[i] = light;
		i++;
		if (i == 32) break;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightBlock), &lightBlock);

	std::vector<RenderCommand> renderCommands;
	for (RenderComponent* renderComponent : renderComponents)
	{
		RenderCommand renderCommand;
		renderCommand.material = renderComponent->GetMaterial();
		renderCommand.shader = renderComponent->GetMaterial()->GetShader();
		renderCommand.mesh = renderComponent->GetMesh();
		renderCommand.transform = renderComponent->GetTransformMatrix();
		renderCommand.sortKey = (uint64_t(renderCommand.shader->ID) << 32 | uint64_t(renderCommand.material->ID));
		renderCommands.push_back(renderCommand);
	}
	auto begin = renderCommands.begin();
	auto end = renderCommands.end();
	auto compareFunc = [](const RenderCommand& rc1, const RenderCommand& rc2) {
		return rc1.sortKey > rc2.sortKey;
		};
	std::sort(begin, end, compareFunc);
	Shader* lastShader = nullptr;
	Material* lastMaterial = nullptr;
	for (const RenderCommand& renderCommand : renderCommands)
	{
		if (renderCommand.shader != lastShader)
		{
			renderCommand.shader->Use();
			renderCommand.shader->SetMat4("projection", camera->GetProjectionMatrix());
			renderCommand.shader->SetMat4("view", camera->GetViewMatrix());
			lastShader = renderCommand.shader; 
			glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightUBO);

		}
		if (renderCommand.material != lastMaterial)
		{
			renderCommand.material->Bind();
			lastMaterial = renderCommand.material;
		}

		renderCommand.shader->SetMat4("model", renderCommand.transform);
		
		glBindVertexArray(renderCommand.mesh->GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, renderCommand.mesh->GetVertexCount());
	}
}

void RenderingManager::AddRenderComponent(RenderComponent* renderComponent)
{
	renderComponents.push_back(renderComponent);
}

void RenderingManager::AddLightComponent(LightComponent* lightComponent)
{
	lightComponents.push_back(lightComponent);
}

void RenderingManager::RemoveRenderComponent(RenderComponent* renderComponent)
{
	auto begin = renderComponents.begin();
	auto end = renderComponents.end();
	auto it = std::find(begin, end, renderComponent);
	renderComponents.erase(it);
}

void RenderingManager::RemoveLightComponent(LightComponent* lightComponent)
{
	auto begin = lightComponents.begin();
	auto end = lightComponents.end();
	auto it = std::find(begin, end, lightComponent);
	lightComponents.erase(it);
}
