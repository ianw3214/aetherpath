#pragma once
#include "util/util.hpp"

class Entity;
class Component
{
public:
    Component(Ref<Entity> entityRef);

    inline Ref<Entity> GetEntity() const { return m_entityRef; }

    virtual void Update(float delta) {}
protected:
    Ref<Entity> m_entityRef;
};