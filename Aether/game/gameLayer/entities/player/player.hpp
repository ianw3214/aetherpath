#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/entity.hpp"

// -------------------------------------------------------------
// Player entities are entities that the player controls
class PlayerEntity : public RenderEntity
{
public:
    PlayerEntity(int o = 0, int f = 0, int p = 0, int m = 0, int t = 1)
        : m_oxygen(o)
        , m_fuel(f)
        , m_population(p)
        , m_metal(m)
        , m_transferSpeed(t)
    {}

    virtual bool CanMove() const { return false; }
    virtual bool CanMine() const { return false; }
    virtual bool CanCreate() const { return false; }
    virtual bool CanDeploy() const { return false; }
    virtual bool CanTransfer() const { return true; }

    virtual void Tick() override;
    virtual void DayCycle() override;

    inline int GetOxygen() const { return m_oxygen; }
    inline int GetFuel() const { return m_fuel; }
    inline int GetPopulation() const { return m_population; }
    inline int GetMetal() const { return m_metal; }
    inline int AddOxygen(int amount) { m_oxygen += amount; return m_oxygen; }
    inline int AddFuel(int amount) { m_fuel += amount; return m_fuel; }
    inline int AddPopulation(int amount) { m_population += amount; return m_population; }
    inline int AddMetal(int amount) { m_metal += amount; return m_metal; }
    inline int ConsumeOxygen(int amount) { m_oxygen -= amount; return m_oxygen; }
    inline int ConsumeFuel(int amount) { m_fuel -= amount; return m_fuel; }
    inline int ConsumePopulation(int amount) { m_population -= amount; return m_population; }
    inline int ConsumeMetal(int amount) { m_metal -= amount; return m_metal; }

    inline int GetTransferSpeed() const { return m_transferSpeed; }

    virtual void MoveAction() {}
    virtual void TryMove(float x, float y) {}
    virtual void MineAction() {}
    virtual void TryMine(float x, float y) {}
    virtual void DeployAction() {}
    virtual void TryDeploy(float x, float y) {}
    virtual void TransferAction() {}
    virtual void TryTransfer(float x, float y) {}

    virtual void CreateAction() {}

private:
    int m_oxygen;
    int m_fuel;
    int m_population;
    int m_metal;
    
    int m_transferSpeed;
};