#include "Material.h"


uint32_t Material::currentMaterialIndex = 0;

Material::Material()
{
	materialInfo.albedo = glm::vec3(1.0f, 0.0f, 0.0f);
	materialInfo.roughness = 0.00f;
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

void Material::SetVec3(const std::string& uniformName, const glm::vec3& value)
{
	vec3Uniforms[uniformName] = value;
}

void Material::SetAlbedo(const glm::vec3& albedo)
{
	materialInfo.albedo = albedo;
}


void Material::SetRoughness(float roughness)
{
	materialInfo.roughness = roughness;
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
	for (std::pair<std::string, glm::vec3> pair : vec3Uniforms)
		shader->SetVec3(pair.first.c_str(), pair.second);
	shader->SetVec3("material.albedo", materialInfo.albedo);
	shader->SetFloat("material.roughness", materialInfo.roughness);
}
