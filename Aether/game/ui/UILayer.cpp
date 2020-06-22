#include "UILayer.hpp"

Ref<UILayer> UIService::s_UILayer = nullptr;

void UIService::AddUIWindow(UIWindow window)
{
    s_UILayer->m_windows.push_back(window);
}

UILayer::UILayer()
{
    UIService::s_UILayer = this;
}

void UILayer::Init()
{

}

void UILayer::Close()
{

}

bool UILayer::HandleEvent(const Oasis::Event& event)
{
    return false;
}

void UILayer::Update() 
{
    for (const UIWindow& window : m_windows)
    {
        if (!window.m_show) 
        {
            continue;
        }
        const float x = static_cast<float>(window.m_x);
        const float y = static_cast<float>(window.m_y);
        const float w = static_cast<float>(window.m_w);
        const float h = static_cast<float>(window.m_h);
        Oasis::Renderer::DrawQuad(x, y, w, h, Oasis::Colour{0.f, 0.2f, 0.3f});
    }
}