#pragma once
#include "oasis.h"

#include "game/gameLayer/entities/entity.hpp"

struct GameSettings
{
    int m_mapBorder;
    float m_densityPerSquareThousand;

    GameSettings()
        : m_mapBorder(10000)
        , m_densityPerSquareThousand(0.3f)
    {}
};

class GameLayer;
class GameService
{
    friend class GameLayer;
    static Oasis::Reference<GameLayer> s_game;
    static void SetGameLayer(Oasis::Reference<GameLayer> game) { s_game = game;}
public:
    static Oasis::Reference<Entity> GetSelectedEntity();
    static Oasis::Reference<Entity> GetEntityAt(float x, float y);
    static GameSettings GetGameSettings() { return GameSettings(); }
};