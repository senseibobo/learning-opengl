#include <algorithm>
#include "RenderingManager.h"
#include "RenderComponent.h"

std::vector<RenderComponent*> RenderingManager::renderComponents = std::vector<RenderComponent*>();
Camera* RenderingManager::camera = nullptr;

void RenderingManager::SetCamera(Camera* newCamera)
{
	camera = newCamera;
}

void RenderingManager::Render()
{
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

void RenderingManager::RemoveRenderComponent(RenderComponent* renderComponent)
{
	auto begin = renderComponents.begin();
	auto end = renderComponents.end();
	auto it = std::find(begin, end, renderComponent);
	renderComponents.erase(it);
}
