#include "alertService.hpp"
#include "alertLayer.hpp"

Oasis::Reference<AlertLayer> AlertService::s_layer;
bool AlertService::s_won = false;
bool AlertService::s_lost = false;

void AlertService::Info(const std::string& message)
{
    s_layer->m_alerts.push_back({AlertLayer::AlertLevel::INFO, message});
}

void AlertService::Warning(const std::string& message)
{
    s_layer->m_alerts.push_back({AlertLayer::AlertLevel::WARNING, message});
}

void AlertService::Critical(const std::string& message)
{
    s_layer->m_alerts.push_back({AlertLayer::AlertLevel::CRITICAL, message});
}

void AlertService::PopupInfo(const std::string& message)
{
    s_layer->m_showPopup = true;
    s_layer->m_popup = { AlertLayer::AlertLevel::INFO, message };
}

void AlertService::PopupWarning(const std::string& message)
{
    s_layer->m_showPopup = true;
    s_layer->m_popup = { AlertLayer::AlertLevel::WARNING, message };
}

void AlertService::PopupCritical(const std::string& message)
{
    s_layer->m_showPopup = true;
    s_layer->m_popup = { AlertLayer::AlertLevel::CRITICAL, message };
}

void AlertService::Win()
{
    if (!s_won && !s_lost)
    {
        s_won = true;
        s_layer->m_alerts.push_back({AlertLayer::AlertLevel::WIN});
    }
}

void AlertService::Lose()
{
    if (!s_won && !s_lost)
    {
        s_lost = true;
        s_layer->m_alerts.push_back({AlertLayer::AlertLevel::LOSE});
    }
}
