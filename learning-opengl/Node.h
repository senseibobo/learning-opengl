#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Component.h"
class Node
{
public:
	Node();
	virtual ~Node() = default;
	void AddComponent(std::unique_ptr<Component> component);
private:
	std::vector<std::unique_ptr<Component>> components;
};

