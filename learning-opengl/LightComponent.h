#pragma once
#include "Component.h"
#include <glm/glm.hpp>
class LightComponent :
    public Component
{
public:
    glm::vec3 GetColor() const;

    void SetColor(const glm::vec3& color);

private:
    glm::vec3 color;
};

