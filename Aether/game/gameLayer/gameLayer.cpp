#include "gameLayer.hpp"

#include "entities/earth.hpp"

GameLayer::GameLayer()
    : m_entities()
    , m_selected(nullptr)
{

}

void GameLayer::Init()
{
    m_entities.push_back(new Earth());
}

void GameLayer::Close()
{

}

bool GameLayer::HandleEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        const Oasis::MousePressedEvent& mouseEvent = dynamic_cast<const Oasis::MousePressedEvent&>(event);
        // try to select a unit
        bool selected = false;
        for (Oasis::Reference<Entity> entity : m_entities)
        {
            Oasis::Reference<RenderEntity> renderEntity = Oasis::DynamicCast<RenderEntity>(entity);
            if (renderEntity)
            {
                float x = static_cast<float>(mouseEvent.GetX() + Camera::GetCamera()->GetX() - Oasis::WindowService::WindowWidth() / 2);
				// this is such lazy code but I'm a lazy person so whatever
                float y = static_cast<float>(Oasis::WindowService::WindowHeight() - mouseEvent.GetY() + Camera::GetCamera()->GetY() - Oasis::WindowService::WindowHeight() / 2);
                float scale = Camera::GetCamera()->GetScale();
                if (renderEntity->Colliding(x / scale, y / scale))
                {
                    SelectEntity(Oasis::DynamicCast<Entity>(renderEntity));
                    selected = true;
                    break;
                }
            }
        }
        if (!selected)
        {
            SelectEntity(nullptr);
        }
    }
    return false;
}

void GameLayer::Update() 
{
    for (Oasis::Reference<Entity> entity : m_entities)
    {
        entity->Update();
    }
}

void GameLayer::SelectEntity(Oasis::Reference<Entity> entity)
{
    // Passing in a null entity will just deselct it
    if (m_selected)
    {
        m_selected->Deselect();
    }
    m_selected = entity;
    if (m_selected)
    {
        entity->Select();
    }
}