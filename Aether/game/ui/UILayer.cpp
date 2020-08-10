#include "UILayer.hpp"

UIElement UIElement::CreateText(char * text, Oasis::Colour colour, UI::Font font)
{
    UIElement result{UIElement::Type::TEXT};
    result.m_text = text;
    result.m_colour = colour;
    result.m_font = font;
    result.m_isButton = false;
    return result;
}

UIElement UIElement::CreateDynamicText(std::function<std::string(UIWindow&)> func, Oasis::Colour colour, UI::Font font)
{
    UIElement result{UIElement::Type::TEXT_DYNAMIC};
    result.m_textFunction = func;
    result.m_colour = colour;
    result.m_font = font;
    result.m_isButton = false;
    return result;
}

UIElement UIElement::CreateTexture(char * path, int width, int height)
{
    UIElement result{UIElement::Type::TEXTURE};
    result.m_path = path;
    result.m_width = width;
    result.m_height = height;
    result.m_isButton = false;
    return result;
}

Ref<UILayer> UIService::s_UILayer = nullptr;

void UIService::AddUIWindow(UIWindow window)
{
    s_UILayer->m_windows.push_back(window);
}

Ref<UILayer> UIService::GetUILayer()
{
    return s_UILayer;
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

    // ADD UI
    AddInfoUI();
    AddResourceUI();
    AddShipUI();
    AddActionsUI();
    
    {   // ADD TEST POPUP UI
        UIWindow window{true, true, UIWindow::Alignment::TOP_LEFT, 300, 300, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateText("TEST POPUP", Oasis::Colours::WHITE, UI::Font::DEFAULT));
        UIService::AddUIWindow(window);
    }
}

void UILayer::Close()
{

}

bool UILayer::HandleEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        const auto& mouse = dynamic_cast<const Oasis::MousePressedEvent&>(event);
        const float x = static_cast<float>(mouse.GetX());
        // TODO: This is flipped since the engine isn't consistent... :(
        const float y = static_cast<float>(Oasis::WindowService::WindowHeight() - mouse.GetY());
        // With popup windows, it's possible buttons overlap so we need to prioritize popups
        UIElement * pressedButton = nullptr;
        for (UIWindow& window : m_windows)
        {
            if (window.m_cachedX < x && window.m_cachedX + (float) window.m_w > x)
            {
                if (window.m_cachedY < y && window.m_cachedY + (float) window.m_h > y)
                {
                    for (UIElement& element : window.m_elements)
                    {
                        if (!element.m_isButton)
                        {
                            continue;
                        }
                        if (element.m_cachedX < x && element.m_cachedX + element.m_cachedW > x)
                        {
                            if (element.m_cachedY < y && element.m_cachedY + element.m_cachedH > y)
                            {
                                if (!pressedButton || window.m_isPopup)
                                {
                                    pressedButton = &element;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (pressedButton)
        {
            pressedButton->m_buttonFunction();
            return true;
        }
    }
    return false;
}

void UILayer::Update() 
{
    // Keep track of current positions based on alignment to know where to draw next
    float tl_x = 0.f;
    float tl_y = 0.f;
    float tr_x = static_cast<float>(Oasis::WindowService::WindowWidth());
    float tr_y = 0.f;
    float bl_x = 0.f;
    float bl_y = static_cast<float>(Oasis::WindowService::WindowHeight());
    float br_x = static_cast<float>(Oasis::WindowService::WindowWidth());
    float br_y = static_cast<float>(Oasis::WindowService::WindowHeight());
    auto GetAlignmentX = [&](UIWindow window) {
        const UIWindow::Alignment a = window.m_alignment;
        const float w = static_cast<float>(window.m_w);
        const float marginH = static_cast<float>(window.m_marginH);
        return a == UIWindow::Alignment::TOP_LEFT ? tl_x + marginH :
               a == UIWindow::Alignment::TOP_RIGHT ? tr_x - w - marginH:
               a == UIWindow::Alignment::BOTTOM_LEFT ? bl_x + marginH : br_x - w - marginH;
    };
    auto GetAlignmentY = [&](UIWindow window) {
        const UIWindow::Alignment a = window.m_alignment;
        const float h = static_cast<float>(window.m_h);
        const float marginV = static_cast<float>(window.m_marginV);
        return a == UIWindow::Alignment::TOP_LEFT ? tl_y + marginV:
               a == UIWindow::Alignment::TOP_RIGHT ? tr_y + marginV :
               a == UIWindow::Alignment::BOTTOM_LEFT ? bl_y - h - marginV : br_y - h - marginV;
    };
    auto UpdateAlignmentCoords = [&](UIWindow::Alignment a, float h, float margin) {
        if (a == UIWindow::Alignment::TOP_LEFT) tl_y += h + margin;
        if (a == UIWindow::Alignment::TOP_RIGHT) tr_y += h + margin;
        if (a == UIWindow::Alignment::BOTTOM_LEFT) bl_y -= h + margin;
        if (a == UIWindow::Alignment::BOTTOM_RIGHT) br_y -= h + margin;
    };

    // TODO: Many hard coded numbers need to be moved to margin/padding
    std::vector<Ref<UIWindow>> popups;
    for (UIWindow& window : m_windows)
    {
        if (!window.m_show) 
        {
            // TODO: This is pretty hard coded but I don't have a better solution
            // Still update dynamic text even if not shown
            for (const UIElement& element : window.m_elements)
            {
                if (element.m_type == UIElement::Type::TEXT_DYNAMIC)
                {
                    element.m_textFunction(window);
                }
            }
            continue;
        }
        // Handle all the popups after handling all the normal UI
        if (window.m_isPopup)
        {
            popups.push_back(&window);
            continue;
        }
        const float x = GetAlignmentX(window);
        const float y = GetAlignmentY(window);
        {   // Update cached values
            window.m_cachedX = x;
            window.m_cachedY = y;
        }
        DrawWindow(window, x, y);
        UpdateAlignmentCoords(window.m_alignment, (float) window.m_h, (float) window.m_marginV);
    }
    for (Ref<UIWindow> window : popups)
    {
        // Just center popups for now
        const float x = static_cast<float>(Oasis::WindowService::WindowWidth() - window->m_w) / 2.f;
        const float y = static_cast<float>(Oasis::WindowService::WindowHeight() - window->m_h) / 2.f;
        {   // Update cached values
            window->m_cachedX = x;
            window->m_cachedY = y;
        }
        DrawWindow(*window, x, y);
        // UpdateAlignmentCoords(window->m_alignment, (float) window->m_h, (float) window->m_marginV);
    }
}

void UILayer::DrawWindow(UIWindow& window, float x, float y)
{
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
    // TODO: Text drawing actually goes a little bit over the line for letters like p/y - FIX
    float curr_y = y;
    for (UIElement& element : window.m_elements)
    {
        if (element.m_type == UIElement::Type::TEXT)
        {
            // TODO: Fix these issues in engine (or maybe not)
            // Text drawing as also actually top aligned
            const float y = curr_y + UI::GetFontSize(element.m_font);
            const int length = Oasis::TextRenderer::DrawString(UI::GetFont(element.m_font), std::string(element.m_text), x + 10, y, Oasis::Colour{0.6f, 0.8f, 1.f});
            {   // Update cached values
                element.m_cachedX = x + 10;
                element.m_cachedY = curr_y; // Text is drawn from a 'bottom' line so need to use original y
                element.m_cachedW = (float) length;
                element.m_cachedH = (float) UI::GetFontSize(element.m_font);
            }
            // TODO: Allow things to stay on the same line
            curr_y += UI::GetFontSize(element.m_font) + 2;
        }
        if (element.m_type == UIElement::Type::TEXT_DYNAMIC)
        {
            // TODO: Fix these issues in engine (or maybe not)
            // Text drawing as also actually top aligned
            std::string text = element.m_textFunction(window);
            const float y = curr_y + UI::GetFontSize(element.m_font);
            const int length = Oasis::TextRenderer::DrawString(UI::GetFont(element.m_font), text, x + 10, y, Oasis::Colour{0.6f, 0.8f, 1.f});
            {   // Update cached values
                element.m_cachedX = x + 10;
                element.m_cachedY = curr_y;
                element.m_cachedW = (float) length;
                element.m_cachedH = (float) UI::GetFontSize(element.m_font);
            }
            // TODO: Allow things to stay on the same line
            curr_y += UI::GetFontSize(element.m_font) + 2;
        }
        if (element.m_type == UIElement::Type::TEXTURE)
        {
            const float y = curr_y;
            // TODO: Cache the sprite so we don't have to constantly recreate it
            if (!element.m_cachedSprite)
            {
                element.m_cachedSprite = new Oasis::Sprite(element.m_path);
            }
            element.m_cachedSprite->SetDimensions((float) element.m_width, (float) element.m_height);
            element.m_cachedSprite->SetPos(x + 10, y);
            Oasis::Renderer::DrawSprite(element.m_cachedSprite);
            // TODO: Allow things to stay on the same line
            curr_y += element.m_height + 2;
            {   // Update cached values
                element.m_cachedX = x + 10;
                element.m_cachedY = y;
                element.m_cachedW = (float) element.m_width;
                element.m_cachedH = (float) element.m_height;
            }
        }
    }
}