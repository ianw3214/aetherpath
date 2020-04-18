#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/entity.hpp"

class Ship : public PlayerEntity
{
public:
    Ship();

    virtual void Update() override;
private:
};