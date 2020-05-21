#include "title.hpp"
#include "game/game.hpp"

void Title::Init()
{
    // Initialize any global resources because the title will only be loaded once at the start
    Oasis::TextRenderer::LoadFont("res/fonts/Munro.ttf", "default");
    Oasis::TextRenderer::LoadFont("res/fonts/Munro.ttf", "default40", 40);
    Oasis::TextRenderer::LoadFont("res/fonts/Munro.ttf", "default60", 60);

    Oasis::Reference<Oasis::AudioResource> audio = Oasis::ResourceManager::LoadResource<Oasis::AudioResource>("res/music/track.wav");
    static Oasis::AudioSource * source = nullptr;
    if (source) delete source;
    source = new Oasis::AudioSource();
    source->SetVolume(0.1f);
    source->Play(audio.GetData(), true);
}

void Title::Close()
{

}

void Title::OnEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::KEY_PRESSED || event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        Oasis::StateManager::ChangeState(new Game());
    }
}

void Title::Update()
{
    static Oasis::Sprite bg("res/sprites/background_backup.png");
    bg.SetDimensions(Oasis::WindowService::WindowWidth(), Oasis::WindowService::WindowHeight());
    Oasis::Renderer::DrawSprite(bg);

    static Oasis::Sprite title("res/sprites/title.png");
    title.SetPos(
        Oasis::WindowService::WindowWidth() / 2 - title.GetWidth() / 2,
        Oasis::WindowService::WindowHeight() / 2 - title.GetHeight() / 2
    );
    Oasis::Renderer::DrawSprite(title);

    constexpr float blink_time = 1000.f;    // Milliseconds
    static float m_accum = 0.f;
    if (m_accum > blink_time * 2.f)
    {
        m_accum = 0.f;
    }
    else if (m_accum > blink_time)
    {
        const float x = Oasis::WindowService::WindowWidth() / 2 - 220;
        Oasis::TextRenderer::DrawString("Click anywhere to start", "default40", x, 20, Oasis::Colours::WHITE);
    }
    m_accum += Oasis::WindowService::GetDelta() / 1000.f;
}
