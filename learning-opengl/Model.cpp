#include "Model.h"
#include "ModelLoader.h"

std::shared_ptr<Model> Model::Load(const char* modelPath)
{
	return ModelLoader::Load(modelPath);
}

Model::Node* Model::GetRootNode()
{
	return root.get();
}

std::vector<std::shared_ptr<Mesh>> Model::GetMeshPool()
{
	return meshPool;
}

void Model::SetRootNode(std::unique_ptr<Node> root)
{
	this->root = std::move(root);
}

void Model::SetMeshPool(std::vector<std::shared_ptr<Mesh>> meshPool)
{
	this->meshPool = meshPool;
}
