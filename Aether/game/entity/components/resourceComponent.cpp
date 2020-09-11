#include "resourceComponent.hpp"

// TODO: Make this adjustable by game settings
constexpr unsigned int kWinningPopulation = 10;

unsigned int GameWinSystem::s_totalPopulation = 0;

void GameWinSystem::Update()
{
    // First check if we've won the game
    if (s_totalPopulation >= kWinningPopulation)
    {
        Oasis::Console::AddLog("YAY THE GAME IS WON!!!");
    }
    // Just clear the population at the start of every update
    s_totalPopulation = 0;
}

void GameWinSystem::AddPopulation(unsigned int population)
{
    s_totalPopulation += population;
}

ResourceComponent::ResourceComponent(Ref<Entity> entity, int population, int oxygen, int fuel, int metal, bool countsForGameWin)
    : Component(entity)
    , m_population(population)
    , m_oxygen(oxygen)
    , m_fuel(fuel)
    , m_metal(metal)
    , m_countsForGameWin(countsForGameWin)
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
    if (m_countsForGameWin)
    {
        GameWinSystem::AddPopulation(m_population);
    }
}

bool ResourceComponent::ConsumePopulation(int amount)
{
    if (amount > m_population) return false;
    m_population -= amount;
    return true;
}

bool ResourceComponent::ConsumeOxygen(int amount)
{
    if (amount > m_oxygen) return false;
    m_oxygen -= amount;
    return true;
}

bool ResourceComponent::ConsumeFuel(int amount)
{
    if (amount > m_fuel) return false;
    m_fuel -= amount;
    return true;
}

bool ResourceComponent::ConsumeMetal(int amount)
{
    if (amount > m_metal) return false;
    m_metal -= amount;
    return true;
}


void ResourceComponent::TransferResources(Ref<ResourceComponent> other)
{
    OASIS_TRAP(other != this);
    m_transferring = true;
    m_transferTarget = other;
}

ResourceComponent* ResourceComponent::LoadFromJson(const json& data, Ref<Entity> entity)
{
    int population = 0, oxygen = 0, fuel = 0, metal = 0;
    if (data.find("population") != data.end() && data["population"].is_number_integer())
    {
        population = data["population"];
    }
    if (data.find("oxygen") != data.end() && data["oxygen"].is_number_integer())
    {
        oxygen = data["oxygen"];
    }
    if (data.find("fuel") != data.end() && data["fuel"].is_number_integer())
    {
        fuel = data["fuel"];
    }
    if (data.find("metal") != data.end() && data["metal"].is_number_integer())
    {
        metal = data["metal"];
    }
    return new ResourceComponent(entity, population, oxygen, fuel, metal);
}