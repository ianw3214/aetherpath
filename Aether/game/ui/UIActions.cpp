#include "UILayer.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

void UILayer::AddActionsUI()
{
    // Actions window
    UIWindow window{true, UIWindow::Alignment::BOTTOM_RIGHT, 120, 210, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};
    
    // This element is just to determine if the window should be shown
    auto element = UIElement::CreateDynamicText([](UIWindow& window){
        if (auto selected = GameService::GetSelected())
        {
            window.m_show = true;
        }
        else
        {
            window.m_show = false;
        }
        return "";
    }, Oasis::Colours::WHITE, UI::Font::NONE);
    window.m_elements.push_back(element);

    auto movebutton = UIElement::CreateTexture("res/icons/move.png", 100, 100);
    movebutton.m_isButton = true;
    movebutton.m_buttonFunction = [](){
        GameService::SetMoveAction();
    };
    window.m_elements.push_back(movebutton);

    auto transferbutton = UIElement::CreateTexture("res/icons/transfer.png", 100, 100);
    transferbutton.m_isButton = true;
    transferbutton.m_buttonFunction = [](){
        GameService::SetTransferAction();
    };
    window.m_elements.push_back(transferbutton);

    UIService::AddUIWindow(window);
}