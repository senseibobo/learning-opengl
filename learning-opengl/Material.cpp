#include "Material.h"


uint32_t Material::currentMaterialIndex = 0;

Material::Material()
{
	materialInfo.albedo = glm::vec3(1.0f, 1.0f, 1.0f);
	materialInfo.roughness = 0.2f;
	materialInfo.specular = 1.0f;
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

void Material::SetFloat(const std::string& uniformName, float value)
{
	floatUniforms[uniformName] = value;
}

void Material::SetAlbedo(const glm::vec3& albedo)
{
	materialInfo.albedo = albedo;
}


void Material::SetRoughness(float roughness)
{
	materialInfo.roughness = roughness;
}

void Material::SetSpecular(float specular)
{
	materialInfo.specular = specular;
}

void Material::SetAlbedoMap(std::shared_ptr<Texture2D> albedoMap)
{
	materialInfo.albedoMap = albedoMap;
}

void Material::SetRoughnessMap(std::shared_ptr<Texture2D> roughnessMap)
{
	materialInfo.roughnessMap = roughnessMap;
}

void Material::SetSpecularMap(std::shared_ptr<Texture2D> specularMap)
{
	materialInfo.specularMap = specularMap;
}

Shader* Material::GetShader()
{
	return shader.get();
}

void Material::Bind()
{
	shader->Use();
	
	// set material info
	shader->SetVec3("material.albedo", materialInfo.albedo);
	shader->SetFloat("material.roughness", materialInfo.roughness);
	shader->SetFloat("material.specular", materialInfo.specular);

	std::shared_ptr<Texture2D>
		albedoMap = Texture2D::WhiteFallbackTexture,
		roughnessMap = Texture2D::WhiteFallbackTexture,
		specularMap = Texture2D::WhiteFallbackTexture;

	if (materialInfo.albedoMap) albedoMap = materialInfo.albedoMap;
	if (materialInfo.roughnessMap) roughnessMap = materialInfo.roughnessMap;
	if (materialInfo.specularMap) specularMap = materialInfo.specularMap;

	SetTexture("material.albedoMap", albedoMap);
	SetTexture("material.roughnessMap", roughnessMap);
	SetTexture("material.specularMap", specularMap);

	// set texture2Ds
	int textureLocation = 0;
	
	for (std::pair<std::string, std::shared_ptr<Texture2D>> pair : texture2Ds)
	{
		shader->SetTexture(pair.first.c_str(), pair.second->ID, textureLocation);
		textureLocation += 1;
	}

	// set other uniforms
	for (std::pair<std::string, glm::vec3> pair : vec3Uniforms) shader->SetVec3(pair.first.c_str(), pair.second); // vec3
	for (std::pair<std::string, float> pair : floatUniforms) shader->SetFloat(pair.first.c_str(), pair.second); // float

	// TODO: int, whatever else

}
