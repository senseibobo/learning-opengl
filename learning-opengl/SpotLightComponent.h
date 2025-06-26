#pragma once
#include "PointLightComponent.h"
class SpotLightComponent :
    public PointLightComponent
{
public:
    SpotLightComponent() : PointLightComponent(), 
        innerAngle(0.0f), outerAngle(0.0f), cosInnerAngle(0.0f), cosOuterAngle(0.0f) {};
    void SetInnerAngle(float angle);
    void SetOuterAngle(float angle);

    float GetInnerAngle() const;
    float GetOuterAngle() const;

    RenderingManager::Light GetLightStruct() override;
protected:
    float innerAngle;
    float outerAngle;
    float cosInnerAngle;
    float cosOuterAngle;
};

