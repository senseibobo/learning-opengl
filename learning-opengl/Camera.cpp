#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& direction)
{
	this->position = position;
	SetSpeed(10.0f);
	SetDirection(direction);
}

glm::mat4 Camera::GetViewMatrix() const
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(position, position+direction, glm::vec3(0.0f, 1.0f, 0.0f));
	return view;
}

void Camera::LookAt(const glm::vec3& targetPosition)
{
	SetDirection(glm::normalize(targetPosition - position));
}

glm::vec3 Camera::GetRightVector() const
{
	return rightVector;
}

glm::vec3 Camera::GetForwardVector() const
{
	return forwardVector;
}

glm::vec3 Camera::GetUpVector() const
{
	return upVector;
}

glm::vec3 Camera::GetPosition() const
{
	return this->position;
}

void Camera::SetDirection(const glm::vec3& direction)
{
	this->direction = direction;
	updateVectors();
}

void Camera::SetSpeed(float speed)
{
	this->speed = speed;
}

float Camera::GetSpeed() const
{
	return speed;
}

void Camera::updateVectors()
{
	forwardVector = direction;
	rightVector = glm::normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
	upVector = glm::normalize(glm::cross(forwardVector, rightVector));
}


void Camera::Move(const glm::vec3& moveVector)
{
	position += moveVector;
}

void Camera::Rotate(float angle, const glm::vec3& axis)
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, angle, axis);
	direction = rotationMatrix * glm::vec4(direction, 1.0f);
	updateVectors();
}
