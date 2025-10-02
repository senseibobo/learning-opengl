#include "PickupComponent.h"
#include "Node3D.h"
#include "Camera.h"
#include "Game.h"


void PickupComponent::Process(float delta)
{
	Node3D* owner3D = static_cast<Node3D*>(owner);
	owner3D->transform.SetEuler(glm::vec3(0.0, rot, 0.0));
	rot += delta;
	glm::vec3 camPos = Camera::currentCamera->GetPosition();
	glm::vec3 pickupPos = owner3D->transform.GetPosition();
	if (glm::distance(camPos, pickupPos) < 2.0f)
	{
		Game::AddGun();
		QueueFree();
	}
}
