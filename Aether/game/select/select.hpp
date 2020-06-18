#pragma once
#include "oasis.h"

class Entity;

////////////////////////////////////////////////////////////////////////////////////////
class SelectLayer: public Oasis::GameStateLayer
{
    friend class SelectService;
public:
    SelectLayer();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    Ref<Entity> m_selected;
};

////////////////////////////////////////////////////////////////////////////////////////
class SelectService
{
    friend class SelectLayer;
    static Ref<SelectLayer> s_selectLayer;
public:
    static void Select(Ref<Entity> entity);
    static bool Selected(Ref<Entity> entity);
    static Ref<Entity> GetSelected();
};