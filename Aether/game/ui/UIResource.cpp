#include "UILayer.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

void UILayer::AddResourceUI()
{
    {   // Population window
        UIWindow window{true, false, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    return std::to_string(resource->GetPopulation());
                }
            }
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
        window.m_windowFunction = [](UIWindow& window){
            if (auto selected = GameService::GetSelected())
            {
                window.m_show = selected->GetComponent<ResourceComponent>();
            }
            else
            {
                window.m_show = false;
            }
        };
        UIService::AddUIWindow(window);
    }
    {   // Oxygen window
        UIWindow window{true, false, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    return std::to_string(resource->GetOxygen());
                }
            }
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));
        window.m_windowFunction = [](UIWindow& window){
            if (auto selected = GameService::GetSelected())
            {
                window.m_show = selected->GetComponent<ResourceComponent>();
            }
            else
            {
                window.m_show = false;
            }
        };
        UIService::AddUIWindow(window);
    }
    {   // Fuel window
        UIWindow window{true, false, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    return std::to_string(resource->GetFuel());
                }
            }
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));

        window.m_windowFunction = [](UIWindow& window){
            if (auto selected = GameService::GetSelected())
            {
                window.m_show = selected->GetComponent<ResourceComponent>();
            }
            else
            {
                window.m_show = false;
            }
        };

        UIService::AddUIWindow(window);
    }
    {   // Metal window
        UIWindow window{true, false, UIWindow::Alignment::TOP_LEFT, 400, 50, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
        window.m_elements.push_back(UIElement::CreateDynamicText([&](UIWindow& window){
            if (auto entity = GameService::GetSelected())
            {
                if (auto resource = entity->GetComponent<ResourceComponent>())
                {
                    return std::to_string(resource->GetMetal());
                }
            }
            return std::string();
        }, Oasis::Colours::WHITE, UI::Font::DEFAULT));

        window.m_windowFunction = [](UIWindow& window){
            if (auto selected = GameService::GetSelected())
            {
                window.m_show = selected->GetComponent<ResourceComponent>();
            }
            else
            {
                window.m_show = false;
            }
        };

        UIService::AddUIWindow(window);
    }
}