#pragma once
#include "oasis.h"

class AlertLayer;
class Entity;
class AlertService
{
private:
    friend class AlertLayer;
    static Oasis::Reference<AlertLayer> s_layer;
    static void SetAlertLayer(Oasis::Reference<AlertLayer> layer) { 
        s_layer = layer;
        // Treat this as a reset
        s_won = false;
        s_lost = false;
    }
    static bool s_won;
    static bool s_lost;
public:
    static void Info(const std::string& message, Oasis::Reference<Entity> = nullptr);
    static void Warning(const std::string& message, Oasis::Reference<Entity> = nullptr);
    static void Critical(const std::string& message, Oasis::Reference<Entity> = nullptr);

    // These are for directly sending popups
    static void PopupInfo(const std::string& message, Oasis::Reference<Entity> = nullptr);
    static void PopupWarning(const std::string& message, Oasis::Reference<Entity> = nullptr);
    static void PopupCritical(const std::string& message, Oasis::Reference<Entity> = nullptr);

    static void Win(Oasis::Reference<Entity> goal);
    static void Lose();
};