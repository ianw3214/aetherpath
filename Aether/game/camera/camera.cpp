#include "camera.hpp"

Ref<Camera> CameraService::s_camera;

float CameraService::ScreenToRawX(int x)
{
    const float scale = s_camera->m_scale;
    return static_cast<float>(x - Oasis::WindowService::WindowWidth() / 2) / scale + s_camera->m_x;

}

float CameraService::ScreenToRawY(int y)
{
    const float scale = s_camera->m_scale;
    return static_cast<float>(Oasis::WindowService::WindowHeight() - y - Oasis::WindowService::WindowHeight() / 2) / scale + s_camera->m_y;
}

float CameraService::RawToScreenX(float x, float parallax)
{
    const float scale = s_camera->m_scale;
    const float window_width = static_cast<float>(Oasis::WindowService::WindowWidth());
    return (x - s_camera->m_x) / parallax * scale + window_width / 2;
}

float CameraService::RawToScreenY(float y, float parallax)
{
    const float scale = s_camera->m_scale;
    float window_height = static_cast<float>(Oasis::WindowService::WindowHeight());
    return (y - s_camera->m_y)  / parallax * scale + window_height / 2;
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
	CameraService::s_camera = this;
}

void Camera::Close()
{
    
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
            m_y -= y;
        }
    }
    if (event.GetType() == Oasis::EventType::MOUSE_SCROLL)
    {
        const Oasis::MouseScrolledEvent& mouseEvent = static_cast<const Oasis::MouseScrolledEvent&>(event);
        if (mouseEvent.GetVerticalScroll() > 0)
        {
            m_scale *= 1.5f;
            if (m_scale > 5.f) m_scale = 5.f;
        }
        if (mouseEvent.GetVerticalScroll() < 0)
        {
            m_scale /= 1.5f;
            if (m_scale < 0.05f) m_scale = .05f;
        }
        return true;
    }
    return false;
}

void Camera::Update() 
{

}