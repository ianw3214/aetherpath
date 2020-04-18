#pragma once
#include "oasis.h"

#include "game/gameLayer/entities/entity.hpp"

struct GameSettings
{
    int m_mapBorder;
    int m_densityPerSquareThousand;

    GameSettings()
        : m_mapBorder(4000)
        , m_densityPerSquareThousand(3)
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
    static GameSettings GetGameSettings() { return GameSettings(); }
};