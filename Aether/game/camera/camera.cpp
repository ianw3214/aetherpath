#include "camera.hpp"

Oasis::Reference<Camera> Camera::s_camera;

float Camera::ScreenToRawX(int x)
{
    const float scale = Camera::GetCamera()->GetScale();
    return static_cast<float>(x - Oasis::WindowService::WindowWidth() / 2) / scale + Camera::GetCamera()->GetX();

}

float Camera::ScreenToRawY(int y)
{
    const float scale = Camera::GetCamera()->GetScale();
    return static_cast<float>(Oasis::WindowService::WindowHeight() - y - Oasis::WindowService::WindowHeight() / 2) / scale + Camera::GetCamera()->GetY();
}

int Camera::RawToScreenX(float x)
{
    const float scale = Camera::GetCamera()->GetScale();
    const float window_width = static_cast<float>(Oasis::WindowService::WindowWidth());
    return (x - Camera::GetCamera()->GetX()) * scale + window_width / 2;
}

int Camera::RawToScreenY(float y)
{
    const float scale = Camera::GetCamera()->GetScale();
    float window_height = static_cast<float>(Oasis::WindowService::WindowHeight());
    return (y - Camera::GetCamera()->GetY()) * scale + window_height / 2;
}


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