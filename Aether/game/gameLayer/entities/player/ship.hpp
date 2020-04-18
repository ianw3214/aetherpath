#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"

class Ship : public PlayerEntity
{
public:
    Ship();

    virtual void Update() override;
private:
};