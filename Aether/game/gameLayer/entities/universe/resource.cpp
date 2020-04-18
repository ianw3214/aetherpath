#include "resource.hpp"

ResourceEntity::ResourceEntity()
    : m_oxygen(0)
    , m_fuel(0)
    , m_metal(0)
{
    SetSprite("res/sprites/asteroid.png");
}

void ResourceEntity::Update()
{
    Render();
}