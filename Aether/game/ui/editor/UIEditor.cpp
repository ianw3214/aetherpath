#include "UIEditor.hpp"

#include "game/gamelayer.hpp"
#include "game/ui/UILayer.hpp"

bool UIEditor::s_enabled = false;

UIEditor::UIEditor()
    : m_selectedWindow(nullptr)
    , m_selectedElement(nullptr)
{

}

void UIEditor::Init() 
{

}

void UIEditor::Close() 
{

}

bool UIEditor::HandleEvent(const Oasis::Event& event) 
{
    if (!s_enabled)
    {
        return false;
    }
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        const auto& mouse = dynamic_cast<const Oasis::MousePressedEvent&>(event);
        const float x = static_cast<float>(mouse.GetX());
        // TODO: This is flipped since the engine isn't consistent... :(
        const float y = static_cast<float>(Oasis::WindowService::WindowHeight() - mouse.GetY());
        for (UIWindow& window : UIService::GetUILayer()->m_windows)
        {
            if (window.m_cachedX < x && window.m_cachedX + (float) window.m_w > x)
            {
                if (window.m_cachedY < y && window.m_cachedY + (float) window.m_h > y)
                {
                    m_selectedWindow = &window;
                    // Choose a specific element to select if we can
                    for (UIElement& element : window.m_elements)
                    {
                        if (element.m_cachedX < x && element.m_cachedX + element.m_cachedW > x)
                        {
                            if (element.m_cachedY < y && element.m_cachedY + element.m_cachedH > y)
                            {
                                m_selectedElement = &element;
                                return true;
                            }
                        }
                    }
                    // If we finish this loop, no element was selected
                    m_selectedElement = nullptr;
                    return true;
                }
            }
        }
        // If we finish this loop, no window was selected
        m_selectedWindow = nullptr;
    }
    return false;
}

void UIEditor::Update()  
{
    if (m_selectedWindow)
    {
        const float x = m_selectedWindow->m_cachedX;
        const float y = m_selectedWindow->m_cachedY;
        const float w = m_selectedWindow->m_w;
        const float h = m_selectedWindow->m_h;
        Oasis::Renderer::DrawQuad(x, y, w, h, Oasis::Colours::WHITE, 0.3f);
    }
    if (m_selectedElement)
    {
        const float x = m_selectedElement->m_cachedX;
        const float y = m_selectedElement->m_cachedY;
        const float w = m_selectedElement->m_cachedW;
        const float h = m_selectedElement->m_cachedH;
        Oasis::Renderer::DrawQuad(x, y, w, h, Oasis::Colours::WHITE, 0.3f);
    }
}
