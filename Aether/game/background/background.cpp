#include "background.hpp"

Background::Background()
{

}

void Background::Render() const
{
    // TODO: Cache the sprite
    static Oasis::Sprite sprite(path);
    sprite.SetDimensions(1280.f, 960.f);
    sprite.SetPos(0.f, 0.f);
    Oasis::Renderer::DrawSprite(&sprite);
}