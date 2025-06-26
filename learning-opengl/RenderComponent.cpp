#include "RenderComponent.h"



void RenderComponent::SetModel(std::shared_ptr<Model> model)
{
	this->model = model;
}

void RenderComponent::SetMaterial(std::shared_ptr<Material> material)
{
	this->material = material;
}

Material* RenderComponent::GetMaterial()
{
	return material.get();
}

std::shared_ptr<Model> RenderComponent::GetModel()
{
	return model;
}

glm::mat4 RenderComponent::GetTransformMatrix() const
{
	Node3D* node3d = dynamic_cast<Node3D*>(owner);
	if (!node3d)
	{
		std::cout << "It's not a node3d :(\n";
		return glm::mat4();
	}
	else
	{
		return node3d->transform.GetMatrix();
	}
}
