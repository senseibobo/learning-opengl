#pragma once
#include <vector>
#include <memory>
#include "Mesh.h"
#include "Transform.h"
class Model
{
public:
	static std::shared_ptr<Model> Load(const char* modelPath);
	struct Node {
		glm::mat4 localTransform;
		std::vector<std::unique_ptr<Node>> children;
		std::vector<std::shared_ptr<Mesh>> meshes;
	};
	Node* GetRootNode();
	std::vector<std::shared_ptr<Mesh>> GetMeshPool();
	void SetRootNode(std::unique_ptr<Node> root);
	void SetMeshPool(std::vector<std::shared_ptr<Mesh>> meshPool);
	

private:
	std::vector<std::shared_ptr<Mesh>> meshPool;
	std::unique_ptr<Node> root;
};

