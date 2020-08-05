#include "gamelayer.hpp"
#include "entity/entity.hpp"

////////////////////////////////////////////////////////////
#include "entity/components/renderComponent.hpp"
#include "entity/components/collisionComponent.hpp"
#include "entity/components/moveComponent.hpp"
#include "game/entity/components/resourceComponent.hpp"
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
#include "game/ui/UILayer.hpp"
////////////////////////////////////////////////////////////

#include "game/map/map.hpp"
#include "game/camera/camera.hpp"

#include <string>

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
    RenderItem item{RenderItem::Type::SPRITE, 0.f, 0.f, z, Oasis::Colours::WHITE};
    item.m_sprite = sprite;
    s_gameLayer->DrawItem(item);
}

void GameService::DrawLine(float x1, float y1, float x2, float y2, int z, const Oasis::Colour& colour)
{
    RenderItem item{RenderItem::Type::LINE, x1, y1, z, colour};
    item.m_x2 = x2;
    item.m_y2 = y2;
    s_gameLayer->DrawItem(item);
}

void GameService::DrawCircle(float x, float y, float radius, int z, const Oasis::Colour& colour)
{
    RenderItem item{RenderItem::Type::CIRCLE, x, y, z, colour};
    item.m_radius = radius;
    s_gameLayer->DrawItem(item);
}

void GameService::DrawRect(float x, float y, float w, float h, int z, const Oasis::Colour& colour)
{
    RenderItem item{RenderItem::Type::RECT, x, y, z, colour};
    item.m_width = w;
    item.m_height = h;
    s_gameLayer->DrawItem(item);
}

void GameService::Select(Ref<Entity> entity)
{
    s_gameLayer->m_selected = entity;
}

bool GameService::Selected(Ref<Entity> entity)
{
    return s_gameLayer->m_selected == entity;
}

Ref<Entity> GameService::GetSelected()
{
    return s_gameLayer->m_selected;
}

void GameService::SetMoveAction()
{
    OASIS_TRAP(s_gameLayer->m_selected);
    s_gameLayer->m_userActionState = GameLayer::UserActionState::MOVE;
}

void GameService::SetTransferAction()
{
    OASIS_TRAP(s_gameLayer->m_selected);
    s_gameLayer->m_userActionState = GameLayer::UserActionState::TRANSFER;
}


//////////////////////////////////////////////////
// Game layer
//////////////////////////////////////////////////

GameLayer::GameLayer()
    : m_selected(nullptr)
{
    GameService::s_gameLayer = this;
}

void GameLayer::Init()
{
    Map::GenerateMap();
}

void GameLayer::Close()
{

}

bool GameLayer::HandleEvent(const Oasis::Event& event)
{
    // Leave event handling of game logic in gamelayer for easier control
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
					// If we have a selected entity and we're clicking on another, transfer resources
					if (m_selected && m_selected != entity && m_userActionState == UserActionState::TRANSFER)
					{
						if (auto resource = entity->GetComponent<ResourceComponent>())
						{
							if (auto source = m_selected->GetComponent<ResourceComponent>())
							{
								source->TransferResources(resource);
							}
						}
					}
                }
            }
        }
        // Move the selected entity if we are not clicking on another entity
        if (!over_entity && m_userActionState == UserActionState::MOVE)
        {
            if (Ref<Entity> entity = m_selected)
            {
                if (auto move = entity->GetComponent<MoveComponent>())
                {
                    move->Move(x, y);
                }
            }
        }
        // No matter what we do, revert the user action state to none to reset
        m_userActionState = UserActionState::NONE;
        // NOTE: Not sure if I like having selection included in game layer yet
        // Handle selection of an entity if the click wasn't already handled
        for (Ref<Entity> entity : GameService::GetEntities())
        {
            if (auto collision = entity->GetComponent<CollisionComponent>())
            {
                const float x = CameraService::ScreenToRawX(mouseEvent.GetX());
                const float y = CameraService::ScreenToRawY(mouseEvent.GetY());
                if (collision->Colliding(x, y))
                {
                    // Assume entities can't overlap
                    if( m_selected != entity)
                    {
                        m_selected = entity;
                        return true;
                    }
                    return false;
                }
            }
        }
        // If we click no entities, then deselect
        m_selected = nullptr;
    }
    // Deselect the entity if the player presses escape
    // TODO: in the future this should also bring up a pause menu
    if (event.GetType() == Oasis::EventType::KEY_PRESSED)
    {
        const auto key = dynamic_cast<const Oasis::KeyPressedEvent&>(event);
        if (key.GetKey() == SDL_SCANCODE_ESCAPE)
        {
            if (m_selected)
            {
                m_selected = nullptr;
            }
        }
    }
    return false;
}

void GameLayer::Update()
{
    // Render the background first
    m_background.Render();

    // Microseconds to seconds
    float delta = Oasis::WindowService::GetDeltaF() / 1000000.f;
    // Update all systems
    GameWinSystem::Update();
    // Update all entity components
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
        const float x = item.m_x;
        const float y = item.m_y;
        
        switch(item.m_type)
        {
            case RenderItem::Type::SPRITE: {
                // TODO: Consider moving this into engine code?
                // Skip rendering if the sprite is off screen
                if (x + item.m_width < 0 || x > Oasis::WindowService::WindowWidth())
                {
                    if (y + item.m_height < 0 || y > Oasis::WindowService::WindowHeight())
                    {
                        continue;
                    }
                }
                // Assume the x/y and other things are already set in the sprite
                Oasis::Renderer::DrawSprite(item.m_sprite);
            } break;
            case RenderItem::Type::LINE: {
                // Skip rendering if the sprite is off screen
                const float width = static_cast<float>(Oasis::WindowService::WindowWidth());
                const float height = static_cast<float>(Oasis::WindowService::WindowHeight());
                if ((x < 0 && item.m_x2 < 0) || (x > width && item.m_x2 > width))
                {
                    continue;
                }
                if ((y < 0 && item.m_y2 < 0) || (y > height && item.m_y2 > height))
                {
                    continue;
                }
                Oasis::Renderer::DrawLine(item.m_x, item.m_y, item.m_x2, item.m_y2, item.m_colour);
            } break;
            case RenderItem::Type::CIRCLE: {
                // Skip rendering if the sprite is off screen
                if (x + item.m_radius < 0 || x - item.m_radius > Oasis::WindowService::WindowWidth())
                {
                    if (y + item.m_radius < 0 || y - item.m_radius > Oasis::WindowService::WindowHeight())
                    {
                        continue;
                    }
                }
                // Draw the circle as a line strip
                constexpr unsigned int granularity = 20;
                float * points = new float[(granularity + 1) * 2];
                points[0] = item.m_x + item.m_radius;
                points[1] = item.m_y;
                for (unsigned int i = 1; i <= granularity; ++i)
                {
                    const float angle = 2.f * 3.14f * static_cast<float>(i) / static_cast<float>(granularity);
                    points[i * 2 + 0] = item.m_x + std::cos(angle) * item.m_radius;
                    points[i * 2 + 1] = item.m_y +  std::sin(angle) * item.m_radius;
                }
                Oasis::Renderer::DrawLineStrip(points, granularity + 1, item.m_colour);
            } break;
            case RenderItem::Type::RECT: {
                const float width = item.m_width;
                const float height = item.m_height;
                if (x + width< 0 || x > Oasis::WindowService::WindowWidth())
                {
                    if (y + height < 0 || y > Oasis::WindowService::WindowHeight())
                    {
                        continue;
                    }
                }
                Oasis::Renderer::DrawLine(x, y, x, y + height, item.m_colour);
                Oasis::Renderer::DrawLine(x, y, x + width, y, item.m_colour);
                Oasis::Renderer::DrawLine(x + width, y, x + width, y + height, item.m_colour);
                Oasis::Renderer::DrawLine(x, y + height, x + width, y + height, item.m_colour);
            } break;
            default: {
                Oasis::Console::AddLog("ERROR: Tried to render invalid render item");
            } break;
        }
    }
    m_renderItems.clear();
}