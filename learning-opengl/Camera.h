#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
class Camera // TODO: turn it into a Component
{
public:
	Camera(const glm::vec3& position, const glm::vec3& direction);

	void Move(const glm::vec3& moveVector);
	void Rotate(float angle, const glm::vec3& axis);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void LookAt(const glm::vec3& targetPosition);

	void SetDirection(const glm::vec3& direction);
	void SetSpeed(float speed);
	void SetFov(float fov);

	glm::vec3 GetRightVector() const;
	glm::vec3 GetForwardVector() const;
	glm::vec3 GetUpVector() const;
	glm::vec3 GetPosition() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	float GetSpeed() const;
	float GetFov() const;
private:
	void updateVectors();
	void recalculateYawPitch();
	void recalculateDirection();
	float speed;

	float fov;

	float yaw;
	float pitch;
	
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 rightVector;
	glm::vec3 upVector;
	glm::vec3 forwardVector;
	
};

