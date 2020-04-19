#include "earth.hpp"

Earth::Earth(int o, int f, int p, int m)
    : Base(o, f, p, m)
{
    SetSprite("res/sprites/earth.png");
}

void Earth::Update()
{
    Render();
}