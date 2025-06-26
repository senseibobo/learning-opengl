#pragma once
#include "LightComponent.h"
class PointLightComponent :
    public LightComponent
{

public:
    PointLightComponent() : LightComponent(), radius(32.0f) {};
    void SetRadius(float radius);

    float GetRadius() const;
    RenderingManager::Light GetLightStruct() override;
protected:
    float radius;
};

