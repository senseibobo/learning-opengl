#include "UnityComponent.h"
#include "Camera.h"
#include "Node3D.h"
#include "Game.h"

std::vector<UnityComponent*> UnityComponent::unitys = std::vector<UnityComponent*>();
int UnityComponent::score = 0;

void UnityComponent::Process(float delta)
{
	Camera* currentCamera = Camera::currentCamera;
	Node3D* owner3D = (Node3D*)owner;
	glm::vec3 vectorToPlayer = currentCamera->GetPosition() - owner3D->transform.GetPosition();
	glm::vec3 dirToPlayer = glm::normalize(vectorToPlayer);
	float distToPlayer = glm::length(vectorToPlayer);
	if (distToPlayer < 0.5f)
		Game::over = true;
	owner3D->transform.SetPosition(owner3D->transform.GetPosition() + dirToPlayer * speed * delta);
	owner3D->transform.SetQuaternion(glm::quatLookAt(-dirToPlayer, glm::vec3(0, 1, 0)));
}

void UnityComponent::ProcessClick(const glm::vec3& position, const glm::vec3& direction)
{
	//Camera* currentCamera = Camera::currentCamera;
	//Node3D* owner3D = (Node3D*)owner;
	//glm::vec3 dirFromPlayer = glm::normalize(owner3D->transform.GetPosition() - currentCamera->GetPosition());
	//float dot = glm::dot(dirFromPlayer, direction);
	//std::cout << "Dot " << dot << "\n";
	//if (dot > 0.96f)
	//{
	//	score += 1;
	//	QueueFree();
	//}
}

void UnityComponent::GetHit()
{
	score += 1;
	QueueFree();
}
