#include "Node.h"

Node::Node()
{

}

void Node::AddComponent(std::unique_ptr<Component> component)
{
	if (!component)
		std::cout << "Error: Invalid component.\n";
	component->owner = this;
	components.push_back(std::move(component));
}
