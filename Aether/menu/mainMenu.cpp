#include "mainMenu.hpp"
#include "game/game.hpp"

void MainMenu::Init()
{

}

void MainMenu::Close()
{

}

void MainMenu::OnEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::KEY_PRESSED || event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        Oasis::StateManager::ChangeState(new Game());
    }
}

void MainMenu::Update()
{
    
}