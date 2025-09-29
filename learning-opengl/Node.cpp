#include "Node.h"

std::vector<Node*> Node::nodes = std::vector<Node*>();
std::vector<Node*> Node::queuedForFreeing = std::vector<Node*>();

Node::Node() {
	std::cout << "Node created: " << this << "\n";
	nodes.push_back(this);
}

Node::~Node() {
	std::cout << "Node destroyed: " << this << "\n";
	auto it = std::find(nodes.begin(), nodes.end(), this);
	if (it != nodes.end())
		nodes.erase(it);
}


void Node::AddComponent(std::unique_ptr<Component> component)
{
	if (!component)
		std::cout << "Error: Invalid component.\n";
	component->owner = this;
	components.push_back(std::move(component));
}

void Node::Process(float delta)
{
	for (auto& component : components)
	{
		component->Process(delta);
	}
}

void Node::PhysicsProcess(float delta)
{
}


void Node::FreeQueuedObjects()
{
	for (int i = 0; i < queuedForFreeing.size(); i++)
	{
		auto it = std::find(nodes.begin(), nodes.end(), queuedForFreeing[i]);
		if (it != nodes.end()) nodes.erase(it);
		delete queuedForFreeing[i];
	}
	queuedForFreeing.clear();
}

void Node::QueueFree()
{

	auto it = std::find(queuedForFreeing.begin(), queuedForFreeing.end(), this);
	if(it == queuedForFreeing.end())
		queuedForFreeing.push_back(this);
}
