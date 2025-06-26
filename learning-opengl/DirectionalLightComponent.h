#pragma once
#include "LightComponent.h"
class DirectionalLightComponent :
    public LightComponent
{
public:
    RenderingManager::Light GetLightStruct() override;
};

