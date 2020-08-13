#include "hangarComponent.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

HangarComponent::HangarComponent(Ref<Entity> entity, int capacity)
    : Component(entity)
    , m_capacity(capacity)
    , m_ships(0)
{

}

void HangarComponent::Update(float delta)
{

}

bool HangarComponent::CreateShip()
{
    // If we are full, do nothing
    if (m_ships >= m_capacity)
    {
        return false;
    }

    // Temporarily just have a set amount of resources to require
    auto resource = GetEntity()->GetComponent<ResourceComponent>();
    OASIS_TRAP(resource);
    if (!resource->ConsumeMetal(10))
    {
        return false;
    }

    m_ships++;
    return true;
}