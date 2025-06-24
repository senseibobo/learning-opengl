#include "LightComponent.h"

glm::vec3 LightComponent::GetColor() const
{
    return color;
}

void LightComponent::SetColor(const glm::vec3& color)
{
    this->color = color;
}
