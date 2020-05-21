#include "credits.hpp"

void Credits::Init()
{
    
}

void Credits::Close()
{

}

void Credits::OnEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::KEY_PRESSED || event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        exit(0);
    }
}

void Credits::Update()
{
    static Oasis::Sprite bg("res/sprites/background_backup.png");
    bg.SetDimensions(Oasis::WindowService::WindowWidth(), Oasis::WindowService::WindowHeight());
    Oasis::Renderer::DrawSprite(bg);

    static Oasis::Sprite credits("res/sprites/credits.png");
    credits.SetDimensions(Oasis::WindowService::WindowWidth(), Oasis::WindowService::WindowHeight());
    Oasis::Renderer::DrawSprite(credits);

    constexpr float blink_time = 1000.f;    // Milliseconds
    static float m_accum = 0.f;
    if (m_accum > blink_time * 2.f)
    {
        m_accum = 0.f;
    }
    else if (m_accum > blink_time)
    {
        const float x = Oasis::WindowService::WindowWidth() / 2 - 220;
        Oasis::TextRenderer::DrawString("Click anywhere to exit", "default40", x, 20, Oasis::Colours::WHITE);
    }
    m_accum += Oasis::WindowService::GetDelta() / 1000.f;
}
