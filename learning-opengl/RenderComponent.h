#pragma once
#include "Node3D.h"
#include "Model.h"
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
        model = nullptr;
        material = nullptr;
        RenderingManager::AddRenderComponent(this);
    };
    void SetModel(std::shared_ptr<Model> model);
    void SetMaterial(std::shared_ptr<Material> material);

    Material* GetMaterial();
    std::shared_ptr<Model> GetModel();
    glm::mat4 GetTransformMatrix() const;
private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;
};

