#include "gamelayer.hpp"
#include "entity/entity.hpp"

////////////////////////////////////////////////////////////
#include "entity/components/renderComponent.hpp"
#include "entity/components/collisionComponent.hpp"
#include "entity/components/moveComponent.hpp"
////////////////////////////////////////////////////////////

#include "game/camera/camera.hpp"
#include "game/select/select.hpp"

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
    // test->AddComponent(new CollisionComponent(test, Shape::GenerateRect(150.f, 100.f)));
    test->AddComponent(new CollisionComponent(test, Shape::GenerateCircle(150.f)));
    test->AddComponent(new MoveComponent(test));
    GameService::AddEntity(test);
    ////////////////////////////////////////////////////////////
}

void GameLayer::Close()
{

}

bool GameLayer::HandleEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        auto mouseEvent = dynamic_cast<const Oasis::MousePressedEvent&>(event);

        // Make sure we aren't clicking on an entity
        bool over_entity = false;
        const float x = CameraService::ScreenToRawX(mouseEvent.GetX());
        const float y = CameraService::ScreenToRawY(mouseEvent.GetY());
        for (Ref<Entity> entity : m_entities)
        {
            if (auto component = entity->GetComponent<CollisionComponent>())
            {
                if (component->Colliding(x, y))
                {
                    over_entity = true;
                }
            }
        }
        // Move the selected entity if we are not clicking on another entity
        if (!over_entity)
        {
            if (Ref<Entity> entity = SelectService::GetSelected())
            {
                if (auto move = entity->GetComponent<MoveComponent>())
                {
                    move->Move(x, y);
                }
            }
        }
    }
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