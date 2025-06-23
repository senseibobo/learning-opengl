#pragma once
#include "Node.h"
#include "Transform.h"
class Node3D : public Node
{
public:
	Node3D() : Node() {
		transform = Transform();
	};
	Transform transform;
private:
};

