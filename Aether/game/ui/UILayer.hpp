#pragma once
#include "oasis.h"

#include <vector>

////////////////////////////////////////////////////////////////
struct UIWindow
{
    bool m_show;
    // TODO: Use alignments w/ padding and margin instead of direct pos
    int m_x;
    int m_y;
    int m_w;
    int m_h;
};

////////////////////////////////////////////////////////////////
class UIService
{
    friend class UILayer;
    static Ref<UILayer> s_UILayer;
public:
    static void AddUIWindow(UIWindow window);
};

////////////////////////////////////////////////////////////////
class UILayer : public Oasis::GameStateLayer
{
    friend class UIService;
public:
    UILayer();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    std::vector<UIWindow> m_windows;
};