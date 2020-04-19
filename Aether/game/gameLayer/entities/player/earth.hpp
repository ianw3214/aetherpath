#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"

class Earth : public PlayerEntity
{
public:
    Earth(int o, int f, int p, int m);

    virtual void Update() override;
private:
};