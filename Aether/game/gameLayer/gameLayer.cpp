#include "gameLayer.hpp"

#include "entities/earth.hpp"

void GameLayer::Init()
{
    m_entities.push_back(new Earth());
}

void GameLayer::Close()
{

}

bool GameLayer::HandleEvent(const Oasis::Event& event)
{
    return false;
}

void GameLayer::Update() 
{
    for (Oasis::Reference<Entity> entity : m_entities)
    {
        entity->Update();
    }
}