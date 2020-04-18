#include "background.hpp"

void Background::Init()
{

}

void Background::Close()
{

}

bool Background::HandleEvent(const Oasis::Event& event)
{
    return false;
}

void Background::Update() 
{
    // Render a black background with stars
    Oasis::Renderer::DrawQuad(0, 0, 1280, 960, Oasis::Texture("res/sprites/background.png"));
}
