#include <iostream>
#include "ModelLoader.h"


std::vector<std::shared_ptr<Mesh>> ModelLoader::meshes = std::vector<std::shared_ptr<Mesh>>();


glm::mat4 ConvertAssimpMatrix(const aiMatrix4x4& m) {
    return glm::mat4(
        m.a1, m.b1, m.c1, m.d1,
        m.a2, m.b2, m.c2, m.d2,
        m.a3, m.b3, m.c3, m.d3,
        m.a4, m.b4, m.c4, m.d4
    );
}

std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<ModelLoader::Vertex> vertices;
    std::vector<uint32_t> indices;
    indices.reserve(mesh->mNumFaces * 3);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        ModelLoader::Vertex vertex;
        // position
        vertex.position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z);
        // normals
        if(mesh->HasNormals())
            vertex.normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        // UVs
        if (mesh->mTextureCoords[0])
            vertex.UV = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        // tangents and bitangents
        if (mesh->HasTangentsAndBitangents())
        {
            vertex.tangent = glm::vec3(
                mesh->mTangents[i].x,
                mesh->mTangents[i].y,
                mesh->mTangents[i].z
            );
            vertex.bitangent = glm::vec3(
                mesh->mBitangents[i].x,
                mesh->mBitangents[i].y,
                mesh->mBitangents[i].z
            );
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    static_assert(sizeof(ModelLoader::Vertex) == sizeof(float) * 14, "Wrong size");
    float* vertexData = reinterpret_cast<float*>(vertices.data());
    uint32_t* indexData = reinterpret_cast<uint32_t*>(indices.data());

    std::shared_ptr<Mesh> modelMesh = std::make_shared<Mesh>(
        vertexData, 
        indexData,
        vertices.size(),
        indices.size());
    return modelMesh;
}


std::unique_ptr<Model::Node> ProcessNode(aiNode* node, const aiScene* scene)
{
    std::unique_ptr<Model::Node> modelNode = std::make_unique<Model::Node>();
    modelNode->localTransform = ConvertAssimpMatrix(node->mTransformation);
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        std::shared_ptr<Mesh> modelMesh = ProcessMesh(mesh, scene);
        modelNode->meshes.push_back(modelMesh);
    }
    for (int i = 0; i < node->mNumChildren; i++)
    {
        aiNode* child = node->mChildren[i];
        std::unique_ptr<Model::Node> modelChild = ProcessNode(child, scene);
        modelNode->children.push_back(std::move(modelChild));
    }
    return std::move(modelNode);
}


std::shared_ptr<Model> processScene(const aiScene* scene)
{
    std::shared_ptr<Model> model = std::make_shared<Model>();
    ModelLoader::meshes.clear();
    std::unique_ptr<Model::Node> rootNode = ProcessNode(scene->mRootNode, scene);
    model->SetRootNode(std::move(rootNode));
    return model;
}


std::shared_ptr<Model> ModelLoader::Load(const char* modelPath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_JoinIdenticalVertices |
        aiProcess_CalcTangentSpace);

    if (scene == nullptr)
    {
        std::cerr << importer.GetErrorString()<<"\n";
        return nullptr;
    }

    return processScene(scene);
}
