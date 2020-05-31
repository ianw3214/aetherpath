#include "entity.hpp"
#include "component.hpp"

Entity::Entity()
    : m_x(0.f)
    , m_y(0.f)
{

}

void Entity::AddComponent(Component * component)
{
    m_components.push_back(component);
}

void Entity::Update(float delta)
{
    for (Component * component : m_components)
    {
        component->Update(delta);
    }
}