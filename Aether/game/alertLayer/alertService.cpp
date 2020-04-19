#include "alertService.hpp"
#include "alertLayer.hpp"

Oasis::Reference<AlertLayer> AlertService::s_layer;

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
