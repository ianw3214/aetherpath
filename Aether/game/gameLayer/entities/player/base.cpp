#include "base.hpp"

#include "game/gameLayer/entities/player/ship.hpp"
#include "game/gameLayer/gameService.hpp"

Base::Base(int o, int f, int p, int m)
    : PlayerEntity(o, f, p, m)
    , m_uiState(UIState::NONE)
    , m_building(false)
{}

void Base::ResetState()
{
    m_uiState = UIState::NONE;
}

void Base::CreateAction()
{
    m_uiState = UIState::CREATE;
}

void Base::DeselectCallback()
{
    ResetState();
}

void Base::CreateShip(ShipType type)
{
    m_buildingQueue.push_back(BuildingEntry{ type, 0 });
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