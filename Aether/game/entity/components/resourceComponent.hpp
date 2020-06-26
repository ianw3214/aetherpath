#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

class ResourceComponent : public Component
{
public:
    ResourceComponent(Ref<Entity> entity, int population = 0, int oxygen = 0, int fuel = 0, int metal = 0);
    // virtual void Update(float delta) override;

    inline int GetPopulation() const { return m_population; }
    inline int GetOxygen() const { return m_oxygen; }
    inline int GetFuel() const { return m_fuel; }
    inline int GetMetal() const { return m_metal; }
private:
    int m_population;
    int m_oxygen;
    int m_fuel;
    int m_metal;
};