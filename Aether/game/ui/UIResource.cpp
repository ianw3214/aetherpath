#include "UILayer.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

void UILayer::AddResourceUI()
{
    {   // Population window
        UIWindow window{true, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    window.m_show = true;
                    return std::to_string(resource->GetPopulation());
                }
            }
            window.m_show = false;
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
        UIService::AddUIWindow(window);
    }
    {   // Oxygen window
        UIWindow window{true, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    window.m_show = true;
                    return std::to_string(resource->GetOxygen());
                }
            }
            window.m_show = false;
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
        UIService::AddUIWindow(window);
    }
    {   // Fuel window
        UIWindow window{true, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    window.m_show = true;
                    return std::to_string(resource->GetFuel());
                }
            }
            window.m_show = false;
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
        UIService::AddUIWindow(window);
    }
    {   // Metal window
        UIWindow window{true, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    window.m_show = true;
                    return std::to_string(resource->GetMetal());
                }
            }
            window.m_show = false;
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
        UIService::AddUIWindow(window);
    }

    {   // TEST WINDOW FOR BUTTONS
        UIWindow window{true, UIWindow::Alignment::TOP_RIGHT, 300, 300, 10, 10, Oasis::Colour{0.f, 0.f, 0.f}, Oasis::Colour{1.f, 1.f, 1.f}, 2};
        auto element = UIElement::CreateText("TEST BUTTON", Oasis::Colours::WHITE, UI::Font::DEFAULT);
        element.m_isButton = true;
        element.m_buttonFunction = [](){
            Oasis::Console::AddLog("TEST BUTTON PRESSED");
        };
        window.m_elements.push_back(element);

        auto element2 = UIElement::CreateTexture("res/icons/colonize.png", 100, 100);
        element2.m_isButton = true;
        element2.m_buttonFunction = [](){
            Oasis::Console::AddLog("TEST BUTTON 2 PRESSED");
        };
        window.m_elements.push_back(element2);

        UIService::AddUIWindow(window);
    }
}