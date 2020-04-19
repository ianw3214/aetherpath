#pragma once
#include "oasis.h"

#include "game/gameLayer/entities/entity.hpp"

struct GameSettings
{
    // Gameplay settings
    float m_seconds_per_tick = 0.5f;
    float m_seconds_per_day = 5.f * 60.f; // 5 minutes
    int m_no_oxygen_death_chance = 5;   // 1 out of this number death chance

    // Multiplier can dictate game difficulty
    float m_resourceMultiplier = 1.f;
    int m_oxygen_floor = 0;
    int m_oxygen_range = 80;
    int m_fuel_floor = 10;
    int m_fuel_range = 100;
    int m_metal_floor = 10;
    int m_metal_range = 80;
    int m_asteroid_multiplier = 2;
    int m_planet_multiplier = 10;

    // Map generation settings
    int m_mapBorder = 10000;
    float m_densityPerSquareThousand = 0.3f;
    int m_meteoroid_weight = 50;
    int m_asteroid_weight = 30;
    int m_planet_weight = 20;

    int m_defaultEarthOxygen = 100;
    int m_defaultEarthFuel = 1000;
    int m_defaultltEarthPopulation = 10000;
    int m_defaultEarthMetal = 1000;

};

class GameLayer;
class GameService
{
    friend class DebugLayer;
    friend class GameLayer;
    static Oasis::Reference<GameLayer> s_game;
    static void SetGameLayer(Oasis::Reference<GameLayer> game) { s_game = game;}
public:
    static Oasis::Reference<Entity> GetSelectedEntity();
    static Oasis::Reference<Entity> GetEntityAt(float x, float y);
    static void TransferEntityToGame(Oasis::Owned<Entity>& entity);
    static GameSettings GetGameSettings() { return s_settings; }
private:
    static GameSettings s_settings;
};