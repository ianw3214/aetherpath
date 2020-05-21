#include "alertService.hpp"
#include "alertLayer.hpp"

#include "game/gameLayer/entities/entity.hpp"

Oasis::Reference<AlertLayer> AlertService::s_layer;
bool AlertService::s_won = false;
bool AlertService::s_lost = false;

void AlertService::Info(const std::string& message, Oasis::Reference<Entity> entity)
{
    s_layer->m_alerts.push_back({AlertLayer::AlertLevel::INFO, message, entity});
}

void AlertService::Warning(const std::string& message, Oasis::Reference<Entity> entity)
{
    s_layer->m_alerts.push_back({AlertLayer::AlertLevel::WARNING, message, entity});
}

void AlertService::Critical(const std::string& message, Oasis::Reference<Entity> entity)
{
    s_layer->m_alerts.push_back({AlertLayer::AlertLevel::CRITICAL, message, entity});
}

void AlertService::PopupInfo(const std::string& message, Oasis::Reference<Entity> entity)
{
    s_layer->m_showPopup = true;
    s_layer->m_popup = { AlertLayer::AlertLevel::INFO, message, entity };
}

void AlertService::PopupWarning(const std::string& message, Oasis::Reference<Entity> entity)
{
    s_layer->m_showPopup = true;
    s_layer->m_popup = { AlertLayer::AlertLevel::WARNING, message, entity };
}

void AlertService::PopupCritical(const std::string& message, Oasis::Reference<Entity> entity)
{
    s_layer->m_showPopup = true;
    s_layer->m_popup = { AlertLayer::AlertLevel::CRITICAL, message, entity };
}

void AlertService::Win(Oasis::Reference<Entity> entity)
{
    if (!s_won && !s_lost)
    {
        s_won = true;
        s_layer->m_alerts.push_back({AlertLayer::AlertLevel::WIN, "", entity});
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
