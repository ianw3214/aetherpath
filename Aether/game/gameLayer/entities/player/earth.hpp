#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/base.hpp"

class Earth : public Base
{
public:
    Earth(int o, int f, int p, int m);

    virtual void Update() override;
private:
};