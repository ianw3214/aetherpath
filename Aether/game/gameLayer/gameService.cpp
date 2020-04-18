#include "gameService.hpp"

#include "game/gameLayer/gameLayer.hpp"

Oasis::Reference<GameLayer> GameService::s_game;

Oasis::Reference<Entity> GameService::GetSelectedEntity()
{
    return s_game->m_selected;
}