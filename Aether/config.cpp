#include "oasis.h"
#include "core/entry.hpp"

#include "menu/mainMenu.hpp"
#include "game/game.hpp"

Oasis::Configuration Oasis::GetConfiguration()
{
    Oasis::Configuration config;
    config.m_width = 1280;
    config.m_height = 960;
    config.m_name = "Aether";
    
    // Return the initial state as a callback so it doesn't get instantiated before engine inits
    config.m_initState = []() -> IState* 
    {
        return new MainMenu();
    };

    return config;
}