#pragma once
#include <vector>

class Node;
class Component
{
	friend class Node;
public:
	virtual ~Component() = default;
	Component();


	Node* GetOwner() const;
	virtual void Process(float delta) {}
	virtual void PhysicsProcess(float delta) {}

	void QueueFree();

protected:
	Node* owner;
};

