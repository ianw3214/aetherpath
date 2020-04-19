#include "base.hpp"

#include "game/gameLayer/entities/player/ship.hpp"
#include "game/gameLayer/gameService.hpp"

Base::Base(int o, int f, int p, int m)
    : PlayerEntity(o, f, p, m)
    , m_uiState(UIState::NONE)
    , m_building(false)
    , m_shipToDeploy(nullptr)
{}

void Base::ResetState()
{
    m_uiState = UIState::NONE;
    m_shipToDeploy = nullptr;
}

void Base::CreateAction()
{
    ResetState();
    m_uiState = UIState::CREATE;
}

void Base::DeployAction()
{
    ResetState();
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
    ResetState();
}

void Base::DeselectCallback()
{
    ResetState();
}

void Base::CreateShip(ShipType type)
{
    m_buildingQueue.push_back(BuildingEntry{ type, 0 });
    ResetState();
}

void Base::ChooseShipToDeploy(Oasis::Reference<Ship> ship)
{
    m_uiState = UIState::DEPLOY2;
    m_shipToDeploy = Oasis::DynamicCast<Entity>(ship);
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
    Render();

}

void Base::Tick()
{
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
    return false;
}