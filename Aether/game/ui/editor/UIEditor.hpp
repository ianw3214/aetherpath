#pragma once
#include "oasis.h"

class UIWindow;
class UIElement;

class UIEditor : public Oasis::GameStateLayer
{
public:
    UIEditor();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
public:
    // static flag for enabling/disabling editor
    static bool s_enabled;
    inline static void SetEnabled(bool enabled) 
    {
        s_enabled = enabled;
    }
private:
    Ref<UIWindow> m_selectedWindow;
    Ref<UIElement> m_selectedElement;
};