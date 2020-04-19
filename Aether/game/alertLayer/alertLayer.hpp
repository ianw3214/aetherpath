#pragma once
#include "oasis.h"

#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////
class AlertService;
class AlertLayer : public Oasis::GameStateLayer
{
    friend class AlertService;
public:
    enum class AlertLevel
    {
        INFO,
        WARNING,
        CRITICAL
    };
    struct Alert
    {
        AlertLevel m_level;
        std::string m_message;
    };
public:
    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    // The cursor is rendered here because it is the top most layer
    Oasis::Sprite m_cursor;

    std::vector<Alert> m_alerts;
    // This is the popup that will dominate the users attention
    // Only one at a time
    bool m_showPopup;
    Alert m_popup;

    Oasis::Sprite m_infoIcon;
    Oasis::Sprite m_warningIcon;
    Oasis::Sprite m_criticalIcon;

    Oasis::Sprite m_infoPopup;
    Oasis::Sprite m_warningPopup;
    Oasis::Sprite m_criticalPopup;
};