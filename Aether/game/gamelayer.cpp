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

void GameService::DrawSprite(Oasis::Sprite * sprite, int z)
{
    RenderItem item{RenderItem::Type::SPRITE, 0.f, 0.f, z};
    item.m_sprite = sprite;
    s_gameLayer->DrawItem(item);
}

void GameService::DrawLine(float x1, float y1, float x2, float y2, int z)
{
    RenderItem item{RenderItem::Type::LINE, x1, y1, z};
    item.m_x2 = x2;
    item.m_y2 = y2;
    s_gameLayer->DrawItem(item);
}

void GameService::DrawCircle(float x, float y, float radius, int z)
{
    RenderItem item{RenderItem::Type::CIRCLE, x, y, z};
    item.m_radius = radius;
    s_gameLayer->DrawItem(item);
}

void GameService::DrawRect(float x, float y, float w, float h, int z)
{
    RenderItem item{RenderItem::Type::RECT, x, y, z};
    item.m_width = w;
    item.m_height = h;
    s_gameLayer->DrawItem(item);
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

    // Render the game
    std::sort(m_renderItems.begin(), m_renderItems.end(), [](const RenderItem& a, const RenderItem& b) -> bool {
        return a.m_z < b.m_z;
    });
    for (const RenderItem& item : m_renderItems)
    {
        switch(item.m_type)
        {
            case RenderItem::Type::SPRITE: {
                // Assume the x/y and other things are already set in the sprite
                Oasis::Renderer::DrawSprite(item.m_sprite);
            } break;
            case RenderItem::Type::LINE: {
                // TODO: Colours need to be adjustable
                Oasis::Renderer::DrawLine(item.m_x, item.m_y, item.m_x2, item.m_y2, Oasis::Colours::RED);
            } break;
            case RenderItem::Type::CIRCLE: {
                float last_x = item.m_x + item.m_radius;
                float last_y = item.m_y;
                constexpr unsigned int granularity = 20;
                for (unsigned int i = 0; i <= granularity; ++i)
                {
                    const float angle = 2.f * 3.14f * static_cast<float>(i) / static_cast<float>(granularity);
                    float next_x = item.m_x + std::cos(angle) * item.m_radius;
                    float next_y = item.m_y +  std::sin(angle) * item.m_radius;
                    // TODO: Colours need to be adjustable
                    Oasis::Renderer::DrawLine(last_x, last_y, next_x, next_y, Oasis::Colours::RED);
                    last_x = next_x;
                    last_y = next_y;
                }
            } break;
            case RenderItem::Type::RECT: {
                const float x = item.m_x;
                const float y = item.m_y;
                const float width = item.m_width;
                const float height = item.m_height;
                // TODO: Colours need to be adjustable
                Oasis::Renderer::DrawLine(x, y, x, y + height, Oasis::Colours::RED);
                Oasis::Renderer::DrawLine(x, y, x + width, y, Oasis::Colours::RED);
                Oasis::Renderer::DrawLine(x + width, y, x + width, y + height, Oasis::Colours::RED);
                Oasis::Renderer::DrawLine(x, y + height, x + width, y + height, Oasis::Colours::RED);
            } break;
            default: {
                Oasis::Console::AddLog("ERROR: Tried to render invalid render item");
            } break;
        }
    }
    m_renderItems.clear();
}