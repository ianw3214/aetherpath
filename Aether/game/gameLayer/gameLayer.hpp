#pragma once
#include "oasis.h"

#include <vector>

#include "entities/entity.hpp"

class PlayerEntity;

////////////////////////////////////////////////////////////////////////////////////////
class GameLayer : public Oasis::GameStateLayer
{
public:
    friend class GameService;
public:
    GameLayer();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;

    void AddPlayer(Entity * entity);
    void SelectEntity(Oasis::Reference<Entity> entity);
private:
    // Game entities
    std::vector<Oasis::Owned<Entity>> m_entities;
    std::vector<Oasis::Reference<PlayerEntity>> m_players;
    Oasis::Reference<Entity> m_selected;

    // Game clock
    float m_tickAccumulator;
    float m_dayAccumulator;
private:
    // Additional helper methods
    void GenerateGameWorld();
    void UpdateClockAndTick();
};