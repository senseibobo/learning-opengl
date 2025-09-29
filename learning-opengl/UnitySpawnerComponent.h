#pragma once
#include "Component.h"
#include <vector>
class Node3D;
class UnitySpawnerComponent :
    public Component
{

public:
    void Process(float delta) override;

private:
    float t = 0.0f;
    Node3D* SpawnUnity();
};

