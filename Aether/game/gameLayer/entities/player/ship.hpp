#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/player/player.hpp"

class Ship : public PlayerEntity
{
public:
    enum class UIState
    {
        NONE,
        MOVE
    };
    enum class State
    {
        IDLE,
        MOVE
    };
public:
    Ship(float speed = 100.f);

    float GetSpeed() const { return m_speed; }

    virtual bool CanMove() const override { return true; }

    virtual void Update() override;
    virtual bool HandleClick(float x, float y) override;

    virtual void MoveAction() override;
    virtual void TryMove(float x, float y) override;
private:
    float m_speed;

    UIState m_UIState;
    State m_state;

    float m_targetX;
    float m_targetY;
private:
    // Other less important functions
    void RenderMoveDots();
};

class FlagShip : public Ship
{
public:
    FlagShip();
};