#include "ship.hpp"

#include <cmath>

#include "game/camera/camera.hpp"

Ship::Ship(float speed)
    : m_speed(speed)
    , m_UIState(UIState::NONE)
    , m_state(State::IDLE)
    , m_targetX(0.f)
    , m_targetY(0.f)
{
    SetSprite("res/sprites/ship.png");
}

void Ship::InitializeShip(float x, float y)
{
    SetPos(x, y);
    m_targetX = x;
    m_targetY = y;
}

void Ship::Update()
{
    RenderMoveDots();
    Render();

    // Update movement (Assume linear line to target)
    if (m_targetX != GetX() || m_targetY != GetY())
    {
        const float x_offset = m_targetX - GetX();
        const float y_offset = m_targetY - GetY();
        const float delta = Oasis::WindowService::GetDelta();

        const float hypotenuse = std::sqrt(x_offset * x_offset + y_offset * y_offset);
        const float ratio = m_speed / hypotenuse * delta / 1000000.f;
        // Arrived
        if (ratio > 1.f)
        {
            SetX(m_targetX);
            SetY(m_targetY);
            m_state = State::IDLE;
            // TODO: Send an alert
        }
        // Move a teeny bit
        else
        {
            const float move_x = x_offset * ratio;
            const float move_y = y_offset * ratio;
            SetX(GetX() + move_x);
            SetY(GetY() + move_y);
        }
    }
}

bool Ship::HandleClick(float x, float y)
{
    if (m_UIState == UIState::MOVE)
    {
        m_UIState = UIState::NONE;
        TryMove(Camera::ScreenToRawX(static_cast<int>(x)), Camera::ScreenToRawY(static_cast<int>(y)));
        return true;
    }
    return false;
}

void Ship::MoveAction()
{
    if (m_UIState == UIState::NONE && m_state == State::IDLE)
    {
        m_UIState = UIState::MOVE;
    }
}

void Ship::TryMove(float x, float y)
{
    // Double check that we are in IDLE even though we probably checked already
    // I am just lazy and don't want mroe bugs randomly
    if (m_state == State::IDLE)
    {
        m_targetX = x;
        m_targetY = y;
    }
}

void Ship::RenderMoveDots()
{
    // Just draw a line for now
    float x1 = static_cast<float>(Camera::RawToScreenX(GetX()));
    float y1 = static_cast<float>(Camera::RawToScreenY(GetY()));
    float x2 = static_cast<float>(Camera::RawToScreenX(m_targetX));
    float y2 = static_cast<float>(Camera::RawToScreenY(m_targetY));
    // TODO: Render dot sprites for the path
    Oasis::Renderer::DrawLine(x1, y1, x2, y2, Oasis::Colours::GREEN);
}

FlagShip::FlagShip()
    : Ship(50.f)
{
    SetSprite("res/sprites/flagship.png");   
}