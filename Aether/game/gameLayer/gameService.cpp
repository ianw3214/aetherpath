#include "gameService.hpp"

#include "game/gameLayer/gameLayer.hpp"
#include "game/gameLayer/entities/player/player.hpp"

Oasis::Reference<GameLayer> GameService::s_game;
GameSettings GameService::s_settings;

Oasis::Reference<Entity> GameService::GetSelectedEntity()
{
    return s_game->m_selected;
}

void GameService::TransferEntityToGame(Entity * entity)
{
    s_game->m_entities.emplace_back(entity);
    if (auto ref = Oasis::DynamicCast<PlayerEntity>(s_game->m_entities[s_game->m_entities.size() - 1]))
    {
        s_game->m_players.push_back(ref);
    }
}

void GameService::TransferEntityToGame(Oasis::Owned<Entity>& entity)
{
    s_game->m_entities.emplace_back();
    s_game->m_entities[s_game->m_entities.size() - 1] = std::move(entity);
    if (auto ref = Oasis::DynamicCast<PlayerEntity>(s_game->m_entities[s_game->m_entities.size() - 1]))
    {
        s_game->m_players.push_back(ref);
    }
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

Oasis::Reference<PlayerEntity> GameService::GetPlayerAt(float x, float y)
{
    for (Oasis::Reference<PlayerEntity> player : s_game->m_players)
    {
        if (player->Colliding(x, y))
        {
            return player;
        }
    }
    return nullptr;
}

void GameService::DestroyEntity(Oasis::Reference<Entity> entity)
{
    for (auto it = s_game->m_entities.begin(); it != s_game->m_entities.end(); ++it)
    {
        Oasis::Reference<Entity> e = *it;
        if (e == entity)
        {
            s_game->m_entities.erase(it);
            return;
        }
    }   
}