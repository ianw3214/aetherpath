#include "player.hpp"

#include <random>

#include "game/gameLayer/gameService.hpp"
#include "game/alertLayer/alertService.hpp"

void PlayerEntity::Tick()
{
    // Kill people randomly if there is no more oxygen
    if (GetOxygen() <= 0 && GetPopulation() > 0)
    {
        static GameSettings settings = GameService::GetGameSettings();
        static std::random_device r;
        static std::default_random_engine el(r());
        static std::uniform_int_distribution<int> death_dist(1, settings.m_no_oxygen_death_chance);
        if (death_dist(el) == 1)
        {
            int result = ConsumePopulation(1);
            if (result == 0)
            {
                AlertService::Warning("Population has completely died", this);
            }
        }
    }
}

void PlayerEntity::DayCycle()
{
    if (GetOxygen() > 0 && GetPopulation() > 0)
    {
        int result = ConsumeOxygen(m_population / 100 > 0 ? m_population / 100 : 1);
        if (result <= 0)
        {
            AlertService::Critical("No oxygen - population will start dying", this);
        }
    }
}