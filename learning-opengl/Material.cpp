#include "Material.h"


uint32_t Material::currentMaterialIndex = 0;

Material::Material()
{
	ID = ++currentMaterialIndex;
}

void Material::SetShader(std::shared_ptr<Shader> shader)
{
	this->shader = shader;
}

void Material::SetTexture(const std::string& uniformName, std::shared_ptr<Texture2D> texture)
{
	texture2Ds[uniformName] = texture;
}

Shader* Material::GetShader()
{
	return shader.get();
}

void Material::Bind() const
{
	shader->Use();
	int textureLocation = 0;
	for (std::pair<std::string, std::shared_ptr<Texture2D>> pair : texture2Ds)
	{
		shader->SetTexture(pair.first.c_str(), pair.second->ID, textureLocation);
		textureLocation += 1;
	}
}
