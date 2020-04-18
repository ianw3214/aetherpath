#include "camera.hpp"

Oasis::Reference<Camera> Camera::s_camera;

Camera::Camera()
    : m_x(0.f)
    , m_y(0.f)
    , m_scale(1.f)
    , m_dragging(false)
{
    
}

void Camera::Init()
{
    s_camera = this;
}

void Camera::Close()
{
    s_camera = nullptr;
}

bool Camera::HandleEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        m_dragging = true;
        return true;
    }
    if (event.GetType() == Oasis::EventType::MOUSE_RELEASE)
    {
        m_dragging = false;
    }
    if (event.GetType() == Oasis::EventType::MOUSE_MOVE)
    {
        if (m_dragging)
        {
            const Oasis::MouseMovedEvent& mouseEvent = static_cast<const Oasis::MouseMovedEvent&>(event);
            const float x = static_cast<float>(mouseEvent.GetXOffset()) / m_scale;
            const float y = static_cast<float>(mouseEvent.GetYOffset()) / m_scale;
            m_x -= x;
            m_y += y;   // (Y is inverted)
        }
    }
    if (event.GetType() == Oasis::EventType::MOUSE_SCROLL)
    {
        const Oasis::MouseScrolledEvent& mouseEvent = static_cast<const Oasis::MouseScrolledEvent&>(event);
        if (mouseEvent.GetVerticalScroll() > 0)
        {
            m_scale *= 1.5f;
        }
        if (mouseEvent.GetVerticalScroll() < 0)
        {
            m_scale /= 1.5f;
        }
        return true;
    }
    return false;
}

void Camera::Update() 
{

}