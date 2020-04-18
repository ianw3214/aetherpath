#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/entity.hpp"

// -------------------------------------------------------------
// Player entities are entities that the player controls
class PlayerEntity : public RenderEntity
{
public:
    PlayerEntity() 
        : m_oxygen(0)
        , m_fuel(0)
        , m_population(0)
        , m_metal(0) 
    {}

    inline int GetOxygen() const { return m_oxygen; }
    inline int GetFuel() const { return m_fuel; }
    inline int GetPopulation() const { return m_population; }
    inline int GetMetal() const { return m_metal; }

private:
    int m_oxygen;
    int m_fuel;
    int m_population;
    int m_metal;
};