#pragma once
#include "oasis.h"

#include <string>

#include "game/gameLayer/entities/entity.hpp"

class ResourceEntity : public RenderEntity
{
public:
    ResourceEntity(int o = 0, int f = 0, int m = 0);

    virtual void Update() override;

    inline int GetOxygen() const { return m_oxygen; }
    inline int GetFuel() const { return m_fuel; }
    inline int GetMetal() const { return m_metal; }

    int GatherOxygen(int speed);
    int GatherFuel(int speed);
    int GatherMetal(int speed);

    virtual bool Colliding(float x, float y) const override;

protected:
    int m_oxygen;
    int m_fuel;
    int m_metal;
};

class Meteoroid : public ResourceEntity
{
public:
    Meteoroid(int o = 0, int f = 0, int m = 0);
};

class Asteroid : public ResourceEntity
{
public:
    Asteroid(int o = 0, int f = 0, int m = 0);
};

class Planet : public ResourceEntity
{
public:
    Planet(int o = 0, int f = 0, int m = 0);
    inline const std::string& GetColonyImagePath() const { return m_colony_img_path; }
private:
    std::string m_colony_img_path;
};

class Goal : public ResourceEntity
{
public:
    Goal(int o = 0, int f = 0, int m = 0);
};