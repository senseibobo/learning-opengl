#pragma once
#include "Node3D.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
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
        shader = nullptr;
        RenderingManager::AddRenderComponent(this);
    };
    void SetMesh(Mesh* mesh);
    void SetShader(Shader* shader);
    void Draw(Camera* camera);

    Shader* GetShader();
private:
    Mesh* mesh;
    Shader* shader;
};

