#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"

class ResourceEntity;
class Ship : public PlayerEntity
{
public:
    enum class UIState
    {
        NONE,
        MOVE,
        MINE
    };
    enum class State
    {
        IDLE,
        MOVE,
        MINE
    };
public:
    Ship(float speed = 100.f, float mineRange = 200.f, int ticksPerFuel = 10, int gatherSpeed = 1);
    void InitializeShip(float x, float y);

    float GetSpeed() const { return m_speed; }
    float GetMineRange() const { return m_mineRange; }

    virtual bool CanMove() const override { return true; }
    virtual bool CanMine() const { return true; }

    virtual void Update() override;
    virtual void Tick() override;
    virtual bool HandleClick(float x, float y) override;

    virtual void MoveAction() override;
    virtual void TryMove(float x, float y) override;
    virtual void MineAction() override;
    virtual void TryMine(float x, float y) override;
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
private:
    // Other less important functions
    void ResetState();
    void RenderMoveDots();
    void RenderMineDots();
};

class MotherShip : public Ship
{
public:
    MotherShip();
};

class FlagShip : public Ship
{
public:
    FlagShip();
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