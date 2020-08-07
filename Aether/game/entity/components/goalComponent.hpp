#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

// TODO: This should be managed by a game difficulty setting
#define TARGET_POPULATION 101

////////////////////////////////////////////////////////////////
class GoalComponent : public Component
{
public:
    GoalComponent(Ref<Entity> entity);
    virtual void Update(float delta) override;
};