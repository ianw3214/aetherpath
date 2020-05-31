#pragma once
#include "util/util.hpp"

class Entity;
class Component
{
public:
    Component(Ref<Entity> entityRef);

    virtual void Update(float delta) {}
private:
    Ref<Entity> m_entityRef;
};