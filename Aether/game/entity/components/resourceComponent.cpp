#include "resourceComponent.hpp"

ResourceComponent::ResourceComponent(Ref<Entity> entity, int population, int oxygen, int fuel, int metal)
    : Component(entity)
    , m_population(population)
    , m_oxygen(oxygen)
    , m_fuel(fuel)
    , m_metal(metal)
{

}