#pragma once

#define DEBUG_DIVISOR 100

enum class ShipType
{
    MOTHERSHIP,
    FLAGSHIP,
    DRONESHIP,
    SCOUT
};

inline int SecondsToBuildShip(ShipType type)
{
    switch(type)
    {
        case ShipType::MOTHERSHIP: return 180 / DEBUG_DIVISOR;
        case ShipType::FLAGSHIP: return 60 / DEBUG_DIVISOR;
        case ShipType::DRONESHIP: return 20 / DEBUG_DIVISOR;
        case ShipType::SCOUT: return 15 / DEBUG_DIVISOR;
        default: return 0;
    }
}