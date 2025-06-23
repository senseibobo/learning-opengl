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
	for (int i = 0; i < ((int)renderComponents.size()) - 1; i++)
	{
		for (int j = i + 1; j < ((int)renderComponents.size()); j++)
		{
			RenderComponent* rc1 = renderComponents[i];
			RenderComponent* rc2 = renderComponents[j];
			GLuint shader1 = rc1->GetShader()->ID;
			GLuint shader2 = rc2->GetShader()->ID;
			if (shader2 > shader1)
			{
				std::swap(rc1, rc2);
			}
		}
	}
	Shader* lastShader = nullptr;
	for (RenderComponent* renderComponent : renderComponents)
	{
		Shader* shader = renderComponent->GetShader();
		if (renderComponent->GetShader() != lastShader)
		{
			shader->Use();
			shader->SetMat4("projection", camera->GetProjectionMatrix());
			shader->SetMat4("view", camera->GetViewMatrix());
			lastShader = shader;
		}
		renderComponent->Draw(camera);
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
