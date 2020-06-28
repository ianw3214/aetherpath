#include "resourceComponent.hpp"

ResourceComponent::ResourceComponent(Ref<Entity> entity, int population, int oxygen, int fuel, int metal)
    : Component(entity)
    , m_population(population)
    , m_oxygen(oxygen)
    , m_fuel(fuel)
    , m_metal(metal)
    , m_transferring(false)
    , m_transferTarget(nullptr)
{

}

void ResourceComponent::Update(float delta)
{
    if (m_transferring)
    {
        bool transferred = false;
        // Just transfer 1 resource per tick for now
        if (m_population > 0)
        {
            m_population -= 1;
            m_transferTarget->m_population += 1;
            transferred = true;
        }
        if (m_oxygen > 0)
        {
            m_oxygen -= 1;
            m_transferTarget->m_oxygen += 1;
            transferred = true;
        }
        if (m_fuel > 0)
        {
            m_fuel -= 1;
            m_transferTarget->m_fuel += 1;
            transferred = true;
        }
        if (m_metal > 0)
        {
            m_metal -= 1;
            m_transferTarget->m_metal += 1;
            transferred = true;
        }
        if (!transferred)
        {
            m_transferring = false;
            m_transferTarget = nullptr;
        }
    }
}

void ResourceComponent::TransferResources(Ref<ResourceComponent> other)
{
    OASIS_TRAP(other != this);
    m_transferring = true;
    m_transferTarget = other;
}