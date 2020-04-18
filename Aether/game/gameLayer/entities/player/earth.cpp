#include "earth.hpp"

Earth::Earth()
{
    SetSprite("res/sprites/earth.png");
}

void Earth::Update()
{
    Render();
}