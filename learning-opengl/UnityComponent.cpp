#include "UnityComponent.h"
#include "Camera.h"
#include "Node3D.h"

std::vector<UnityComponent*> UnityComponent::unitys = std::vector<UnityComponent*>();

void UnityComponent::Process(float delta)
{
	Camera* currentCamera = Camera::currentCamera;
	Node3D* owner3D = (Node3D*)owner;
	glm::vec3 dirToPlayer = glm::normalize(currentCamera->GetPosition() - owner3D->transform.GetPosition());
	owner3D->transform.SetPosition(owner3D->transform.GetPosition() + dirToPlayer * speed * delta);
	owner3D->transform.SetQuaternion(glm::quatLookAt(-dirToPlayer, glm::vec3(0, 1, 0)));
}

void UnityComponent::ProcessClick(const glm::vec3& position, const glm::vec3& direction)
{
	Camera* currentCamera = Camera::currentCamera;
	Node3D* owner3D = (Node3D*)owner;
	glm::vec3 dirFromPlayer = glm::normalize(owner3D->transform.GetPosition() - currentCamera->GetPosition());
	float dot = glm::dot(dirFromPlayer, direction);
	std::cout << "Dot " << dot << "\n";
	if (dot > 0.96f)
	{
		QueueFree();
	}
}
