#include "select.hpp"

#include "game/gamelayer.hpp"
#include "game/camera/camera.hpp"
#include "game/entity/entity.hpp"
#include "game/entity/components/collisionComponent.hpp"

Ref<SelectLayer> SelectService::s_selectLayer = nullptr;

SelectLayer::SelectLayer()
    : m_selected(nullptr)
{
    SelectService::s_selectLayer = this;
}

void SelectLayer::Init() {}
void SelectLayer::Close() {}

bool SelectLayer::HandleEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        auto mouse = dynamic_cast<const Oasis::MousePressedEvent&>(event);
        for (Ref<Entity> entity : GameService::GetEntities())
        {
            if (auto collision = entity->GetComponent<CollisionComponent>())
            {
                const float x = CameraService::ScreenToRawX(mouse.GetX());
                const float y = CameraService::ScreenToRawY(mouse.GetY());
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
    return false;
}

void SelectLayer::Update() {}

void SelectService::Select(Ref<Entity> entity)
{
    s_selectLayer->m_selected = entity;
}

bool SelectService::Selected(Ref<Entity> entity)
{
    return s_selectLayer->m_selected == entity;
}

Ref<Entity> SelectService::GetSelected()
{
    return s_selectLayer->m_selected;
}