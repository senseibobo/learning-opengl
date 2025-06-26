#include <algorithm>
#include "RenderComponent.h"
#include "LightComponent.h"
#include "RenderingManager.h"

std::vector<RenderComponent*> RenderingManager::renderComponents = std::vector<RenderComponent*>();
std::vector<LightComponent*> RenderingManager::lightComponents = std::vector<LightComponent*>();
std::vector<RenderingManager::RenderCommand> RenderingManager::renderCommands = std::vector<RenderingManager::RenderCommand>();
GLuint RenderingManager::lightUBO = 0;
GLuint RenderingManager::cameraUBO = 0;
Camera* RenderingManager::camera = nullptr;

void RenderingManager::Init()
{
	glGenBuffers(1, &cameraUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraBlock), nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, cameraUBO);

	glGenBuffers(1, &lightUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBlock), nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, lightUBO);
	
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void RenderingManager::SetCamera(Camera* newCamera)
{
	camera = newCamera;
}


void RenderingManager::uploadLightData()
{
	LightBlock lightBlock = {};
	lightBlock.lightCount = static_cast<int>(lightComponents.size());

	int i = 0;
	for (LightComponent* lightComponent : lightComponents)
	{
		lightBlock.lights[i] = lightComponent->GetLightStruct();
		i++;
		if (i == 16) break;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightBlock), &lightBlock);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void RenderingManager::processModelNode(Model::Node* modelNode, const glm::mat4& parentTransform, Material* material)
{
	
	if (modelNode == nullptr)
	{
		std::cout << "Breaking the point\n";
		return;
	}

	glm::mat4 currentTransform = parentTransform * modelNode->localTransform;
	for (std::shared_ptr<Mesh> mesh : modelNode->meshes)
	{
		RenderCommand renderCommand;
		renderCommand.material = material;
		renderCommand.mesh = mesh.get();
		renderCommand.shader = material->GetShader();
		renderCommand.transform = currentTransform;
		renderCommand.sortKey = (uint64_t(renderCommand.shader->ID) << 32 | uint64_t(renderCommand.material->ID));
		renderCommands.push_back(renderCommand);
	}

	for (std::unique_ptr<Model::Node>& child : modelNode->children)
	{
		processModelNode(child.get(), currentTransform, material);
	}
}

const std::vector<RenderingManager::RenderCommand>& RenderingManager::getRenderCommands()
{
	renderCommands.clear();
	for (RenderComponent* renderComponent : renderComponents)
	{
		processModelNode(renderComponent->GetModel()->GetRootNode(), renderComponent->GetTransformMatrix(), renderComponent->GetMaterial());
	}
	auto begin = renderCommands.begin();
	auto end = renderCommands.end();
	auto compareFunc = [](const RenderCommand& rc1, const RenderCommand& rc2) {
		return rc1.sortKey > rc2.sortKey;
		};
	std::sort(begin, end, compareFunc);
	return renderCommands;
}


void RenderingManager::uploadCameraData()
{
	CameraBlock cameraBlock;
	cameraBlock.position = glm::vec4(camera->GetPosition(),1.0f);
	cameraBlock.direction = glm::vec4(camera->GetForwardVector(), 0.0f);
	cameraBlock.projection = camera->GetProjectionMatrix();
	cameraBlock.view = camera->GetViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraBlock), &cameraBlock);
}


void RenderingManager::Render()
{
	uploadLightData();
	uploadCameraData();

	Shader* lastShader = nullptr;
	Material* lastMaterial = nullptr;
	for (const RenderCommand& renderCommand : getRenderCommands())
	{
		if (renderCommand.shader != lastShader)
		{
			renderCommand.shader->Use();
			lastShader = renderCommand.shader; 
		}
		if (renderCommand.material != lastMaterial)
		{
			renderCommand.material->Bind();
			lastMaterial = renderCommand.material;
		}

		renderCommand.shader->SetMat4("model", renderCommand.transform);
		
		glBindVertexArray(renderCommand.mesh->GetVAO());
		glDrawElements(GL_TRIANGLES, renderCommand.mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
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
