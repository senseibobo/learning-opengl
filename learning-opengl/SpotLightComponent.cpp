#include "SpotLightComponent.h"
#include "Node3D.h"

void SpotLightComponent::SetInnerAngle(float angle)
{
	this->innerAngle = angle;
	this->cosInnerAngle = glm::cos(angle);
}

float SpotLightComponent::GetInnerAngle() const
{
	return this->innerAngle;
}

void SpotLightComponent::SetOuterAngle(float angle)
{
	this->outerAngle = angle;
	this->cosOuterAngle = glm::cos(angle);
}

float SpotLightComponent::GetOuterAngle() const
{
	return this->outerAngle;
}

RenderingManager::Light SpotLightComponent::GetLightStruct()
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
	light.params = glm::vec4(2.0f, radius, cosInnerAngle, cosOuterAngle); // x-2 (spotlight) y-radius, z-cos(innerAngle) w-cos(outerAngle)
	light.position = glm::vec4(node3d->transform.GetPosition(), 1.0f);
	return light;
}
