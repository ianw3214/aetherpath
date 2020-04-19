#include "base.hpp"

#include "game/gameLayer/entities/player/ship.hpp"
#include "game/gameLayer/gameService.hpp"

#include "game/alertLayer/alertService.hpp"

Base::Base(int o, int f, int p, int m, int t)
    : PlayerEntity(o, f, p, m, t)
    , m_uiState(UIState::NONE)
    , m_state(State::IDLE)
    , m_building(false)
    , m_shipToDeploy(nullptr)
{}

void Base::ResetUIState()
{
    m_uiState = UIState::NONE;
}

void Base::ResetState()
{
    ResetUIState();
    m_state = State::IDLE;
    m_shipToDeploy = nullptr;
}

void Base::CreateAction()
{
    ResetUIState();
    m_uiState = UIState::CREATE;
}

void Base::DeployAction()
{
    ResetUIState();
    m_uiState = UIState::DEPLOY;
}

void Base::TryDeploy(float x, float y)
{
    float x_offset = x - GetX();
    float y_offset = y - GetY();
    if (x_offset * x_offset + y_offset * y_offset <= DEPLOY_RADIUS * DEPLOY_RADIUS)
    {
        for (auto it = m_shipStorage.begin(); it != m_shipStorage.end(); ++it)
        {
			Oasis::Reference<Entity> entity = *it;
            if (entity == m_shipToDeploy)
            {
                auto ref = Oasis::DynamicCast<Ship>(*it);
                ref->InitializeShip(x, y);
                GameService::TransferEntityToGame(*it);
                m_shipStorage.erase(it);
                break;
            }
        }
    }
    ResetUIState();
}

void Base::TransferAction()
{
    ResetUIState();
    m_uiState = UIState::TRANSFER;
}

void Base::TryTransfer(float x, float y)
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

void Base::DeselectCallback()
{
    ResetUIState();
}

void Base::Update()
{
    if (m_uiState == UIState::DEPLOY2)
    {
        // Render a circle to show the deploy range
        constexpr float granularity = 30.f;
        constexpr float pi = 3.141592653f;
        float last_x = static_cast<float>(Camera::RawToScreenX(std::cos(0.f) * Base::DEPLOY_RADIUS + GetX()));
        float last_y = static_cast<float>(Camera::RawToScreenY(std::sin(0.f) * Base::DEPLOY_RADIUS + GetY()));
        for (float i = 1; i <= granularity; ++i)
        {
            const float x = static_cast<float>(Camera::RawToScreenX(std::cos(i * 2 * pi / granularity) * Base::DEPLOY_RADIUS + GetX()));
            const float y = static_cast<float>(Camera::RawToScreenY(std::sin(i * 2 * pi / granularity) * Base::DEPLOY_RADIUS + GetY()));
            Oasis::Renderer::DrawLine(x, y, last_x, last_y, Oasis::Colour{1.f, 1.f, 0.f});
            last_x = x;
            last_y = y;
        }
    }
    RenderTransferRange();
    RenderTransferDots();
    Render();
}

void Base::Tick()
{
    PlayerEntity::Tick();
    // Update the ship building if there is one
    if (!m_buildingQueue.empty())
    {
        auto& front = m_buildingQueue.front();
        front.m_elapsedTicks += 1;

        GameSettings settings = GameService::GetGameSettings();
        int target = static_cast<int>(SecondsToBuildShip(front.m_type) / settings.m_seconds_per_tick);
        if (front.m_elapsedTicks >= target)
        {
            Ship * ship;
            if (front.m_type == ShipType::MOTHERSHIP)
            {
                ship = new MotherShip();
            }
            else if (front.m_type == ShipType::FLAGSHIP)
            {
                ship = new FlagShip();
            }
            else if (front.m_type == ShipType::DRONESHIP)
            {
                ship = new DroneShip();
            }
            else if (front.m_type == ShipType::SCOUT)
            {
                ship = new Scout();
            }
            ship->InitializeShip(GetX(), GetY());
            m_shipStorage.emplace_back(ship);
            m_buildingQueue.pop_front();

            AlertService::Info("Ship built!");
        }
    }
    if (m_state == State::TRANSFER && m_transferTarget)
    {
        if (m_transferType == ResourceType::OXYGEN)
        {
            int amount = GetOxygen() < GetTransferSpeed() ? GetOxygen() : GetTransferSpeed();
            int capacity = m_transferTarget->GetOxygenCapacity() - m_transferTarget->GetOxygen();
            if (capacity <= amount && m_transferTarget->GetMetalCapacity() >= 0)
            {
                amount = capacity;
                AlertService::Info("Oxygen at capactiy");
                ResetState();
            }
            m_transferTarget->AddOxygen(amount);
            if (ConsumeOxygen(amount) == 0)
            {
                AlertService::Warning("All oxygen has been transferred");
                ResetState();
            }
        }
        if (m_transferType == ResourceType::FUEL)
        {
            int amount = GetFuel() < GetTransferSpeed() ? GetFuel() : GetTransferSpeed();
            int capacity = m_transferTarget->GetFuelCapacity() - m_transferTarget->GetFuel();
            if (capacity <= amount && m_transferTarget->GetMetalCapacity() >= 0)
            {
                amount = capacity;
                AlertService::Info("Fuel at capactiy");
                ResetState();
            }
            m_transferTarget->AddFuel(amount);
            if (ConsumeFuel(amount) == 0)
            {
                AlertService::Warning("All fuel has been transferred");
                ResetState();
            }
        }
        if (m_transferType == ResourceType::POPULATION)
        {
            int amount = GetPopulation() < GetTransferSpeed() ? GetPopulation() : GetTransferSpeed();
            int capacity = m_transferTarget->GetPopulationCapacity() - m_transferTarget->GetPopulation();
            if (capacity <= amount && m_transferTarget->GetMetalCapacity() >= 0)
            {
                amount = capacity;
                AlertService::Info("Population at capactiy");
                ResetState();
            }
            m_transferTarget->AddPopulation(amount);
            if (ConsumePopulation(amount) == 0)
            {
                AlertService::Warning("All population has been transferred");
                ResetState();
            }
        }
        if (m_transferType == ResourceType::METAL)
        {
            int amount = GetMetal() < GetTransferSpeed() ? GetMetal() : GetTransferSpeed();
            int capacity = m_transferTarget->GetMetalCapacity() - m_transferTarget->GetMetal();
            if (capacity <= amount && m_transferTarget->GetMetalCapacity() >= 0)
            {
                amount = capacity;
                AlertService::Info("Metal at capactiy");
                ResetState();
            }
            m_transferTarget->AddMetal(amount);
            if (ConsumeMetal(amount) == 0)
            {
                AlertService::Warning("All metal has been transferred");
                ResetState();
            }
        }
    }
}

bool Base::HandleClick(float x, float y)
{
    if (m_uiState == UIState::DEPLOY2)
    {
        TryDeploy(Camera::ScreenToRawX(static_cast<int>(x)), Camera::ScreenToRawY(static_cast<int>(y)));
        return true;
    }
    if (m_uiState == UIState::TRANSFER2)
    {
        m_uiState = UIState::NONE;
        TryTransfer(Camera::ScreenToRawX(static_cast<int>(x)), Camera::ScreenToRawY(static_cast<int>(y)));
        return true;
    }
    return false;
}

void Base::CreateShip(ShipType type)
{
    if (GetMetal() > ShipCost(type))
    {
        ConsumeMetal(ShipCost(type));
        m_buildingQueue.push_back(BuildingEntry{ type, 0 });
    }
    else
    {
        AlertService::Critical("Not enough metal to build ship");
    }
    ResetUIState();
}

void Base::ChooseShipToDeploy(Oasis::Reference<Ship> ship)
{
    m_uiState = UIState::DEPLOY2;
    m_shipToDeploy = Oasis::DynamicCast<Entity>(ship);
}

void Base::TransferResource(ResourceType type)
{
    if (m_state == State::TRANSFER) ResetState();
    m_transferType = type;
    m_uiState = UIState::TRANSFER2;
}

void Base::RenderTransferRange()
{
    if(m_uiState != UIState::TRANSFER2) return;
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

void Base::RenderTransferDots()
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

GoalBase::GoalBase(int o, int f, int p, int m, int t)
    : Base(o, f, p, m, t)
{
    SetSprite("res/sprites/planets/goal_base.png");
}

void GoalBase::Tick() 
{
    Base::Tick();

    GameSettings settings = GameService::GetGameSettings();
    // Check for win condition
    if (GetPopulation() >= settings.m_population_to_win)
    {
        AlertService::Win();
    }
}