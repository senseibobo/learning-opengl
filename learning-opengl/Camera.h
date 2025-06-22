#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& direction);
	glm::mat4 GetViewMatrix() const;
	void Move(const glm::vec3& moveVector);
	void Rotate(float angle, const glm::vec3& axis);
	void LookAt(const glm::vec3& targetPosition);
	glm::vec3 GetRightVector() const;
	glm::vec3 GetForwardVector() const;
	glm::vec3 GetUpVector() const;
	glm::vec3 GetPosition() const;
	void SetDirection(const glm::vec3& direction);
	void SetSpeed(float speed);
	float GetSpeed() const;
private:
	void updateVectors();
	float speed;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 rightVector;
	glm::vec3 upVector;
	glm::vec3 forwardVector;
};

