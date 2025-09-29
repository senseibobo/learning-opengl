#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Component.h"
class Node
{
public:
	static std::vector<Node*> nodes;
	Node();
	virtual ~Node();

	void AddComponent(std::unique_ptr<Component> component);
	template <typename T>
	T* GetComponent() {
		for (auto& c : components) {
			if (auto casted = dynamic_cast<T*>(c.get())) {
				return casted;
			}
		}
	}
	virtual void Process(float delta);
	virtual void PhysicsProcess(float delta);
	void QueueFree();
	static void FreeQueuedObjects();
private:
	std::vector<std::unique_ptr<Component>> components;
	static std::vector<Node*> queuedForFreeing;
};

