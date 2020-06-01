#pragma once
#include "util/util.hpp"

class Entity;
class Component
{
public:
    Component(Ref<Entity> entityRef);

    virtual void Update(float delta) {}
protected:
    Ref<Entity> m_entityRef;
};