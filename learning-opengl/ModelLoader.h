#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Model.h"

class ModelLoader
{
public:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 UV;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};
	static std::shared_ptr<Model> Load(const char* modelPath);
	static std::vector<std::shared_ptr<Mesh>> meshes;
};

