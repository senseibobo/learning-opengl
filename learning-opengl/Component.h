#pragma once
class Node;
class Component
{
	friend class Node;
public:
	virtual ~Component() = default;
	Component();

	Node* GetOwner() const;

protected:
	Node* owner;
};

