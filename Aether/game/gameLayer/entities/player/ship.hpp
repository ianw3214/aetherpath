#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"

class Ship : public PlayerEntity
{
public:
    Ship();

    virtual bool CanMove() const override { return true; }

    virtual void Update() override;

    virtual void TryMove() override;
private:
};