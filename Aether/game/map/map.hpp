#pragma once

// TODO: This should be dynamically set in some sort of settings
#define NUM_PLANETS 50
#define NUM_ASTEROIDS 100

class Map
{
public:
    static void GenerateMap();
private:
    // Helper functions
    static void GenerateEarth();
    static void GenerateMoon();
    static void GeneratePlanets();
    static void GenerateAsteroids();
    static void GenerateGoalPlanet();
};