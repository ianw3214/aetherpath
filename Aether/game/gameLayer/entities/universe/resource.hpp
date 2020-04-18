#pragma once
#include "oasis.h"
#include "game/gameLayer/entities/entity.hpp"

class ResourceEntity : public RenderEntity
{
public:
    ResourceEntity();

    virtual void Update() override;

    inline int GetOxygen() const { return m_oxygen; }
    inline int GetFuel() const { return m_fuel; }
    inline int GetMetal() const { return m_metal; }

protected:
    int m_oxygen;
    int m_fuel;
    int m_metal;
};