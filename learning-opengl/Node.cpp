#include "Node.h"
#include "Component.h"

Node::Node()
{

}

void Node::AddComponent(std::unique_ptr<Component> component)
{
	if (!component)
		std::cout << "Error: Invalid component.\n";
	components.push_back(std::move(component));
}
