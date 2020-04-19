#pragma once
#include "oasis.h"

class AlertLayer;
class AlertService
{
private:
    friend class AlertLayer;
    static Oasis::Reference<AlertLayer> s_layer;
    static void SetAlertLayer(Oasis::Reference<AlertLayer> layer) { s_layer = layer;}
public:
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Critical(const std::string& message);

    // These are for directly sending popups
    static void PopupInfo(const std::string& message);
    static void PopupWarning(const std::string& message);
    static void PopupCritical(const std::string& message);
};