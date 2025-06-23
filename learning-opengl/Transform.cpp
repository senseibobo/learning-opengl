#include "Transform.h"

Transform::Transform()
{
	this->position = glm::vec3(0.0f);
	this->euler = glm::vec3(0.0f);
	this->quaternion = glm::quat();
	this->scale = glm::vec3(1.0f);
	updateMatrix();
}

Transform::Transform(const glm::vec3& position)
{
	this->position = glm::vec3(position);
	this->euler = glm::vec3(0.0f);
	this->quaternion = glm::quat();
	this->scale = glm::vec3(1.0f);
	updateMatrix();
}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	this->position = position;
	this->scale = scale;
	SetEuler(rotation);
}

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
{
	this->position = position;
	this->scale = scale;
	SetQuaternion(rotation);
}


void Transform::SetPosition(const glm::vec3& position)
{
	this->position = position;
	updateMatrix();
}

void Transform::SetEuler(const glm::vec3& euler)
{
	this->euler = euler;
	quaternion = glm::quat(euler);
	updateMatrix();
}

void Transform::SetQuaternion(const glm::quat& quaternion)
{
	this->quaternion = quaternion;
	euler = glm::eulerAngles(quaternion);
	updateMatrix();
}

void Transform::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
	updateMatrix();
}

glm::vec3 Transform::GetPosition() const
{
	return position;
}

glm::vec3 Transform::GetEuler() const
{
	return euler;
}

glm::quat Transform::GetQuaternion() const
{
	return quaternion;
}

glm::vec3 Transform::GetScale() const
{
	return scale;
}

glm::mat4 Transform::GetMatrix() const
{
	return glm::mat4();
}

void Transform::updateMatrix()
{
	matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);
	matrix = glm::toMat4(quaternion) * matrix;
	matrix = glm::scale(matrix, scale);
}
