#include "gameService.hpp"

#include "game/gameLayer/gameLayer.hpp"

Oasis::Reference<GameLayer> GameService::s_game;

Oasis::Reference<Entity> GameService::GetSelectedEntity()
{
    return s_game->m_selected;
}

Oasis::Reference<Entity> GameService::GetEntityAt(float x, float y)
{
    for (Oasis::Reference<Entity> e : s_game->m_entities)
    {
        if (auto entity = Oasis::DynamicCast<RenderEntity>(e))
        {
            if (entity->Colliding(x, y))
            {
                return e;
            }
        }
    }
    return nullptr;
}