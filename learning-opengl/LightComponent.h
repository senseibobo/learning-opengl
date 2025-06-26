#pragma once
#include "Component.h"
#include "RenderingManager.h"
#include <glm/glm.hpp>
class LightComponent :
    public Component
{
public:
    ~LightComponent() override = default;
    LightComponent();


    glm::vec3 GetColor() const;
    float GetIntensity() const;

    void SetColor(const glm::vec3& color);
    void SetIntensity(float intensity);

    virtual RenderingManager::Light GetLightStruct();

protected:
    glm::vec3 color;
    float intensity;
};

