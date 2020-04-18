#include "ship.hpp"

Ship::Ship()
{
    SetSprite("res/sprites/ship.png");
}

void Ship::Update()
{
    Render();
}

void Ship::TryMove()
{
    Oasis::Console::Print("TRY MOVE");
}