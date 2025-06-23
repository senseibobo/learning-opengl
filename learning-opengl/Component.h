#pragma once
#include "Node.h"
class Component
{
	friend class Node;
public:
	virtual ~Component() = default;
	Component();
protected:
	Node* owner;
};

