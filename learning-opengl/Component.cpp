#include "Component.h"
#include "Node.h"


Component::Component()
{
	owner = nullptr;
}

Node* Component::GetOwner() const
{
	return owner;
}

void Component::QueueFree()
{
	owner->QueueFree();
}