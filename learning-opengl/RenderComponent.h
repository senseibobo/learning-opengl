#pragma once
#include "Node3D.h"
#include "Mesh.h"
#include "Camera.h"
#include "Material.h"
#include "Component.h"
#include "RenderingManager.h"
class RenderComponent :
    public Component
{
public:
    ~RenderComponent() override = default;
    RenderComponent() : Component() 
    {
        mesh = nullptr;
        material = nullptr;
        RenderingManager::AddRenderComponent(this);
    };
    void SetMesh(std::shared_ptr<Mesh> mesh);
    void SetMaterial(std::shared_ptr<Material> material);

    Material* GetMaterial();
    Mesh* GetMesh();
    glm::mat4 GetTransformMatrix() const;
private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
};

