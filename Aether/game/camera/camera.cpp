#include "camera.hpp"

Oasis::Reference<Camera> Camera::s_camera;

Camera::Camera()
    : m_x(0.f)
    , m_y(0.f)
    , m_scale(1.f)
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
    return false;
}

void Camera::Update() 
{

}