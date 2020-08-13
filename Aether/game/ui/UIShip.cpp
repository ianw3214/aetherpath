#include "UILayer.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"
#include "game/entity/components/hangarComponent.hpp"

void CreateShipUICommon(UIWindow& window)
{
    window.m_elements.push_back(UIElement::CreateText("ENTITY NAME GOES HERE", Oasis::Colours::WHITE, UI::Font::DEFAULT));
}

void UILayer::AddShipUI()
{
    UIWindow window{true, false, UIWindow::Alignment::BOTTOM_LEFT, 400, 300, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};

    window.m_windowFunction = [](UIWindow& window){
        static Ref<Entity> lastEntity = nullptr;
        if (auto selected = GameService::GetSelected())
        {
            window.m_show = true;
            if (selected != lastEntity)
            {
                lastEntity = selected;
                window.m_elements.clear();
                CreateShipUICommon(window);
                
                if (auto hangar = selected->GetComponent<HangarComponent>())
                {
                    Oasis::Console::AddLog("HELLO HELLO HELLO");
                    window.m_elements.push_back(UIElement::CreateDynamicText([=](UIWindow& window){
                        return std::to_string(hangar->GetNumShips());
                    }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
                }
            }
        }
        else
        {
            window.m_show = false;
        }
    };

    UIService::AddUIWindow(window);
}