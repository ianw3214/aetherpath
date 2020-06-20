#include "moveComponent.hpp"

#include "game/entity/entity.hpp"

MoveComponent::MoveComponent(Ref<Entity> entity, float speed)
    : m_speed(speed)
    , m_moving(false)
    , m_targetX(0.f)
    , m_targetY(0.f)
    , Component(entity)
{

}

void MoveComponent::Update(float delta)
{
    // TODO: Swap to direct line movement
    if (m_moving)
    {
        float x = m_entityRef->GetX();
        float y = m_entityRef->GetY();
        if (x < m_targetX)
        {
            x += delta * m_speed;
            if (x > m_targetX) x = m_targetX;
        }
        if (x > m_targetX)
        {
            x -= delta * m_speed;
            if (x < m_targetX) x = m_targetX;
        }
        if (y < m_targetY)
        {
            y += delta * m_speed;
            if (y > m_targetY) y = m_targetY;
        }
        if (y > m_targetY)
        {
            y -= delta * m_speed;
            if (y < m_targetY) y = m_targetY;
        }
        // Check if we have reached the destination
        if (x == m_targetX && y == m_targetY)
        {
            m_moving = false;
        }
        // Update the actual entity position
        m_entityRef->SetX(x);
        m_entityRef->SetY(y);
    }
}

void MoveComponent::Move(float targetX, float targetY)
{
    m_moving = true;
    m_targetX = targetX;
    m_targetY = targetY;
}