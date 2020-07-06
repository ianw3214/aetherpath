#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

///////////////////////////////////////////////////////////////
// public class to handle whether the game has been won or not
class GameWinSystem
{
public:
    static void Update();
    static void AddPopulation(unsigned int population);
private:
    static unsigned int s_totalPopulation;
};

///////////////////////////////////////////////////////////////
class ResourceComponent : public Component
{
public:
    ResourceComponent(Ref<Entity> entity, int population = 0, int oxygen = 0, int fuel = 0, int metal = 0, bool countsForGameWin = false);
    virtual void Update(float delta) override;

    inline int GetPopulation() const { return m_population; }
    inline int GetOxygen() const { return m_oxygen; }
    inline int GetFuel() const { return m_fuel; }
    inline int GetMetal() const { return m_metal; }

    void TransferResources(Ref<ResourceComponent> other);
private:
    int m_population;
    int m_oxygen;
    int m_fuel;
    int m_metal;

    // resource component properties
    bool m_countsForGameWin;

    bool m_transferring;
    Ref<ResourceComponent> m_transferTarget;
};