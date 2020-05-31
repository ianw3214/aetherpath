#pragma once

#include <vector>

class Component;
class Entity
{
public:
    Entity();
    void AddComponent(Component * component);

    void Update(float delta);

    inline void SetX(float x) { m_x = x; }
    inline void SetY(float y) { m_y = y; }
    inline float GetX() const { return m_x; }
    inline float GetY() const { return m_y; }
private:
    float m_x, m_y;
    std::vector<Component*> m_components;
};