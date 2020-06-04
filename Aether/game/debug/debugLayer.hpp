#pragma once
#include "oasis.h"

////////////////////////////////////////////////////////////////
class DebugLayer : public Oasis::GameStateLayer
{
    friend class GameService;
public:
    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
};