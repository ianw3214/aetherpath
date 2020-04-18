#pragma once
#include "oasis.h"

#include "game/gameLayer/entities/entity.hpp"

class GameLayer;
class GameService
{
    friend class GameLayer;
    static Oasis::Reference<GameLayer> s_game;
    static void SetGameLayer(Oasis::Reference<GameLayer> game) { s_game = game;}
public:
    static Oasis::Reference<Entity> GetSelectedEntity();
};