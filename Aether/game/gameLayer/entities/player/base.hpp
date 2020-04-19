#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"
#include "game/gameLayer/entities/player/shipDatabase.hpp"
// Need this, hopefully no circular reference
#include "game/gameLayer/entities/player/ship.hpp"

#include <deque>

class Ship;

// -------------------------------------------------------------
class Base : public PlayerEntity
{
public:
    enum class UIState
    {
        NONE,
        CREATE,
        DEPLOY,     // STAGE 1 OF DEPLOY - CHOOSE SHIP
        DEPLOY2,    // STAGE 2 OF DEPLOY - CHOOSE PLACE
        TRANSFER,   // STAGE 1 OF TRANSFER - CHOOSE RESOURCE
        TRANSFER2   // STAGE 2 OF TRANSFER - CHOOSE TRANSFER TARGET
    };
    enum class State
    {
        IDLE,
        TRANSFER
    };
    struct BuildingEntry
    {
        ShipType m_type;
        int m_elapsedTicks;
    };
    enum class ResourceType
    {
        OXYGEN,
        FUEL,
        POPULATION,
        METAL
    };

    static constexpr float DEPLOY_RADIUS = 500.f;
    static constexpr float TRANSFER_RADIUS = 500.f;
public:
    Base(int o = 0, int f = 0, int p = 0, int m = 0, int t = 1);

    std::vector<Oasis::Owned<Entity>>& GetShipStorage() { return m_shipStorage; }
    std::deque<BuildingEntry>& GetBuildingQueue() { return m_buildingQueue; }

    virtual bool CanCreate() const override { return true; }
    virtual bool CanDeploy() const override { return true; }

    inline UIState GetUIState() const { return m_uiState; }    
    void ResetUIState();
    void ResetState();

    virtual void CreateAction() override;
    virtual void DeployAction() override;
    virtual void TryDeploy(float x, float y) override;
    virtual void TransferAction() override;
    virtual void TryTransfer(float x, float y) override;
    virtual void DeselectCallback() override;

    virtual void Update() override;
    virtual void Tick() override;
    virtual bool HandleClick(float x, float y) override;

    void CreateShip(ShipType type);
    void ChooseShipToDeploy(Oasis::Reference<Ship> ship);
    void TransferResource(ResourceType type);
private:
    void RenderTransferRange();
    void RenderTransferDots();
private:
    UIState m_uiState;
    State m_state;
    bool m_building;

    Oasis::Reference<Entity> m_shipToDeploy;
    ResourceType m_transferType;
    Oasis::Reference<PlayerEntity> m_transferTarget;

    std::vector<Oasis::Owned<Entity>> m_shipStorage;
    std::deque<BuildingEntry> m_buildingQueue;
};

// -------------------------------------------------------------
// The goal base is the win condition
class GoalBase : public Base
{
public:
    GoalBase(int o = 0, int f = 0, int p = 0, int m = 0, int t = 1);
    virtual void Tick() override;
};