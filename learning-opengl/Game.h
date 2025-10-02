#pragma once
#include "Node3D.h"
#include "Components.h"
class Game
{
public:
	static bool over;
	static void Init();
	static void Process(float deltaTime);
	static void AddGun();
private:
	static void AddObjects();
	static Node3D* AddShape(std::shared_ptr<Model> model, std::shared_ptr<Material> material, glm::vec3 position);
};

