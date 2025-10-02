#include "NodeManager.h"

void NodeManager::ProcessNodes(float deltaTime)
{
	std::vector<Node*> tNodes = std::vector<Node*>(Node::nodes);

	for (Node* node : tNodes)
	{
		if (node)
			node->Process(deltaTime);
	}
	Node::FreeQueuedObjects();
}
