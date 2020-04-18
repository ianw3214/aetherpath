#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"

class Earth : public PlayerEntity
{
public:
    Earth();

    virtual void Update() override;
private:
};