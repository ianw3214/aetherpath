#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

class MoveComponent : public Component
{
public:
    MoveComponent(Ref<Entity> entity, float speed = 100.f);
    virtual void Update(float delta) override;

    void Move(float targetX, float targetY);

    inline bool Moving() const { return m_moving; }
    inline float GetTargetX() const { return m_targetX; }
    inline float GetTargetY() const { return m_targetY; }
private:
    float m_speed;
    bool m_moving;
    float m_targetX;
    float m_targetY;
};