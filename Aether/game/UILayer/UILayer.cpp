#include "UILayer.hpp"

#include "game/gameLayer/gameService.hpp"
#include "game/gameLayer/entities/entity.hpp"
#include "game/gameLayer/entities/player/player.hpp"
#include "game/gameLayer/entities/universe/resource.hpp"

// Use fixed size UI
constexpr float icon_width = 80.f;
constexpr float icon_height = 80.f;

void UILayer::Init()
{
    m_cursor = Oasis::Sprite("res/icons/cursor.png");

    m_oxygenIcon = Oasis::Sprite("res/icons/oxygen.png");
    m_fuelIcon = Oasis::Sprite("res/icons/fuel.png");
    m_populationIcon = Oasis::Sprite("res/icons/population.png");
    m_metalIcon = Oasis::Sprite("res/icons/metal.png");
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
    return false;
}

void UILayer::Update() 
{
    Oasis::Renderer::DrawSprite(m_cursor);

    // Show UI based on what's selected
    if (auto selected = GameService::GetSelectedEntity())
    {
        if (auto resource = Oasis::DynamicCast<ResourceEntity>(selected))
        {
            float y = 10;
            DrawResource(ResourceIcon::OXYGEN, resource->GetOxygen(), y);
            AddPadding(10, y);
            DrawResource(ResourceIcon::FUEL, resource->GetFuel(),y);
            AddPadding(10, y);
            DrawResource(ResourceIcon::METAL, resource->GetMetal(),y);
        }
        if (auto player = Oasis::DynamicCast<PlayerEntity>(selected))
        {
            float y = 10;
            DrawResource(ResourceIcon::OXYGEN, player->GetOxygen(), y);
            AddPadding(10, y);
            DrawResource(ResourceIcon::FUEL, player->GetFuel(), y);
            AddPadding(10, y);
            DrawResource(ResourceIcon::POPULATION, player->GetPopulation(),y);
            AddPadding(10, y);
            DrawResource(ResourceIcon::METAL, player->GetMetal(),y);
        }
    }
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
    sprite.SetPos(margin_left, Oasis::WindowService::WindowHeight() - icon_height - curr_y);
    Oasis::Renderer::DrawSprite(sprite);

    // Draw the text representing how much resource there is
    // TODO: Align right
    float x = margin_left + icon_width + text_margin_left;
    float y = Oasis::WindowService::WindowHeight() - curr_y -icon_height + text_margin_vert;
    Oasis::TextRenderer::DrawString(std::to_string(numResource), "default60", x, y, Oasis::Colours::WHITE);

    curr_y += icon_height;
}
