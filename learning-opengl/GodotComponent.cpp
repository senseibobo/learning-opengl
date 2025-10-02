#include "GodotComponent.h"
#include "UnityComponent.h"

void GodotComponent::Process(float delta)
{
	Node3D* owner3D = (Node3D*)owner;
	glm::vec3 position = owner3D->transform.GetPosition() + delta * direction * 100.0f;
	owner3D->transform.SetPosition(position);
	for (UnityComponent* unity : UnityComponent::unitys)
	{
		Node3D* unityOwner3D = (Node3D*)unity->GetOwner();
		glm::vec3 unityPosition = unityOwner3D->transform.GetPosition();
		if (glm::length((unityPosition + glm::vec3(0.0,3.0,0.0)) - position) < 5.0f)
		{
			unity->GetHit();
		}
	}
	if (glm::distance(glm::vec3(0.0, 0.0, 0.0), owner3D->transform.GetPosition()) > 200.0f)
	{
		owner3D->QueueFree();
	}
}

void GodotComponent::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}
