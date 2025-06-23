#pragma once
class Node;
class Component
{
	friend class Node;
public:
	virtual ~Component() = default;
	Component();
protected:
	Node* owner;
};

