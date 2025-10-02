#pragma once
#include "Component.h"
#include "Node3D.h"
#include "GodotComponent.h"

class GunComponent : public Component
{
public:
	static GunComponent* gun;
	GunComponent() : Component()
	{
		gun = this;
		recoilT = 0.0;
	}
	void Process(float delta) override;
	void Shoot();
private:
	float recoilT;
};

