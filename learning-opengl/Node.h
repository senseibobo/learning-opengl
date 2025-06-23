#pragma once
#include <iostream>
#include <vector>
#include <memory>
class Component;
class Node
{
public:
	Node();
	virtual ~Node() = default;
	void AddComponent(std::unique_ptr<Component> component);
private:
	std::vector<std::unique_ptr<Component>> components;
};

