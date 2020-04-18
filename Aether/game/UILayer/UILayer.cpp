#include "UILayer.hpp"

void UILayer::Init()
{
    m_cursor = Oasis::Sprite("res/icons/cursor.png");
}

void UILayer::Close()
{

}

bool UILayer::HandleEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::MOUSE_MOVE)
    {
        const Oasis::MouseMovedEvent& mouseEvent = dynamic_cast<const Oasis::MouseMovedEvent&>(event);
        float mouse_x = static_cast<float>(mouseEvent.GetX());
        float mouse_y = static_cast<float>(Oasis::WindowService::WindowHeight() - mouseEvent.GetY());
        m_cursor.SetPos(mouse_x, mouse_y - m_cursor.GetHeight());
    }
    return false;
}

void UILayer::Update() 
{
    Oasis::Renderer::DrawSprite(m_cursor);
}
