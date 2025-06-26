#include "DirectionalLightComponent.h"
#include "Node3D.h"

RenderingManager::Light DirectionalLightComponent::GetLightStruct()
{
	Node3D* node3d = dynamic_cast<Node3D*>(owner);
	if (!node3d)
	{
		std::cerr << "Error: Light node isn't 3D.\n";
		return RenderingManager::Light();
	}

	RenderingManager::Light light;
	light.color = glm::vec4(color, intensity);
	light.direction = glm::vec4(node3d->transform.GetForwardVector(), 0.0f);
	light.params = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f); // x-1 (directional light)
	light.position = glm::vec4(node3d->transform.GetPosition(), 1.0f);
	return light;
}

