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
    // TODO: Make this less of a hack
    static bool fonts_loaded = false;
    if (!fonts_loaded)
    {
        fonts_loaded = true;
        // Initialize font resources only once
        Oasis::TextRenderer::LoadFont(UI::GetFont(UI::Font::DEFAULT), UI::GetFontPath(UI::Font::DEFAULT), UI::GetFontSize(UI::Font::DEFAULT));
        Oasis::TextRenderer::LoadFont(UI::GetFont(UI::Font::SMALL), UI::GetFontPath(UI::Font::SMALL), UI::GetFontSize(UI::Font::SMALL));
    }
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
    // TODO: Many hard coded numbers need to be moved to margin/padding
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
        // Draw the border as a line strip
        float border[30] = {
            // Layer 1
            x, y,
            x + w, y,
            x + w, y + h,
            x, y + h,
            x, y,
            // Layer 2
            x + 1.f, y + 1.f,
            x + w - 1.f, y + 1.f,
            x + w - 1.f, y + h - 1.f,
            x + 1.f, y + h - 1.f,
            x + 1.f, y + 1.f,
            // Layer 3
            x + 2.f, y + 2.f,
            x + w - 2.f, y + 2.f,
            x + w - 2.f, y + h - 2.f,
            x + 2.f, y + h - 2.f,
            x + 2.f, y + 2.f
        };
        Oasis::Renderer::DrawLineStrip(border, 15, Oasis::Colour{0.6f, 0.8f, 1.f});
        // Draw the UI elements
        float curr_y = static_cast<float>(window.m_y);
        for (const UIElement& element : window.m_elements)
        {
            if (element.m_type == UIElement::Type::TEXT)
            {
                // TODO: Fix these issues in engine (or maybe not)
                // y is actually inverted for text renderer
                // Text drawing as also actually top aligned
                const float y = static_cast<float>(Oasis::WindowService::WindowHeight()) - curr_y - UI::GetFontSize(element.m_font);
                Oasis::TextRenderer::DrawString(UI::GetFont(element.m_font), std::string(element.m_text), x + 10, y, Oasis::Colour{0.6f, 0.8f, 1.f});
                // TODO: Allow things to stay on the same line
                curr_y += UI::GetFontSize(element.m_font) + 2;
            }
        }
    }
}