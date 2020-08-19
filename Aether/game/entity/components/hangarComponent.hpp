#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

#include <string>

class HangarComponent : public Component
{
public:
    HangarComponent(Ref<Entity> entity, int capacity = 10, int deployRange = 500);
    virtual void Update(float delta) override;

    int GetNumShips() const { return m_ships; }

    bool CreateShip();
    bool DeployShip(float x, float y);
private:
    // Hangar component properties
    int m_capacity;
    int m_deployRange;

    // Hangar component stats
    int m_ships;
};