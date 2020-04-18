#include "background.hpp"

#include <random>

#include "game/gameLayer/gameService.hpp"
#include "game/camera/camera.hpp"

void Background::Init()
{
    m_starSprite = Oasis::Sprite("res/sprites/star.png");

    // Generate all stars entities randomly based on game settings
    GameSettings settings = GameService::GetGameSettings();
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> position_dist(-(settings.m_mapBorder) * 5, settings.m_mapBorder * 5);
    std::uniform_int_distribution<int> parallax_dist(1, 5);

    const int area = (settings.m_mapBorder * 2) * (settings.m_mapBorder * 2);
    const int numStars = area * Star::StarDensityPerSquareThousand / 1000 / 1000;
 
    for (int i = 0; i < numStars; ++i)
    {
        const float x = static_cast<float>(position_dist(el));
        const float y = static_cast<float>(position_dist(el));
        const float parallax = static_cast<float>(parallax_dist(el));
        Oasis::Console::Print(std::to_string(parallax));
        m_stars.push_back(Star{x, y, parallax});
    }
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
    // Render a black base background
    Oasis::Renderer::DrawQuad(0, 0, 1280, 960, Oasis::Texture("res/sprites/background.png"));

    // Draw the stars
    // TODO: This can be heavily optimized
    for (const Star& star : m_stars)
    {
        const float screen_x = static_cast<float>(Camera::RawToScreenX(star.x, star.parallax));
        const float screen_y = static_cast<float>(Camera::RawToScreenY(star.y, star.parallax));
        m_starSprite.SetPos(screen_x, screen_y);
        // Affect stars a TEENY bit from scaling
        const float scale = (Camera::GetCamera()->GetScale() - 1.f) * star_scale_ratio + 1.f;
        m_starSprite.SetDimensions(star_sprite_width * scale, star_sprite_height * scale);
        Oasis::Renderer::DrawSprite(m_starSprite);
    }
}
