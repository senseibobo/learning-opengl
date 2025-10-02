#pragma once
#include "Component.h"
class PickupComponent :
    public Component
{
public:

    void Process(float delta) override;
private:
    float rot = 0.0f;
};

