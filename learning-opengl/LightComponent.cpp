#include "LightComponent.h"

LightComponent::LightComponent()
{
    this->color = glm::vec3(1.0f, 1.0f, 1.0f);
    this->intensity = 1.0f;
    RenderingManager::AddLightComponent(this);
}

glm::vec3 LightComponent::GetColor() const
{
    return color;
}

float LightComponent::GetIntensity() const
{
    return intensity;
}

void LightComponent::SetColor(const glm::vec3& color)
{
    this->color = color;
}

void LightComponent::SetIntensity(float intensity)
{
    this->intensity = intensity;
}

RenderingManager::Light LightComponent::GetLightStruct()
{
    return RenderingManager::Light();
}
