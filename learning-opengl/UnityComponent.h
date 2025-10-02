#pragma once
#include "Component.h"
#include <glm/glm.hpp>
class UnityComponent : public Component
{
public:
	static std::vector<UnityComponent*> unitys;

	UnityComponent() : Component()
	{
		unitys.push_back(this);
	}
	~UnityComponent() {
		auto it = std::find(unitys.begin(), unitys.end(), this);
		if (it != unitys.end())
			unitys.erase(it);
	}
	void Process(float delta) override;
	void ProcessClick(const glm::vec3& position, const glm::vec3& direction);
	void GetHit();

	static int score;

private:
	float speed = 10.0f;
};

