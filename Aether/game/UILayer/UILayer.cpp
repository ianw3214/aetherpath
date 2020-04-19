#include "UILayer.hpp"

#include <SDL2/SDL.h>

#include "game/gameLayer/gameService.hpp"
#include "game/gameLayer/entities/entity.hpp"
#include "game/gameLayer/entities/player/player.hpp"
#include "game/gameLayer/entities/player/base.hpp"
#include "game/gameLayer/entities/player/ship.hpp"
#include "game/gameLayer/entities/universe/resource.hpp"

// Use fixed size UI
constexpr float resource_icon_width = 80.f;
constexpr float resource_icon_height = 80.f;
constexpr float action_icon_width = 100.f;
constexpr float action_icon_height = 100.f;
constexpr float create_ship_icon_width = 400.f;
constexpr float create_ship_icon_height = 100.f;
constexpr float build_queue_icon_width = 200.f;
constexpr float build_queue_icon_height = 120.f;
constexpr float queue_progress_icon_width = 190.f;
constexpr float queue_progress_icon_height = 120.f;

constexpr float margin_horizontal = 10;
constexpr float margin_vertical = 10;

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::Init()
{
    m_motherShipInfo = Oasis::Sprite("res/icons/mothership_info.png");
    m_flagShipInfo = Oasis::Sprite("res/icons/flagship_info.png");
    m_droneShipInfo = Oasis::Sprite("res/icons/droneship_info.png");
    m_scoutInfo = Oasis::Sprite("res/icons/scout_info.png");
    m_planetInfo = Oasis::Sprite("res/icons/planet_info.png");

    m_oxygenIcon = Oasis::Sprite("res/icons/oxygen.png");
    m_fuelIcon = Oasis::Sprite("res/icons/fuel.png");
    m_populationIcon = Oasis::Sprite("res/icons/population.png");
    m_metalIcon = Oasis::Sprite("res/icons/metal.png");
    
    m_moveIcon = Oasis::Sprite("res/icons/move.png");
    m_mineIcon = Oasis::Sprite("res/icons/mine.png");
    m_transferIcon = Oasis::Sprite("res/icons/transfer.png");
    m_transferOxygenIcon = Oasis::Sprite("res/icons/transfer_oxygen_ship.png");
    m_transferFuelIcon = Oasis::Sprite("res/icons/transfer_fuel_ship.png");
    m_transferPopulationIcon = Oasis::Sprite("res/icons/transfer_population_ship.png");
    m_transferMetalIcon = Oasis::Sprite("res/icons/transfer_metal_ship.png");
    m_colonizeIcon = Oasis::Sprite("res/icons/colonize.png");

    m_createIcon = Oasis::Sprite("res/icons/create.png");
    m_createMotherShipIcon = Oasis::Sprite("res/icons/create_mothership.png");
    m_createFlagShipIcon = Oasis::Sprite("res/icons/create_flagship.png");
    m_createDroneShipIcon = Oasis::Sprite("res/icons/create_droneship.png");
    m_createScoutIcon = Oasis::Sprite("res/icons/create_scout.png");
    m_deployIcon = Oasis::Sprite("res/icons/deploy.png");
    m_transferIconBase = Oasis::Sprite("res/icons/transfer_base.png");
    m_transferOxygenIconBase = Oasis::Sprite("res/icons/transfer_oxygen_base.png");
    m_transferFuelIconBase = Oasis::Sprite("res/icons/transfer_fuel_base.png");
    m_transferPopulationIconBase = Oasis::Sprite("res/icons/transfer_population_base.png");
    m_transferMetalIconBase = Oasis::Sprite("res/icons/transfer_metal_base.png");

    m_queueMotherShipIcon = Oasis::Sprite("res/icons/queue_mothership.png");
    m_queueFlagShipIcon = Oasis::Sprite("res/icons/queue_flagship.png");
    m_queueDroneShipIcon = Oasis::Sprite("res/icons/queue_droneship.png");
    m_queueScoutIcon = Oasis::Sprite("res/icons/queue_scout.png");
    m_queueProgressIcon = Oasis::Sprite("res/icons/queue_progress.png");

    m_storageMotherShipIcon = Oasis::Sprite("res/icons/storage_mothership.png");
    m_storageFlagShipIcon = Oasis::Sprite("res/icons/storage_flagship.png");
    m_storageDroneShipIcon = Oasis::Sprite("res/icons/storage_droneship.png");
    m_storageScoutIcon = Oasis::Sprite("res/icons/storage_scout.png");
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::Close()
{

}

////////////////////////////////////////////////////////////////////////////////////////////
bool UILayer::HandleEvent(const Oasis::Event& event)
{
    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        const Oasis::MousePressedEvent& mouseEvent = dynamic_cast<const Oasis::MousePressedEvent&>(event);
        bool result = HandleMousePress(
            static_cast<float>(mouseEvent.GetX()), 
            static_cast<float>(Oasis::WindowService::WindowHeight() - mouseEvent.GetY())
        );
        if (result) return true;
    }
    // Hotkeys for when a player entity is selected
    if (auto player = Oasis::DynamicCast<PlayerEntity>(GameService::GetSelectedEntity()))
    {
        if (event.GetType() == Oasis::EventType::KEY_PRESSED)
        {
            const Oasis::KeyPressedEvent& keyEvent = dynamic_cast<const Oasis::KeyPressedEvent&>(event);
            if (keyEvent.GetKey() == SDL_SCANCODE_1)
            {
                player->MoveAction();
                return true;
            }
            if (keyEvent.GetKey() == SDL_SCANCODE_2)
            {
                player->MineAction();
                return true;
            }
            if (keyEvent.GetKey() == SDL_SCANCODE_3)
            {
                player->TransferAction();
                return true;
            }
            if (keyEvent.GetKey() == SDL_SCANCODE_4)
            {
                player->ColonizeAction();
                return true;
            }
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::Update() 
{
    // Show UI based on what's selected
    if (auto selected = GameService::GetSelectedEntity())
    {
        if (auto resource = Oasis::DynamicCast<ResourceEntity>(selected))
        {
            HandleResourceUI(resource);
        }
        if (auto player = Oasis::DynamicCast<PlayerEntity>(selected))
        {
            HandlePlayerUI(player);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::HandleResourceUI(Oasis::Reference<ResourceEntity> resource)
{
    float y = 10;
    DrawResource(ResourceIcon::OXYGEN, resource->GetOxygen(), y);
    AddPadding(10, y);
    DrawResource(ResourceIcon::FUEL, resource->GetFuel(),y);
    AddPadding(10, y);
    DrawResource(ResourceIcon::METAL, resource->GetMetal(),y);
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::HandlePlayerUI(Oasis::Reference<PlayerEntity> player)
{
    float y = margin_vertical;
    {   // Draw the info sprite
        Oasis::Reference<Oasis::Sprite> target;
        if (Oasis::DynamicCast<MotherShip>(player)) target = m_motherShipInfo;
        if (Oasis::DynamicCast<FlagShip>(player)) target = m_flagShipInfo;
        if (Oasis::DynamicCast<DroneShip>(player)) target = m_droneShipInfo;
        if (Oasis::DynamicCast<Scout>(player)) target = m_scoutInfo;
        if (Oasis::DynamicCast<Base>(player)) target = m_planetInfo;
        if (target)
        {
            target->SetPos(margin_horizontal, Oasis::WindowService::WindowHeight() - 200 - y);
            Oasis::Renderer::DrawSprite(target);
            y += m_droneShipInfo.GetHeight() + margin_vertical;
        }
    }
    DrawResource(ResourceIcon::OXYGEN, player->GetOxygen(), y);
    AddPadding(margin_vertical, y);
    DrawResource(ResourceIcon::FUEL, player->GetFuel(), y);
    AddPadding(margin_vertical, y);
    DrawResource(ResourceIcon::POPULATION, player->GetPopulation(),y);
    AddPadding(margin_vertical, y);
    DrawResource(ResourceIcon::METAL, player->GetMetal(),y);
    if (auto ship = Oasis::DynamicCast<Ship>(player))
    {
        HandleShipUI(ship);
    }
    if (auto base = Oasis::DynamicCast<Base>(player))
    {
        HandleBaseUI(base);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::HandleShipUI(Oasis::Reference<Ship> ship)
{
    float x = margin_horizontal;
    float y = margin_vertical;
    
    DrawActionIcon(m_moveIcon, x, y);
    AddPadding(margin_horizontal, x);
    DrawActionIcon(m_mineIcon, x, y);
    AddPadding(margin_horizontal, x);
    DrawActionIcon(m_transferIcon, x, y);
    // Draw the transfer icons directly above if transfering
    if (ship->GetUIState() == Ship::UIState::TRANSFER)
    {
        AddPadding(-action_icon_width, x);
        // The player pressed the transfer button and is now wanting to transfer a resource
        float y2 = y + action_icon_height + margin_vertical;
        m_transferMetalIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferMetalIcon);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_transferPopulationIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferPopulationIcon);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_transferFuelIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferFuelIcon);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_transferOxygenIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferOxygenIcon);
        // Restore the x to after the icon
        AddPadding(action_icon_width, x);
    }
    AddPadding(margin_horizontal, x);
    DrawActionIcon(m_colonizeIcon, x, y);
}

void UILayer::HandleBaseUI(Oasis::Reference<Base> base)
{
    float x = margin_horizontal;
    float y = margin_vertical;
    
    DrawActionIcon(m_createIcon, x, y);
    if (base->GetUIState() == Base::UIState::CREATE)
    {
        AddPadding(-action_icon_width, x);
        // The player pressed the create button and is now wanting to create a new ship
        float y2 = y + action_icon_height + margin_vertical;
        m_createScoutIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_createScoutIcon);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_createDroneShipIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_createDroneShipIcon);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_createFlagShipIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_createFlagShipIcon);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_createMotherShipIcon.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_createMotherShipIcon);
        AddPadding(action_icon_width, x);
    }
    AddPadding(margin_horizontal, x);
    DrawActionIcon(m_deployIcon, x, y);
    AddPadding(margin_horizontal, x);
    DrawActionIcon(m_transferIconBase, x, y);
    // Draw the transfer icons directly above if transfering
    if (base->GetUIState() == Base::UIState::TRANSFER)
    {
        AddPadding(-action_icon_width, x);
        // The player pressed the transfer button and is now wanting to transfer a resource
        float y2 = y + action_icon_height + margin_vertical;
        m_transferMetalIconBase.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferMetalIconBase);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_transferPopulationIconBase.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferPopulationIconBase);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_transferFuelIconBase.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferFuelIconBase);
        AddPadding(margin_vertical + create_ship_icon_height, y2);
        m_transferOxygenIconBase.SetPos(x, y2);
        Oasis::Renderer::DrawSprite(m_transferOxygenIconBase);
        // Restore the x to after the icon
        AddPadding(action_icon_width, x);
    }
    AddPadding(margin_horizontal, x);

    {   // Render ship storage AND building queue at bottom right I guess?
        float x = Oasis::WindowService::WindowWidth() - build_queue_icon_width - margin_horizontal;
        float y = margin_vertical;

        for (const Oasis::Reference<Entity> entity : base->GetShipStorage())
        {
            const Oasis::Reference<Ship> ship = Oasis::DynamicCast<Ship>(entity);
            Oasis::Reference<Oasis::Sprite> sprite = nullptr;
            if (Oasis::DynamicCast<MotherShip>(ship)) sprite = m_storageMotherShipIcon;
            if (Oasis::DynamicCast<FlagShip>(ship)) sprite = m_storageFlagShipIcon;
            if (Oasis::DynamicCast<DroneShip>(ship)) sprite = m_storageDroneShipIcon;
            if (Oasis::DynamicCast<Scout>(ship)) sprite = m_storageScoutIcon;
            if (sprite)
            {
                sprite->SetPos(x, y);
                Oasis::Renderer::DrawSprite(sprite.GetData());
            }
            else
            {
                OASIS_TRAP(false && "This should never happen");
            }
            AddPadding(margin_vertical + build_queue_icon_height, y);
        }

        bool first = true;
        for (const Base::BuildingEntry& building : base->GetBuildingQueue())
        {
            Oasis::Reference<Oasis::Sprite> sprite = nullptr;
            if (building.m_type == ShipType::MOTHERSHIP) sprite = m_queueMotherShipIcon;
            if (building.m_type == ShipType::FLAGSHIP) sprite = m_queueFlagShipIcon;
            if (building.m_type == ShipType::DRONESHIP) sprite = m_queueDroneShipIcon;
            if (building.m_type == ShipType::SCOUT) sprite = m_queueScoutIcon;
            if (sprite)
            {
                sprite->SetPos(x, y);
                Oasis::Renderer::DrawSprite(sprite.GetData());
            }
            else
            {
                OASIS_TRAP(false && "This should never happen");
            }
            // Assume the first one in the queue is the only one that can have any progress
            if (first)
            {
                first = false;
                // Render the progress
                GameSettings settings = GameService::GetGameSettings();
                float target = static_cast<float>(SecondsToBuildShip(building.m_type) / settings.m_seconds_per_tick);
                float ratio = static_cast<float>(building.m_elapsedTicks) / target;
                const float width = queue_progress_icon_width * ratio;
                const float progress_x = x + margin_horizontal;
                m_queueProgressIcon.SetPos(progress_x, y);
                m_queueProgressIcon.SetDimensions(width, queue_progress_icon_height);
                Oasis::Renderer::DrawSprite(m_queueProgressIcon);
            }
            AddPadding(margin_vertical + build_queue_icon_height, y);
        }
    }   
}

////////////////////////////////////////////////////////////////////////////////////////////
bool UILayer::HandleMousePress(float x, float y)
{
    // The button clicks should mirror rendering
    if (auto selected = GameService::GetSelectedEntity())
    {
        constexpr float margin_left = 10;
        constexpr float margin_bottom = 10;
        float icon_x = margin_left;
        float icon_y = margin_bottom;
        auto ship = Oasis::DynamicCast<Ship>(selected);
        auto base = Oasis::DynamicCast<Base>(selected);
        // First icon
        if (x > icon_x && x < icon_x + action_icon_width && y > icon_y && y < icon_y + action_icon_height)
        {
            if (ship && ship->CanMove())
            {
                // Change player to move state
                ship->MoveAction();
                return true;
            }
            if (base && base->CanCreate())
            {
                // Change base to create state
                base->CreateAction();
                return true;
            }
        }
        AddPadding(action_icon_width, icon_x);
        AddPadding(margin_left, icon_x);
        // Second icon
        if (x > icon_x && x < icon_x + action_icon_width && y > icon_y && y < icon_y + action_icon_height)
        {
            if (ship && ship->CanMine())
            {
                // Change player to move state
                ship->MineAction();
                return true;
            }
            if (base && base->CanDeploy() && base->GetShipStorage().size() > 0)
            {
                // Change base to deploy state
                base->DeployAction();
                return true;
            }
        }
        if (base && base->GetUIState() == Base::UIState::CREATE)
        {   // If the creation menu is open
            HandleShipCreateMousePress(x, y, base);
        }
        AddPadding(action_icon_width, icon_x);
        AddPadding(margin_left, icon_x);
        // Third icon
        if (x > icon_x && x < icon_x + action_icon_width && y > icon_y && y < icon_y + action_icon_height)
        {
            if (ship && ship->CanTransfer())
            {
                // Change player to move state
                ship->TransferAction();
                return true;
            }
            if (base && base->CanTransfer())
            {
                // Change base to deploy state
                base->TransferAction();
                return true;
            }
        }
		AddPadding(action_icon_width, icon_x);
		AddPadding(margin_left, icon_x);
        // Render transfer UI directly above the third icon
        if ((ship && ship->GetUIState() == Ship::UIState::TRANSFER) || (base && base->GetUIState() == Base::UIState::TRANSFER))
        {
            AddPadding(-action_icon_width, icon_x);
            // The player pressed the transfer button and is now wanting to transfer a resource
            float y2 = icon_y + action_icon_height + margin_vertical;
            if (x > icon_x && x < icon_x + action_icon_width && y > y2 && y < y2 + action_icon_height)
            {
                if (ship) ship->TransferResource(Ship::ResourceType::METAL);
                if (base) base->TransferResource(Base::ResourceType::METAL);
                return true;
            }
            AddPadding(margin_vertical + create_ship_icon_height, y2);
            if (x > icon_x && x < icon_x + action_icon_width && y > y2 && y < y2 + action_icon_height)
            {
                if (ship) ship->TransferResource(Ship::ResourceType::POPULATION);
                if (base) base->TransferResource(Base::ResourceType::POPULATION);
                return true;
            }
            AddPadding(margin_vertical + create_ship_icon_height, y2);
            if (x > icon_x && x < icon_x + action_icon_width && y > y2 && y < y2 + action_icon_height)
            {
                if (ship) ship->TransferResource(Ship::ResourceType::FUEL);
                if (base) base->TransferResource(Base::ResourceType::FUEL);
                return true;
            }
            AddPadding(margin_vertical + create_ship_icon_height, y2);
            if (x > icon_x && x < icon_x + action_icon_width && y > y2 && y < y2 + action_icon_height)
            {
                if (ship) ship->TransferResource(Ship::ResourceType::OXYGEN);
                if (base) base->TransferResource(Base::ResourceType::OXYGEN);
                return true;
            }
            // Restore the x to after the icon
            AddPadding(action_icon_width, icon_x);
        }
        // Fourth icon
        if (x > icon_x && x < icon_x + action_icon_width && y > icon_y && y < icon_y + action_icon_height)
        {
            if (ship)
            {
                // Change player to move state
                ship->ColonizeAction();
                return true;
            }
        }
        // Bottom right deployment list
        if (base && base->GetUIState() == Base::UIState::DEPLOY)
        {
            float icon_x = Oasis::WindowService::WindowWidth() - build_queue_icon_width - margin_horizontal;
            float icon_y = margin_vertical;
            for (const Oasis::Reference<Entity> entity : base->GetShipStorage())
            {
                const Oasis::Reference<Ship> ship = Oasis::DynamicCast<Ship>(entity);
                constexpr float w = build_queue_icon_width;
                constexpr float h = build_queue_icon_height;

                if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
                {
                    base->ChooseShipToDeploy(ship);
                    return true;
                }

                AddPadding(margin_vertical + build_queue_icon_height, icon_y);
            }
        }
    }
    return false;
}

bool UILayer::HandleShipCreateMousePress(float x, float y, Oasis::Reference<Base> base)
{
    // The player pressed the create button and is now wanting to create a new ship
    float icon_x = margin_horizontal;
    float icon_y = margin_vertical + action_icon_height + margin_vertical;

    constexpr float w = create_ship_icon_width;
    constexpr float h = create_ship_icon_height;

    // Scout
    if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
    {
        base->CreateShip(ShipType::SCOUT);
        return true;
    }
    // Droneship
    AddPadding(margin_vertical + create_ship_icon_height, icon_y);
    if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
    {
        base->CreateShip(ShipType::DRONESHIP);
        return true;
    }
    // Flagship
    AddPadding(margin_vertical + create_ship_icon_height, icon_y);
    if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
    {
        base->CreateShip(ShipType::FLAGSHIP);
        return true;
    }
    // Mothership
    AddPadding(margin_vertical + create_ship_icon_height, icon_y);
    if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
    {
        base->CreateShip(ShipType::MOTHERSHIP);
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::AddPadding(float padding, float& curr)
{
    curr += padding;
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::DrawResource(ResourceIcon resource, int numResource, float& curr_y)
{
    constexpr float margin_left = 10;
    constexpr float text_margin_left = 20;
    constexpr float text_margin_vert = 10;

    Oasis::Sprite sprite;
    if (resource == UILayer::ResourceIcon::OXYGEN) sprite = m_oxygenIcon;
    if (resource == UILayer::ResourceIcon::FUEL) sprite = m_fuelIcon;
    if (resource == UILayer::ResourceIcon::POPULATION) sprite = m_populationIcon;
    if (resource == UILayer::ResourceIcon::METAL) sprite = m_metalIcon;
    sprite.SetPos(margin_left, Oasis::WindowService::WindowHeight() - resource_icon_height - curr_y);
    Oasis::Renderer::DrawSprite(sprite);

    // Draw the text representing how much resource there is
    // TODO: Align right
    float x = margin_left + resource_icon_width + text_margin_left;
    float y = Oasis::WindowService::WindowHeight() - curr_y -resource_icon_height + text_margin_vert;
    Oasis::TextRenderer::DrawString(std::to_string(numResource), "default60", x, y, Oasis::Colours::WHITE);

    curr_y += resource_icon_height;
}

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::DrawActionIcon(Oasis::Reference<Oasis::Sprite> icon, float& curr_x, float y)
{
    icon->SetPos(curr_x, y);
    Oasis::Renderer::DrawSprite(icon);
    curr_x += action_icon_width;
}