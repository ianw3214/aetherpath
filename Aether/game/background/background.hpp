#pragma once
#include "oasis.h"

////////////////////////////////////////////////////////////////////////////////////////
class Background : public Oasis::GameStateLayer
{
public:
    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
};