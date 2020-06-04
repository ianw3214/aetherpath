#include "gamelayer.hpp"
#include "entity/entity.hpp"

////////////////////////////////////////////////////////////
#include "entity/components/renderComponent.hpp"
#include "entity/components/collisionComponent.hpp"
////////////////////////////////////////////////////////////

Ref<GameLayer> GameService::s_gameLayer = nullptr;

void GameService::AddEntity(Entity * entity)
{
    s_gameLayer->m_entities.push_back(entity);
}

std::vector<Entity *>& GameService::GetEntities()
{
    return s_gameLayer->m_entities;
}

GameLayer::GameLayer()
{
    GameService::s_gameLayer = this;
}

void GameLayer::Init()
{
    ////////////////////////////////////////////////////////////
    Entity * test = new Entity();
    test->SetX(0.f);
    test->SetY(0.f);
    test->AddComponent(new RenderComponent(test, "res/sprites/scout.png", 200.f, 200.f));
    test->AddComponent(new CollisionComponent(test, Shape::GenerateRect(150.f, 100.f)));
    GameService::AddEntity(test);
    ////////////////////////////////////////////////////////////
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
    // Microseconds to seconds
    float delta = Oasis::WindowService::GetDeltaF() / 1000000.f;
    for (Ref<Entity> entity : m_entities)
    {
        entity->Update(delta);
    }
}