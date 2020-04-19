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

////////////////////////////////////////////////////////////////////////////////////////////
void UILayer::Init()
{
    m_cursor = Oasis::Sprite("res/icons/cursor.png");

    m_oxygenIcon = Oasis::Sprite("res/icons/oxygen.png");
    m_fuelIcon = Oasis::Sprite("res/icons/fuel.png");
    m_populationIcon = Oasis::Sprite("res/icons/population.png");
    m_metalIcon = Oasis::Sprite("res/icons/metal.png");
    
    m_moveIcon = Oasis::Sprite("res/icons/move.png");
    m_mineIcon = Oasis::Sprite("res/icons/mine.png");

    m_createIcon = Oasis::Sprite("res/icons/create.png");

    m_createMotherShipIcon = Oasis::Sprite("res/icons/create_mothership.png");
    m_createFlagShipIcon = Oasis::Sprite("res/icons/create_flagship.png");
    m_createDroneShipIcon = Oasis::Sprite("res/icons/create_droneship.png");
    m_createScoutIcon = Oasis::Sprite("res/icons/create_scout.png");

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
    if (event.GetType() == Oasis::EventType::MOUSE_MOVE)
    {
        const Oasis::MouseMovedEvent& mouseEvent = dynamic_cast<const Oasis::MouseMovedEvent&>(event);
        float mouse_x = static_cast<float>(mouseEvent.GetX());
        float mouse_y = static_cast<float>(Oasis::WindowService::WindowHeight() - mouseEvent.GetY());
        m_cursor.SetPos(mouse_x, mouse_y - m_cursor.GetHeight());
    }
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
                // Change player to move UI state
                player->MoveAction();
                return true;
            }
            if (keyEvent.GetKey() == SDL_SCANCODE_2)
            {
                // Change player to mine UI state
                player->MineAction();
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
    // Draw the cursor on top of other things
    Oasis::Renderer::DrawSprite(m_cursor);
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
    float y = 10;
    DrawResource(ResourceIcon::OXYGEN, player->GetOxygen(), y);
    AddPadding(10, y);
    DrawResource(ResourceIcon::FUEL, player->GetFuel(), y);
    AddPadding(10, y);
    DrawResource(ResourceIcon::POPULATION, player->GetPopulation(),y);
    AddPadding(10, y);
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
    constexpr float margin_left = 10;
    constexpr float margin_bottom = 10;

    float x = margin_left;
    float y = margin_bottom;
    
    DrawActionIcon(m_moveIcon, x, y);
    AddPadding(margin_left, x);
    DrawActionIcon(m_mineIcon, x, y);
}

void UILayer::HandleBaseUI(Oasis::Reference<Base> base)
{
    constexpr float margin_horizontal = 10;
    constexpr float margin_vertical = 10;

    float x = margin_horizontal;
    float y = margin_vertical;
    
    DrawActionIcon(m_createIcon, x, y);

    if (base->GetUIState() == Base::UIState::CREATE)
    {
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
    }
    AddPadding(margin_horizontal, x);
    // DrawActionIcon(m_mineIcon, x, y);

    {   // Render ship storage AND building queue at bottom right I guess?
        float x = Oasis::WindowService::WindowWidth() - build_queue_icon_width - margin_horizontal;
        float y = margin_vertical;

        for (const Oasis::Reference<Ship> ship : base->GetShipStorage())
        {
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
            {
                if (ship && ship->CanMine())
                {
                    // Change player to move state
                    ship->MineAction();
                    return true;
                }
            }
        }
        if (base && base->GetUIState() == Base::UIState::CREATE)
        {   // If the creation menu is open
            constexpr float margin_left = 10;
            constexpr float margin_bottom = 10;

            // The player pressed the create button and is now wanting to create a new ship
            float icon_x = margin_left + action_icon_width;
            float icon_y = margin_bottom + action_icon_height + margin_bottom;

            constexpr float w = create_ship_icon_width;
            constexpr float h = create_ship_icon_height;

            // Scout
            if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
            {
                base->CreateShip(ShipType::SCOUT);
            }
            // Droneship
            AddPadding(margin_bottom + create_ship_icon_height, icon_y);
            if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
            {
                base->CreateShip(ShipType::DRONESHIP);
            }
            // Flagship
            AddPadding(margin_bottom + create_ship_icon_height, icon_y);
            if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
            {
                base->CreateShip(ShipType::FLAGSHIP);
            }
            // Mothership
            AddPadding(margin_bottom + create_ship_icon_height, icon_y);
            if (x > icon_x && x < icon_x + w && y > icon_y && y < icon_y + h)
            {
                base->CreateShip(ShipType::MOTHERSHIP);
            }
        }
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