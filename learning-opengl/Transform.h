#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
class Transform
{
public:
	Transform();
	Transform(const glm::vec3& position);
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

	void SetPosition(const glm::vec3& position);
	void SetEuler(const glm::vec3& euler);
	void SetQuaternion(const glm::quat& quaternion);
	void SetScale(const glm::vec3& scale);
	void LookAt(const glm::vec3& targetPosition);

	void Translate(const glm::vec3& translation);

	glm::vec3 GetPosition() const;
	glm::vec3 GetScale() const;
	glm::vec3 GetEuler() const;
	glm::quat GetQuaternion() const;
	glm::mat4 GetMatrix() const;

	glm::vec3 GetForwardVector() const;
	glm::vec3 GetRightVector() const;
	glm::vec3 GetUpVector() const;

private:
	void updateMatrix();

	glm::vec3 position;
	glm::quat quaternion;
	glm::vec3 euler;
	glm::vec3 scale;
	glm::mat4 matrix;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};

