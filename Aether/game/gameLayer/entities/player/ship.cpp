#include "ship.hpp"

Ship::Ship()
{
    SetSprite("res/sprites/ship.png");
}

void Ship::Update()
{
    Render();
}