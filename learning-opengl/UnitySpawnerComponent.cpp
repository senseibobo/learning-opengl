#include "UnitySpawnerComponent.h"
#include "Node3D.h"
#include "RenderComponent.h"
#include "ModelLoader.h"
#include "UnityComponent.h"


void UnitySpawnerComponent::Process(float delta) {
	t += delta;
	if (t > 3.0f)
	{
		SpawnUnity();
		t = 0.0f;
	}
}

Node3D* UnitySpawnerComponent::SpawnUnity()
{
	Node3D* unityNode = new Node3D();

	float rand1 = (rand() % 10000) / 10000.0f;
	float rand2 = (rand() % 10000) / 10000.0f;

	unityNode->transform.SetPosition(glm::vec3((rand1-0.5f)*100.0f, 0.0f, (rand2-0.5f)*100.0f));

	std::unique_ptr<RenderComponent> renderComponent = std::make_unique<RenderComponent>();
	renderComponent->SetModel(ModelLoader::Load("unity_3d_logo.glb"));
	std::unique_ptr<UnityComponent> unityComponent = std::make_unique<UnityComponent>();

	unityNode->AddComponent(std::move(renderComponent));
	unityNode->AddComponent(std::move(unityComponent));
	return unityNode;
}