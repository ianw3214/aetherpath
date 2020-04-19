#include "resource.hpp"

ResourceEntity::ResourceEntity(int o, int f, int m)
    : m_oxygen(o)
    , m_fuel(f)
    , m_metal(m)
{
    SetSprite("res/sprites/asteroid.png");
}

void ResourceEntity::Update()
{
    Render();
}

int ResourceEntity::GatherOxygen(int speed)
{
    int amount = speed <= m_oxygen ? speed : m_oxygen;
    m_oxygen -= amount;
    return amount;
}
int ResourceEntity::GatherFuel(int speed)
{
    int amount = speed <= m_fuel ? speed : m_fuel;
    m_fuel -= amount;
    return amount;
}
int ResourceEntity::GatherMetal(int speed)
{
    int amount = speed <= m_metal ? speed : m_metal;
    m_metal -= amount;
    return amount;
}

Meteoroid::Meteoroid(int o, int f, int m)
    : ResourceEntity(o, f, m)
{
    SetSprite("res/sprites/meteroid.png");
}

Asteroid::Asteroid(int o, int f, int m)
    : ResourceEntity(o, f, m)
{
    SetSprite("res/sprites/asteroid.png");
}

Planet::Planet(int o, int f, int m)
    : ResourceEntity(o, f, m)
{
    SetSprite("res/sprites/planets/planet1.png");
}

Goal::Goal(int o, int f, int m)
    : ResourceEntity(o, f, m)
{
    SetSprite("res/sprites/planets/goal.png");
}