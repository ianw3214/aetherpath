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
        Oasis::Renderer::DrawQuad(x, y, w, h, window.m_background);
        // Draw the border as a line strip
        float * border = new float[window.m_borderWidth * 5 * 2];
        for (unsigned int i = 0; i < window.m_borderWidth; ++i)
        {
            unsigned int start = i * 5 * 2;
            border[start++] = x + static_cast<float>(i);
            border[start++] = y + static_cast<float>(i);
            border[start++] = x + w - static_cast<float>(i);
            border[start++] = y + static_cast<float>(i);
            border[start++] = x + w - static_cast<float>(i);
            border[start++] = y + h - static_cast<float>(i);
            border[start++] = x + static_cast<float>(i);
            border[start++] = y + h - static_cast<float>(i);
            border[start++] = x + static_cast<float>(i);
            border[start++] = y + static_cast<float>(i);
        }
        Oasis::Renderer::DrawLineStrip(border, window.m_borderWidth * 5, window.m_borderColour);
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