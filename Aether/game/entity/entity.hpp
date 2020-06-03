#pragma once

#include <vector>

class Component;
class Entity
{
public:
    Entity();
    void AddComponent(Component * component);
    template<class T>
    T * GetComponent();

    void Update(float delta);

    inline void SetX(float x) { m_x = x; }
    inline void SetY(float y) { m_y = y; }
    inline float GetX() const { return m_x; }
    inline float GetY() const { return m_y; }
private:
    float m_x, m_y;
    std::vector<Component*> m_components;
};

template<class T>
T * Entity::GetComponent()
{
    for (Component * component : m_components)
    {
        T * result = dynamic_cast<T*>(component);
        if (result) return result;
    }
    return nullptr;
}