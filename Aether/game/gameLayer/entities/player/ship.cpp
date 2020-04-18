#include "ship.hpp"

#include <cmath>

#include "game/camera/camera.hpp"
#include "game/gameLayer/gameService.hpp"
#include "game/gameLayer/entities/universe/resource.hpp"

Ship::Ship(float speed, float mineRange)
    : m_speed(speed)
    , m_mineRange(mineRange)
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
            ResetState();
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

    RenderMoveDots();
    RenderMineDots();
    Render();
    if (m_UIState == UIState::MINE)
    {
        // Render a circle to show the mining range
        constexpr float granularity = 20.f;
        constexpr float pi = 3.141592653f;
        float last_x = static_cast<float>(Camera::RawToScreenX(std::cos(0.f) * m_mineRange + GetX()));
        float last_y = static_cast<float>(Camera::RawToScreenY(std::sin(0.f) * m_mineRange + GetY()));
        for (float i = 1; i <= granularity; ++i)
        {
            const float x = static_cast<float>(Camera::RawToScreenX(std::cos(i * 2 * pi / granularity) * m_mineRange + GetX()));
            const float y = static_cast<float>(Camera::RawToScreenY(std::sin(i * 2 * pi / granularity) * m_mineRange + GetY()));
            Oasis::Renderer::DrawLine(x, y, last_x, last_y, Oasis::Colour{1.f, 1.f, 0.f});
            last_x = x;
            last_y = y;
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
    if (m_UIState == UIState::MINE)
    {
        m_UIState = UIState::NONE;
        TryMine(Camera::ScreenToRawX(static_cast<int>(x)), Camera::ScreenToRawY(static_cast<int>(y)));
        return true;
    }
    return false;
}

void Ship::MoveAction()
{
    m_UIState = UIState::MOVE;
}

void Ship::TryMove(float x, float y)
{
    ResetState();
    m_state = State::MOVE;
    m_targetX = x;
    m_targetY = y;
}

void Ship::MineAction() 
{
    m_UIState = UIState::MINE;
}

void Ship::TryMine(float x, float y) 
{
    // Get the entity at the clicked location
    auto target = GameService::GetEntityAt(x, y);
    if (target)
    {
        if (auto resource = Oasis::DynamicCast<ResourceEntity>(target))
        {
            // Check if target is witihin range by comparing square distance
            const float x_offset = target->GetX() - GetX();
            const float y_offset = target->GetY() - GetY();
            if (x_offset * x_offset + y_offset * y_offset <= m_mineRange * m_mineRange)
            {
                ResetState();
                m_state = State::MINE;
                m_mineTarget = resource;
            }
        }
    }
}


void Ship::RenderMoveDots()
{
    if (m_state != State::MOVE) return;
    // Just draw a line for now
    float x1 = static_cast<float>(Camera::RawToScreenX(GetX()));
    float y1 = static_cast<float>(Camera::RawToScreenY(GetY()));
    float x2 = static_cast<float>(Camera::RawToScreenX(m_targetX));
    float y2 = static_cast<float>(Camera::RawToScreenY(m_targetY));
    // TODO: Render dot sprites for the path
    Oasis::Renderer::DrawLine(x1, y1, x2, y2, Oasis::Colours::GREEN);
}

void Ship::RenderMineDots()
{
    if (!m_mineTarget) return;
    // Just draw a line for now
    float x1 = static_cast<float>(Camera::RawToScreenX(GetX()));
    float y1 = static_cast<float>(Camera::RawToScreenY(GetY()));
    float x2 = static_cast<float>(Camera::RawToScreenX(m_mineTarget->GetX()));
    float y2 = static_cast<float>(Camera::RawToScreenY(m_mineTarget->GetY()));
    // TODO: Render dot sprites for the path
    Oasis::Renderer::DrawLine(x1, y1, x2, y2, Oasis::Colours::RED);
}

void Ship::ResetState()
{
    m_UIState = UIState::NONE;
    m_state = State::IDLE;
    m_targetX = GetX();
    m_targetY = GetY();
    m_mineTarget = nullptr;
}

FlagShip::FlagShip()
    : Ship(40.f)
{
    SetSprite("res/sprites/flagship.png");   
}

DroneShip::DroneShip()
    : Ship(100.f, 600.f)
{
    SetSprite("res/sprites/droneship.png");
}