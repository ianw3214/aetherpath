#include "alertLayer.hpp"

#include "alertService.hpp"

#include "game/gameLayer/entities/entity.hpp"
#include "game/camera/camera.hpp"

constexpr int max_on_screen = 8;
constexpr float alert_icon_width = 80.f;
constexpr float alert_icon_height = 80.f;
constexpr float popup_width = 600.f;
constexpr float popup_height = 300.f;

constexpr float padding_horizontal = 10.f;
constexpr float padding_vertical = 10.f;
constexpr float popup_text_padding_h = 30.f;
constexpr float popup_text_padding_v = 60.f;

#include "mainmenu/title.hpp"
#include "credits/credits.hpp"

void AlertLayer::Init() 
{
    m_showPopup = false;

    m_cursor = Oasis::Sprite("res/icons/cursor.png");

    m_infoIcon = Oasis::Sprite("res/icons/info.png");
    m_warningIcon = Oasis::Sprite("res/icons/warning.png");
    m_criticalIcon = Oasis::Sprite("res/icons/error.png");
    m_winIcon = Oasis::Sprite("res/icons/win.png");
    m_loseIcon = Oasis::Sprite("res/icons/lose.png");

    // These positions are constant, set at beginning
    m_infoPopup = Oasis::Sprite("res/icons/popup_info.png");
    m_warningPopup = Oasis::Sprite("res/icons/popup_warning.png");
    m_criticalPopup = Oasis::Sprite("res/icons/popup_error.png");
    m_winPopup = Oasis::Sprite("res/icons/popup_win.png");
    m_losePopup = Oasis::Sprite("res/icons/popup_lose.png");

    Oasis::TextRenderer::LoadFont("res/fonts/Munro.ttf", "error", 32);
    AlertService::SetAlertLayer(this);
}

void AlertLayer::Close() 
{

}

bool AlertLayer::HandleEvent(const Oasis::Event& event) 
{
    if (event.GetType() == Oasis::EventType::MOUSE_MOVE)
    {
        const Oasis::MouseMovedEvent& mouseEvent = dynamic_cast<const Oasis::MouseMovedEvent&>(event);
        float mouse_x = static_cast<float>(mouseEvent.GetX());
        float mouse_y = static_cast<float>(Oasis::WindowService::WindowHeight() - mouseEvent.GetY());
        m_cursor.SetPos(mouse_x, mouse_y - m_cursor.GetHeight());
    }
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        if (m_showPopup)
        {
            if (m_popup.m_level == AlertLevel::WIN)
            {
                Oasis::Console::Print("WIN GAME");
                Oasis::StateManager::ChangeState(new Credits());
            }
            if (m_popup.m_level == AlertLevel::LOSE)
            {
                Oasis::Console::Print("LOSE GAME");
                Oasis::StateManager::ChangeState(new Title());
            }
            m_showPopup = false;
            return true;
        }
        const Oasis::MousePressedEvent& mouseEvent = dynamic_cast<const Oasis::MousePressedEvent&>(event);
        float x = static_cast<float>(mouseEvent.GetX());
        float y = static_cast<float>(Oasis::WindowService::WindowHeight() - mouseEvent.GetY());
        {   // Check if we've clicked an alert icon
            float icon_x = Oasis::WindowService::WindowWidth() - padding_horizontal - alert_icon_width;
            float icon_y = Oasis::WindowService::WindowHeight() - padding_vertical - alert_icon_height;
            constexpr float w = alert_icon_width;
            constexpr float h = alert_icon_height;
            for (auto it = m_alerts.begin(); it != m_alerts.end(); ++it)
            {
                if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
                {
                    m_showPopup = true;
                    m_popup = *it;
                    m_alerts.erase(it);
                    if (m_popup.m_entity)
                    {
                        Camera::GetCamera()->m_x = m_popup.m_entity->GetX();
                        Camera::GetCamera()->m_y = m_popup.m_entity->GetY();
                    }
                    return true;
                }
                icon_x -= padding_horizontal + alert_icon_width;
            }
        }
    }
    return false;
}

void AlertLayer::Update()  
{
    float x = Oasis::WindowService::WindowWidth() - padding_horizontal - alert_icon_width;
    float y = Oasis::WindowService::WindowHeight() - padding_vertical - alert_icon_height;
    for (const Alert& alert : m_alerts)
    {
        Oasis::Reference<Oasis::Sprite> target;
        if (alert.m_level == AlertLevel::INFO) target = m_infoIcon;
        if (alert.m_level == AlertLevel::WARNING) target = m_warningIcon;
        if (alert.m_level == AlertLevel::CRITICAL) target = m_criticalIcon;
        if (alert.m_level == AlertLevel::WIN) target = m_winIcon;
        if (alert.m_level == AlertLevel::LOSE) target = m_loseIcon;
        if (target)
        {
            target->SetPos(x, y);
            Oasis::Renderer::DrawSprite(target);
        }
        else
        {
            OASIS_TRAP(false && "This should never happen...");
        }
        x -= padding_horizontal + alert_icon_width;
    }
    if (m_showPopup)
    {
        Oasis::Reference<Oasis::Sprite> target;
        if (m_popup.m_level == AlertLevel::INFO) target = m_infoPopup;
        if (m_popup.m_level == AlertLevel::WARNING) target = m_warningPopup;
        if (m_popup.m_level == AlertLevel::CRITICAL) target = m_criticalPopup;
        if (m_popup.m_level == AlertLevel::WIN) target = m_winPopup;
        if (m_popup.m_level == AlertLevel::LOSE) target = m_losePopup;
        if (target)
        {
            const float x = (static_cast<float>(Oasis::WindowService::WindowWidth()) - popup_width) / 2.f;
            const float y = (static_cast<float>(Oasis::WindowService::WindowHeight()) - popup_height) / 2.f;
            target->SetPos(x, y);
            Oasis::Renderer::DrawSprite(target);
            Oasis::TextRenderer::DrawString(m_popup.m_message, "error", x + popup_text_padding_h, y + popup_height - popup_text_padding_v, Oasis::Colours::WHITE);
        }
        else
        {
            OASIS_TRAP(false && "This should never happen...");
        }
    }
    // Draw the cursor on top of other things
    Oasis::Renderer::DrawSprite(m_cursor);
}