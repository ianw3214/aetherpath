#include "UILayer.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/moveComponent.hpp"
#include "game/entity/components/resourceComponent.hpp"
#include "game/entity/components/hangarComponent.hpp"

void UILayer::AddActionsUI()
{
    // Actions window
    UIWindow window{true, false, UIWindow::Alignment::BOTTOM_RIGHT, 120, 320, 10, 10, Oasis::Colour{0.f, 0.2f, 0.2f}, Oasis::Colour{0.6f, 0.9f, 1.f}, 2};

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

    auto createbutton = UIElement::CreateTexture("res/icons/create.png", 100, 100);
    createbutton.m_isButton = true;
    createbutton.m_buttonFunction = [](){
        UIService::ShowShipCreationUI();
    };
    window.m_elements.push_back(createbutton);

    window.m_windowFunction = [](UIWindow& window) {
        if (auto selected = GameService::GetSelected())
        {
            window.m_show = true;
        }
        else
        {
            window.m_show = false;
        }
    };

    UIService::AddUIWindow(window);
}