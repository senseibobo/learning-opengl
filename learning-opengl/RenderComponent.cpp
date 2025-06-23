#include "RenderComponent.h"



void RenderComponent::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void RenderComponent::SetShader(Shader* shader)
{
	this->shader = shader;
}

void RenderComponent::Draw(Camera* camera)
{
	Node3D* node3d = dynamic_cast<Node3D*>(owner);
	if (!node3d)
	{
		std::cout << "It's not a node3d :(\n";
	}
	else {
		shader->SetMat4("model", node3d->transform.GetMatrix());

		glBindVertexArray(mesh->GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertexCount());
		std::cout << "drawing\n";
	}
}

Shader* RenderComponent::GetShader()
{
	return shader;
}
