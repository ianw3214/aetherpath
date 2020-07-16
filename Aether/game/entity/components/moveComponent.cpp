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
    if (m_moving)
    {
        const float x_offset = m_targetX - m_entityRef->GetX();
        const float y_offset = m_targetY - m_entityRef->GetY();

        const float hypotenuse = std::sqrt(x_offset * x_offset + y_offset * y_offset);
        const float ratio = m_speed / hypotenuse * (delta / 1000.f);
        // Update the actual entity position
        if (ratio > 1.f)
        {
            // The ship has arrived at the target position
            m_entityRef->SetX(m_targetX);
            m_entityRef->SetY(m_targetY);
            m_moving = false;
        }
        else
        {
            // Move a teeny bit
            const float move_x = x_offset * ratio;
            const float move_y = y_offset * ratio;
            m_entityRef->SetX(m_entityRef->GetX() + move_x);
            m_entityRef->SetY(m_entityRef->GetY() + move_y);
        }
    }
}

void MoveComponent::Move(float targetX, float targetY)
{
    m_moving = true;
    m_targetX = targetX;
    m_targetY = targetY;
}