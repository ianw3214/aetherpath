#pragma once
#include "oasis.h"
#include "entity.hpp"

class Earth : public RenderEntity
{
public:
    Earth();

    virtual void Update() override;
private:
};