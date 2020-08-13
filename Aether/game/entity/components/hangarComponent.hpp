#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

#include <string>

class HangarComponent : public Component
{
public:
    HangarComponent(Ref<Entity> entity, int capacity = 10);
    virtual void Update(float delta) override;

    int GetNumShips() const { return m_ships; }

    bool CreateShip();
private:
    int m_capacity;
    int m_ships;
};