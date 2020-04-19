#include "gameService.hpp"

#include "game/gameLayer/gameLayer.hpp"

Oasis::Reference<GameLayer> GameService::s_game;
GameSettings GameService::s_settings;

Oasis::Reference<Entity> GameService::GetSelectedEntity()
{
    return s_game->m_selected;
}

void GameService::TransferEntityToGame(Oasis::Owned<Entity>& entity)
{
    s_game->m_entities.emplace_back();
    s_game->m_entities[s_game->m_entities.size() - 1] = std::move(entity);
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