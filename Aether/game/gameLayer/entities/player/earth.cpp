#include "earth.hpp"

Earth::Earth(int o, int f, int p, int m)
    : PlayerEntity(o, f, p, m)
{
    SetSprite("res/sprites/earth.png");
}

void Earth::Update()
{
    Render();
}