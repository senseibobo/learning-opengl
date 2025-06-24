#include "Component.h"

Component::Component()
{
	owner = nullptr;
}

Node* Component::GetOwner() const
{
	return owner;
}
