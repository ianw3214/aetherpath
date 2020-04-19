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
        CREATE,
        DEPLOY,     // STAGE 1 OF DEPLOY - CHOOSE SHIP
        DEPLOY2     // STAGE 2 OF DEPLOY - CHOOSE PLACE
    };
    struct BuildingEntry
    {
        ShipType m_type;
        int m_elapsedTicks;
    };

    static constexpr float DEPLOY_RADIUS = 500.f;
public:
    Base(int o = 0, int f = 0, int p = 0, int m = 0);

    std::vector<Oasis::Owned<Entity>>& GetShipStorage() { return m_shipStorage; }
    std::deque<BuildingEntry>& GetBuildingQueue() { return m_buildingQueue; }

    virtual bool CanCreate() const override { return true; }
    virtual bool CanDeploy() const override { return true; }

    inline UIState GetUIState() const { return m_uiState; }    
    void ResetState();

    virtual void CreateAction() override;
    virtual void DeployAction() override;
    virtual void TryDeploy(float x, float y) override;
    virtual void DeselectCallback() override;

    virtual void Update() override;
    virtual void Tick() override;
    virtual bool HandleClick(float x, float y) override;

    void CreateShip(ShipType type);
    void ChooseShipToDeploy(Oasis::Reference<Ship> ship);
private:
    UIState m_uiState;
    bool m_building;

    Oasis::Reference<Entity> m_shipToDeploy;

    std::vector<Oasis::Owned<Entity>> m_shipStorage;
    std::deque<BuildingEntry> m_buildingQueue;
};