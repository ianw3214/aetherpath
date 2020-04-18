#pragma once
#include "oasis.h"

#include <vector>

#include "entities/entity.hpp"

////////////////////////////////////////////////////////////////////////////////////////
class GameLayer : public Oasis::GameStateLayer
{
public:
    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    std::vector<Oasis::Owned<Entity>> m_entities;
};