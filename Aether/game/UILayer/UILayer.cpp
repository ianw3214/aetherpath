#include "UILayer.hpp"

#include "game/gameLayer/gameService.hpp"
#include "game/gameLayer/entities/entity.hpp"
#include "game/gameLayer/entities/player/player.hpp"
#include "game/gameLayer/entities/player/ship.hpp"
#include "game/gameLayer/entities/universe/resource.hpp"

// Use fixed size UI
constexpr float resource_icon_width = 80.f;
constexpr float resource_icon_height = 80.f;
constexpr float action_icon_width = 100.f;
constexpr float action_icon_height = 100.f;

void UILayer::Init()
{
    m_cursor = Oasis::Sprite("res/icons/cursor.png");

    m_oxygenIcon = Oasis::Sprite("res/icons/oxygen.png");
    m_fuelIcon = Oasis::Sprite("res/icons/fuel.png");
    m_populationIcon = Oasis::Sprite("res/icons/population.png");
    m_metalIcon = Oasis::Sprite("res/icons/metal.png");
    
    m_moveIcon = Oasis::Sprite("res/icons/move.png");
}

void UILayer::Close()
{

}

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
    return false;
}

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

void UILayer::HandleResourceUI(Oasis::Reference<ResourceEntity> resource)
{
    float y = 10;
    DrawResource(ResourceIcon::OXYGEN, resource->GetOxygen(), y);
    AddPadding(10, y);
    DrawResource(ResourceIcon::FUEL, resource->GetFuel(),y);
    AddPadding(10, y);
    DrawResource(ResourceIcon::METAL, resource->GetMetal(),y);
}

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
}

void UILayer::HandleShipUI(Oasis::Reference<Ship> ship)
{
    constexpr float margin_left = 10;
    constexpr float margin_bottom = 10;

    float x = margin_left;
    float y = margin_bottom;
    m_moveIcon.SetPos(x, y);
    Oasis::Renderer::DrawSprite(m_moveIcon);
}

bool UILayer::HandleMousePress(float x, float y)
{
    // The button clicks should mirror rendering
    if (auto selected = GameService::GetSelectedEntity())
    {
        // Resources do nothing on click for now
        /*
        if (auto resource = Oasis::DynamicCast<ResourceEntity>(selected))
        {
            HandleResourceUI(resource);
        }
        */
        if (auto player = Oasis::DynamicCast<PlayerEntity>(selected))
        {
            if (player->CanMove())
            {
                constexpr float margin_left = 10;
                constexpr float margin_bottom = 10;

                float icon_x = margin_left;
                float icon_y = margin_bottom;
                if (x > icon_x && x < icon_x + action_icon_width && y > icon_y && y < icon_y + action_icon_height)
                {
                    player->TryMove();
                    return true;
                }
            }
        }
    }
    return false;
}

void UILayer::AddPadding(float padding, float& curr_y)
{
    curr_y += padding;
}

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
