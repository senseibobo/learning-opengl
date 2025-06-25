#pragma once
#include <unordered_map>
#include <memory>
#include "Shader.h"
#include "Texture2D.h"
class Material
{
public:
	Material();

	void SetShader(std::shared_ptr<Shader> shader);
	void SetTexture(const std::string& uniformName, std::shared_ptr<Texture2D> texture);
	void SetVec3(const std::string& uniformName, const glm::vec3& value);
	void SetAlbedo(const glm::vec3& albedo);
	void SetRoughness(float roughness);

	Shader* GetShader();
	void Bind() const;

	uint32_t ID;
private:
	static uint32_t currentMaterialIndex;
	std::shared_ptr<Shader> shader;
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> texture2Ds;
	std::unordered_map<std::string, float> floatUniforms;
	std::unordered_map<std::string, glm::vec3> vec3Uniforms;

	Shader::MaterialInfo materialInfo;
};

