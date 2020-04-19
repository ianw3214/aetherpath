#include "ship.hpp"

#include <cmath>

#include "game/camera/camera.hpp"
#include "game/gameLayer/gameService.hpp"
#include "game/gameLayer/entities/universe/resource.hpp"

Ship::Ship(float speed, float mineRange, int ticksPerFuel, int gatherSpeed, int transferSpeed)
    : m_speed(speed)
    , m_mineRange(mineRange)
    , m_ticksPerFuel(ticksPerFuel)
    , m_gatherSpeed(gatherSpeed)
    , m_UIState(UIState::NONE)
    , m_state(State::IDLE)
    , m_fuelTickAccumulator(0)
    , m_targetX(0.f)
    , m_targetY(0.f)
    , PlayerEntity(0, 0, 0, 0, transferSpeed)
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
    RenderTransferRange();
    RenderTransferDots();
    Render();
    if (m_UIState == UIState::MINE)
    {
        // Render a circle to show the mining range
        constexpr float granularity = 30.f;
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

void Ship::Tick()
{
    PlayerEntity::Tick();
    if (m_state == State::MOVE)
    {
        m_fuelTickAccumulator++;
        while (m_fuelTickAccumulator >= m_ticksPerFuel)
        {
            m_fuelTickAccumulator -= m_ticksPerFuel;
            if (GetFuel() > 0)
            {
                int fuel_left = ConsumeFuel(1);
                if (fuel_left <= 0)
                {
                    // TODO: Alert player
                }
            }
        }
    }
    if (m_state == State::MINE && m_mineTarget)
    {
        int oxygen = m_mineTarget->GatherOxygen(m_gatherSpeed);
        int fuel = m_mineTarget->GatherFuel(m_gatherSpeed);
        int metal = m_mineTarget->GatherMetal(m_gatherSpeed);
        AddOxygen(oxygen);
        AddFuel(fuel);
        AddMetal(metal);
        if (oxygen + fuel + metal == 0)
        {
            ResetState();
            // TODO: Notification - done mining
        }
    }
    if (m_state == State::TRANSFER && m_transferTarget)
    {
        if (m_transferType == ResourceType::OXYGEN)
        {
            int amount = GetOxygen() < GetTransferSpeed() ? GetOxygen() : GetTransferSpeed();
            m_transferTarget->AddOxygen(amount);
            if (ConsumeOxygen(amount) == 0)
            {
                // TODO: Alert
                ResetState();
            }
        }
        if (m_transferType == ResourceType::FUEL)
        {
            int amount = GetFuel() < GetTransferSpeed() ? GetFuel() : GetTransferSpeed();
            m_transferTarget->AddFuel(amount);
            if (ConsumeFuel(amount) == 0)
            {
                // TODO: Alert
                ResetState();
            }
        }
        if (m_transferType == ResourceType::POPULATION)
        {
            int amount = GetPopulation() < GetTransferSpeed() ? GetPopulation() : GetTransferSpeed();
            m_transferTarget->AddPopulation(amount);
            if (ConsumePopulation(amount) == 0)
            {
                // TODO: Alert
                ResetState();
            }
        }
        if (m_transferType == ResourceType::METAL)
        {
            int amount = GetMetal() < GetTransferSpeed() ? GetMetal() : GetTransferSpeed();
            m_transferTarget->AddMetal(amount);
            if (ConsumeMetal(amount) == 0)
            {
                // TODO: Alert
                ResetState();
            }
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
    if (m_UIState == UIState::TRANSFER2)
    {
        m_UIState = UIState::NONE;
        TryTransfer(Camera::ScreenToRawX(static_cast<int>(x)), Camera::ScreenToRawY(static_cast<int>(y)));
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
    // Can't move if we don't have fuel ;)
    if (GetFuel() > 0)
    {
        m_state = State::MOVE;
        m_targetX = x;
        m_targetY = y;
    }
    else
    {
        // TODO: Alert the player of no fuel
    }
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

void Ship::TransferAction()
{
    ResetUIState();
    m_UIState = UIState::TRANSFER;
}

void Ship::TryTransfer(float x, float y)
{
    auto target = GameService::GetPlayerAt(x, y);
    if (target)
    {
        float x_offset = x - GetX();
        float y_offset = y - GetY();
        if (x_offset * x_offset + y_offset * y_offset <= TRANSFER_RADIUS * TRANSFER_RADIUS)
        {
            ResetState();
            m_state = State::TRANSFER;
            m_transferTarget = target;
        }
    }
}

void Ship::DeselectCallback()
{
    void ResetUIState();
}

void Ship::TransferResource(ResourceType type)
{
    if (m_state == State::TRANSFER) ResetState();
    m_transferType = type;
    m_UIState = UIState::TRANSFER2;
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
    if (!m_mineTarget || m_state != State::MINE) return;
    // Just draw a line for now
    float x1 = static_cast<float>(Camera::RawToScreenX(GetX()));
    float y1 = static_cast<float>(Camera::RawToScreenY(GetY()));
    float x2 = static_cast<float>(Camera::RawToScreenX(m_mineTarget->GetX()));
    float y2 = static_cast<float>(Camera::RawToScreenY(m_mineTarget->GetY()));
    // TODO: Render dot sprites for the path
    Oasis::Renderer::DrawLine(x1, y1, x2, y2, Oasis::Colours::RED);
}

void Ship::RenderTransferRange()
{
    if(m_UIState != UIState::TRANSFER2) return;
    // Render a circle to show the deploy range
    constexpr float granularity = 30.f;
    constexpr float pi = 3.141592653f;
    float last_x = static_cast<float>(Camera::RawToScreenX(std::cos(0.f) * Ship::TRANSFER_RADIUS + GetX()));
    float last_y = static_cast<float>(Camera::RawToScreenY(std::sin(0.f) * Ship::TRANSFER_RADIUS + GetY()));
    for (float i = 1; i <= granularity; ++i)
    {
        const float x = static_cast<float>(Camera::RawToScreenX(std::cos(i * 2 * pi / granularity) * Ship::TRANSFER_RADIUS + GetX()));
        const float y = static_cast<float>(Camera::RawToScreenY(std::sin(i * 2 * pi / granularity) * Ship::TRANSFER_RADIUS + GetY()));
        Oasis::Renderer::DrawLine(x, y, last_x, last_y, Oasis::Colour{1.f, 1.f, 0.f});
        last_x = x;
        last_y = y;
    }
}

void Ship::RenderTransferDots()
{
    if (!m_transferTarget || m_state != State::TRANSFER) return;
    // Just draw a line for now
    float x1 = static_cast<float>(Camera::RawToScreenX(GetX()));
    float y1 = static_cast<float>(Camera::RawToScreenY(GetY()));
    float x2 = static_cast<float>(Camera::RawToScreenX(m_transferTarget->GetX()));
    float y2 = static_cast<float>(Camera::RawToScreenY(m_transferTarget->GetY()));
    // TODO: Render dot sprites for the path
    Oasis::Renderer::DrawLine(x1, y1, x2, y2, Oasis::Colour{ 1.f, 0.4f, 0.f });
}

void Ship::ResetState()
{
    ResetUIState();
    m_state = State::IDLE;
    m_targetX = GetX();
    m_targetY = GetY();
    m_mineTarget = nullptr;
}

void Ship::ResetUIState()
{
    m_UIState = UIState::NONE;
}

MotherShip::MotherShip()
    : Ship(20.f, 200.f, 8, 1, 10)
{
    SetSprite("res/sprites/mothership.png");
}

FlagShip::FlagShip()
    : Ship(40.f, 250.f, 10, 2, 3)
{
    SetSprite("res/sprites/flagship.png");   
}

DroneShip::DroneShip()
    : Ship(100.f, 600.f, 8, 10, 1)
{
    SetSprite("res/sprites/droneship.png");
}

Scout::Scout()
    : Ship(220.f, 50.f, 20, 1, 5)
{
    SetSprite("res/sprites/scout.png");
}