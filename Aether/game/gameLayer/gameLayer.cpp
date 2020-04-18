#include "gameLayer.hpp"

#include <random>

#include "entities/player/earth.hpp"
#include "entities/player/ship.hpp"
#include "entities/universe/resource.hpp"

#include "game/gameLayer/gameService.hpp"

GameLayer::GameLayer()
    : m_entities()
    , m_selected(nullptr)
{
    GameService::SetGameLayer(this);
}

void GameLayer::Init()
{
    GenerateGameWorld();
}

void GameLayer::Close()
{

}

bool GameLayer::HandleEvent(const Oasis::Event& event)
{

    if (event.GetType() == Oasis::EventType::MOUSE_PRESS)
    {
        const Oasis::MousePressedEvent& mouseEvent = dynamic_cast<const Oasis::MousePressedEvent&>(event);
        // Try to handle the click for the ship first
        if (m_selected && m_selected->HandleClick(mouseEvent.GetX(), mouseEvent.GetY()))
        {
            return true;
        }
        // try to select a unit
        bool selected = false;
        for (Oasis::Reference<Entity> entity : m_entities)
        {
            Oasis::Reference<RenderEntity> renderEntity = Oasis::DynamicCast<RenderEntity>(entity);
            if (renderEntity)
            {
                float scale = Camera::GetCamera()->GetScale();
                float x = Camera::ScreenToRawX(mouseEvent.GetX());
				// this is such lazy code but I'm a lazy person so whatever
                float y = Camera::ScreenToRawY(mouseEvent.GetY());
                if (renderEntity->Colliding(x, y))
                {
                    SelectEntity(Oasis::DynamicCast<Entity>(renderEntity));
                    selected = true;
                    break;
                }
            }
        }
        if (!selected)
        {
            SelectEntity(nullptr);
        }
    }
    return false;
}

void GameLayer::Update() 
{
    for (Oasis::Reference<Entity> entity : m_entities)
    {
        entity->Update();
    }
}

void GameLayer::SelectEntity(Oasis::Reference<Entity> entity)
{
    // Passing in a null entity will just deselct it
    if (m_selected)
    {
        m_selected->Deselect();
    }
    m_selected = entity;
    if (m_selected)
    {
        entity->Select();
    }
}

void GameLayer::GenerateGameWorld()
{
    GameSettings settings = GameService::GetGameSettings();

    // Mother earth always generated at 0, 0
    m_entities.push_back(new Earth());

    // -----------------------------------------------------------------
    // TEMPORARY CODE
    {   // New ship
        FlagShip * ship = new FlagShip();
        ship->InitializeShip(-200.f, -200.f);
        m_entities.push_back(ship);
    }

    {   // New ship
        FlagShip * ship = new FlagShip();
        ship->InitializeShip(200.f, -200.f);
        m_entities.push_back(ship);
    }
    // -----------------------------------------------------------------

    // Generate all other game entities randomly
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> position_dist(-(settings.m_mapBorder), settings.m_mapBorder);

    const int area = (settings.m_mapBorder * 2) * (settings.m_mapBorder * 2);
    const int numThings = area * settings.m_densityPerSquareThousand / 1000 / 1000;
    
    for (int i = 0; i < numThings; ++i)
    {
        ResourceEntity * ent = new ResourceEntity();
        ent->SetPos(static_cast<float>(position_dist(el)), static_cast<float>(position_dist(el)));
        m_entities.push_back(ent);
    }

    /*
    {   // New resource entity
        ResourceEntity * ent = new ResourceEntity();
        ent->SetPos(-150.f, 200.f);
        m_entities.push_back(ent);
    }
    */
}