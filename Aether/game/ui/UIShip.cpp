#include "UILayer.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

void UILayer::AddShipUI()
{
    {   // Ship window
        UIWindow window{true, false, UIWindow::Alignment::BOTTOM_LEFT, 400, 300, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                window.m_show = true;
                return std::string("ENTITY NAME GOES HERE");
            }
            window.m_show = false;
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
        UIService::AddUIWindow(window);
    }
}