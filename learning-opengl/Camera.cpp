#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& direction)
{
	this->position = position;
	this->fov = 60.0f;
	SetSpeed(3.0f);
	SetDirection(direction);
}

glm::mat4 Camera::GetViewMatrix() const
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(position, position+direction, glm::vec3(0.0f, 1.0f, 0.0f));
	return view;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.01f, 100.0f);;
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
	recalculateYawPitch();
}

void Camera::SetSpeed(float speed)
{
	this->speed = speed;
}

float Camera::GetSpeed() const
{
	return speed;
}

float Camera::GetFov() const
{
	return fov;
}

void Camera::SetFov(float fov)
{
	this->fov = fov;
}

void Camera::updateVectors()
{
	forwardVector = direction;
	rightVector = glm::normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
	upVector = glm::normalize(glm::cross(forwardVector, rightVector));
}

void Camera::recalculateYawPitch()
{
	yaw = glm::atan(direction.z, direction.x);
	pitch = glm::atan(direction.y, glm::length(glm::vec2(direction.x, direction.z)));
}

void Camera::recalculateDirection()
{
	float cosPitch = glm::cos(pitch);
	direction.x = glm::cos(yaw) * cosPitch;
	direction.z = glm::sin(yaw) * cosPitch;
	direction.y = glm::sin(pitch);
}


void Camera::Move(const glm::vec3& moveVector)
{
	position += moveVector;
}

void Camera::Rotate(float angle, const glm::vec3& axis)
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, angle, axis);
	SetDirection(glm::normalize(rotationMatrix * glm::vec4(direction, 1.0f)));
}

void Camera::RotateYaw(float angle)
{
	yaw += angle;
	recalculateDirection();
	updateVectors();
}

void Camera::RotatePitch(float angle)
{
	pitch += angle;
	pitch = glm::clamp(pitch, -1.5f, 1.5f);
	recalculateDirection();
	updateVectors();
}
