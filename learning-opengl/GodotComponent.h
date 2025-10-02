#pragma once
#include "Component.h"
#include "Node3D.h"
#include "glm/glm.hpp"
class GodotComponent : public Component
{
public:
	void Process(float delta) override;
	void SetDirection(glm::vec3 direction);
private:
	glm::vec3 direction;
};

