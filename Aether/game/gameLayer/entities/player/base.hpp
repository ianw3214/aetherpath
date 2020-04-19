#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"
#include "game/gameLayer/entities/player/shipDatabase.hpp"
// Need this, hopefully no circular reference
#include "game/gameLayer/entities/player/ship.hpp"

#include <deque>

class Ship;

// -------------------------------------------------------------
// For now bases are just used to tag entities as bases
class Base : public PlayerEntity
{
public:
    enum class UIState
    {
        NONE,
        CREATE
    };
    struct BuildingEntry
    {
        ShipType m_type;
        int m_elapsedTicks;
    };
public:
    Base(int o = 0, int f = 0, int p = 0, int m = 0);

    std::vector<Oasis::Owned<Ship>>& GetShipStorage() { return m_shipStorage; }
    std::deque<BuildingEntry>& GetBuildingQueue() { return m_buildingQueue; }

    virtual bool CanCreate() const override { return true; }

    inline UIState GetUIState() const { return m_uiState; }    
    void ResetState();

    virtual void CreateAction() override;
    virtual void DeselectCallback() override;

    virtual void Tick() override;

    void CreateShip(ShipType type);
private:
    UIState m_uiState;
    bool m_building;

    std::vector<Oasis::Owned<Ship>> m_shipStorage;
    std::deque<BuildingEntry> m_buildingQueue;
};