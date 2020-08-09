#include "UIEditor.hpp"

#include "game/gamelayer.hpp"
#include "game/ui/UILayer.hpp"

// TODO: Need to have a better solution for this
#include "../../Oasis/vendor/imgui/imgui.h"

bool UIEditor::s_enabled = false;

UIEditor::UIEditor()
    : m_selectedWindow(nullptr)
    , m_selectedElement(nullptr)
{

}

void UIEditor::Init() 
{
    Oasis::ImGuiWrapper::AddWindowFunction([&](){
        if (!s_enabled) return;
        ImGui::Begin("UI Editor");

        if (m_selectedWindow)
        {
            ImGui::SliderInt("Selected window width", &(m_selectedWindow->m_w), 0, Oasis::WindowService::WindowWidth());
            ImGui::SliderInt("Selected window height", &(m_selectedWindow->m_h), 0, Oasis::WindowService::WindowHeight());
        }
        if (m_selectedElement)
        {
            if (m_selectedElement->m_type == UIElement::Type::TEXT || m_selectedElement->m_type == UIElement::Type::TEXT_DYNAMIC)
            {
                // TODO: Implement
            }
            if (m_selectedElement->m_type == UIElement::Type::TEXTURE)
            {
                // TODO: Implement
            }
        }
        
        ImGui::End();
    });
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
                    if (!window.m_show)
                    {
                        continue;
                    }
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
        m_selectedElement = nullptr;
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
        const float w = static_cast<float>(m_selectedWindow->m_w);
        const float h = static_cast<float>(m_selectedWindow->m_h);
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
