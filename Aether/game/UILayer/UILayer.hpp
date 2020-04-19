#pragma once
#include "oasis.h"

class ResourceEntity;
class PlayerEntity;
class Ship;
class Base;

////////////////////////////////////////////////////////////////////////////////////////
class UILayer : public Oasis::GameStateLayer
{
public:
    // UI enums
    enum class ResourceIcon
    {
        OXYGEN,
        FUEL,
        POPULATION,
        METAL
    };
public:
    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    Oasis::Sprite m_cursor;
    
    // Icons
    // TODO: Make these sprites more consistent (use fuel as reference)
    Oasis::Sprite m_oxygenIcon;
    Oasis::Sprite m_fuelIcon;
    Oasis::Sprite m_populationIcon;
    Oasis::Sprite m_metalIcon;

    Oasis::Sprite m_moveIcon;
    Oasis::Sprite m_mineIcon;
    Oasis::Sprite m_transferIcon;
    // Subicons for transfer
    Oasis::Sprite m_transferOxygenIcon;
    Oasis::Sprite m_transferFuelIcon;
    Oasis::Sprite m_transferPopulationIcon;
    Oasis::Sprite m_transferMetalIcon;

    Oasis::Sprite m_createIcon;
    // Sub icons for create
    Oasis::Sprite m_createMotherShipIcon;
    Oasis::Sprite m_createFlagShipIcon;
    Oasis::Sprite m_createDroneShipIcon;
    Oasis::Sprite m_createScoutIcon;
    Oasis::Sprite m_deployIcon;
    Oasis::Sprite m_transferIconBase;
    // Subicons for transfer(base)
    Oasis::Sprite m_transferOxygenIconBase;
    Oasis::Sprite m_transferFuelIconBase;
    Oasis::Sprite m_transferPopulationIconBase;
    Oasis::Sprite m_transferMetalIconBase;

    // UI For building ships queue in base
    Oasis::Sprite m_queueMotherShipIcon;    
    Oasis::Sprite m_queueFlagShipIcon;    
    Oasis::Sprite m_queueDroneShipIcon;
    Oasis::Sprite m_queueScoutIcon;
    Oasis::Sprite m_queueProgressIcon;

    // Ships in storage
    Oasis::Sprite m_storageMotherShipIcon;
    Oasis::Sprite m_storageFlagShipIcon;
    Oasis::Sprite m_storageDroneShipIcon;
    Oasis::Sprite m_storageScoutIcon;
private:
    void HandleResourceUI(Oasis::Reference<ResourceEntity> resource);
    void HandlePlayerUI(Oasis::Reference<PlayerEntity> player);
    void HandleShipUI(Oasis::Reference<Ship> ship);
    void HandleBaseUI(Oasis::Reference<Base> base);
    bool HandleMousePress(float x, float y);
    // Sub-handle mouse presses to make function look nicer
    bool HandleShipCreateMousePress(float x, float y, Oasis::Reference<Base> base);
private:
    // Drawing helper functions
    void AddPadding(float padding, float& curr);
    void DrawResource(ResourceIcon resource, int numResource, float& curr_y);
    void DrawActionIcon(Oasis::Reference<Oasis::Sprite> icon, float& curr_x, float y);
};