#include "UILayer.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

void UILayer::AddInfoUI()
{
    // Actions window
    UIWindow window{true, UIWindow::Alignment::TOP_LEFT, 500, 60, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
    
    // This element is just to determine if the window should be shown
    auto element = UIElement::CreateDynamicText([](UIWindow& window){
        return "DAY 1";
    }, Oasis::Colours::WHITE, UI::Font::DEFAULT);
    window.m_elements.push_back(element);

    UIService::AddUIWindow(window);
}