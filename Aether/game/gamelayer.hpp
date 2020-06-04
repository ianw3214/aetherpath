#pragma once
#include "oasis.h"

#include <vector>

class Entity;

////////////////////////////////////////////////////////////////
class GameService
{
public:
    static void AddEntity(Entity * entity);
    static std::vector<Entity *>& GetEntities();
private:
    friend class GameLayer;
    static Ref<GameLayer> s_gameLayer;
};

////////////////////////////////////////////////////////////////
class GameLayer : public Oasis::GameStateLayer
{
    friend class GameService;
public:
    GameLayer();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    std::vector<Entity *> m_entities;
};