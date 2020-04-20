#include "resource.hpp"

#include <random>

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

bool ResourceEntity::Colliding(float x, float y) const
{
    // Center the sprite
    x -= GetX();
    y -= GetY();
    // Assume resources are circles
    float radius = GetWidth() / 2.f;
    // Check distance to center
    return x * x + y * y < radius * radius;
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
    static std::random_device r;
    static std::default_random_engine el(r());
    static std::uniform_int_distribution<int> dist(0, 1);
    int key = dist(el);
    if (key == 0)
    {
        SetSprite("res/sprites/planets/planet1.png");
        m_colony_img_path = "res/sprites/planets/planet1_base.png";
    }
    if (key == 1)
    {
        SetSprite("res/sprites/planets/planet2.png");
        m_colony_img_path = "res/sprites/planets/planet2_base.png";
    }
}

Goal::Goal(int o, int f, int m)
    : ResourceEntity(o, f, m)
{
    SetSprite("res/sprites/planets/goal.png");
}