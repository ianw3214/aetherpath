#pragma once

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
        case ShipType::MOTHERSHIP: return 180;
        case ShipType::FLAGSHIP: return 60;
        case ShipType::DRONESHIP: return 20;
        case ShipType::SCOUT: return 15;
        default: return 0;
    }
}