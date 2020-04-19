#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"

#define SPEED_DEBUG_MULTIPLIER 1000

class ResourceEntity;
class Ship : public PlayerEntity
{
public:
    enum class UIState
    {
        NONE,
        MOVE,
        MINE,
        TRANSFER,
        TRANSFER2,
        COLONIZE
    };
    enum class State
    {
        IDLE,
        MOVE,
        MINE,
        TRANSFER
    };
    enum class ResourceType
    {
        OXYGEN,
        FUEL,
        POPULATION,
        METAL
    };

    static constexpr float TRANSFER_RADIUS = 500.f;
    static constexpr float COLONIZE_RADIUS = 500.f;
public:
    Ship(float speed = 100.f, float mineRange = 200.f, int ticksPerFuel = 10, int gatherSpeed = 1, int transferSpeed = 1);
    void InitializeShip(float x, float y);

    float GetSpeed() const { return m_speed; }
    float GetMineRange() const { return m_mineRange; }

    virtual bool CanMove() const override { return true; }
    virtual bool CanMine() const { return true; }

    inline UIState GetUIState() const { return m_UIState; }    

    virtual void Update() override;
    virtual void Tick() override;
    virtual bool HandleClick(float x, float y) override;

    virtual void MoveAction() override;
    virtual void TryMove(float x, float y) override;
    virtual void MineAction() override;
    virtual void TryMine(float x, float y) override;
    virtual void TransferAction() override;
    virtual void TryTransfer(float x, float y) override;
    virtual void ColonizeAction() override;
    virtual void TryColonize(float x, float y) override;
    virtual void DeselectCallback() override;

    void TransferResource(ResourceType type);
private:
    float m_speed;
    float m_mineRange;
    int m_ticksPerFuel;
    int m_gatherSpeed;

    UIState m_UIState;
    State m_state;
    int m_fuelTickAccumulator;

    float m_targetX;
    float m_targetY;
    Oasis::Reference<ResourceEntity> m_mineTarget;
    ResourceType m_transferType;
    Oasis::Reference<PlayerEntity> m_transferTarget;
private:
    // Other less important functions
    void ResetState();
    void ResetUIState();
    void RenderMoveDots();
    void RenderMineDots();
    void RenderTransferRange();
    void RenderTransferDots();
    void RenderColonizeRange();
};

class MotherShip : public Ship
{
public:
    MotherShip();
    virtual bool CanColonize() const { return true; }
};

class FlagShip : public Ship
{
public:
    FlagShip();
    virtual bool CanColonize() const { return true; }
};

class DroneShip : public Ship
{
public:
    DroneShip();
};

class Scout : public Ship
{
public:
    Scout();
};