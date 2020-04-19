#include "gameLayer.hpp"

#include <random>

#include "entities/player/player.hpp"
#include "entities/player/earth.hpp"
#include "entities/player/ship.hpp"
#include "entities/universe/resource.hpp"

#include "game/gameLayer/gameService.hpp"
#include "game/alertLayer/alertService.hpp"

GameLayer::GameLayer()
    : m_entities()
    , m_selected(nullptr)
    , m_tickAccumulator(0.f)
    , m_dayAccumulator(0.f)
{
    GameService::SetGameLayer(this);

    Oasis::Reference<Oasis::AudioResource> audio = Oasis::ResourceManager::LoadResource<Oasis::AudioResource>("res/music/track.wav");
    Oasis::AudioSource * source = new Oasis::AudioSource();
    source->SetVolume(0.1f);
    source->Play(audio.GetData());
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
        if (m_selected && m_selected->HandleClick(static_cast<float>(mouseEvent.GetX()), static_cast<float>(mouseEvent.GetY())))
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
    UpdateClockAndTick();
    for (Oasis::Reference<Entity> entity : m_entities)
    {
        entity->Update();
    }
}

void GameLayer::AddPlayer(Entity * entity)
{
    m_entities.push_back(entity);
    if (auto ref = Oasis::DynamicCast<PlayerEntity>(m_entities[m_entities.size() - 1]))
    {
        m_players.push_back(ref);
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
    AddPlayer(new Earth(
        settings.m_defaultEarthOxygen,
        settings.m_defaultEarthFuel,
        settings.m_defaultltEarthPopulation,
        settings.m_defaultEarthMetal
    ));

    // -----------------------------------------------------------------
    // TEMPORARY CODE
    {   // Mothership
        MotherShip * ship = new MotherShip();
        ship->InitializeShip(400.f, -400.f);
        ship->AddFuel(1000);
        ship->AddOxygen(20);
        ship->AddPopulation(500);
        AddPlayer(ship);
    }

    {   // Flagship
        FlagShip * ship = new FlagShip();
        ship->InitializeShip(-200.f, -200.f);
        ship->AddFuel(1000);
        ship->AddOxygen(20);
        ship->AddPopulation(500);
        AddPlayer(ship);
    }

    {   // Droneship
        DroneShip * ship = new DroneShip();
        ship->InitializeShip(200.f, -200.f);
        ship->AddFuel(1000);
        AddPlayer(ship);
    }

    {   // Scout
        Scout * ship = new Scout();
        ship->InitializeShip(300.f, 300.f);
        ship->AddFuel(1000);
        AddPlayer(ship);
    }
    // -----------------------------------------------------------------

    // Generate all other game entities randomly
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> position_dist(-(settings.m_mapBorder), settings.m_mapBorder);
    std::uniform_int_distribution<int> oxygen_dist(0, settings.m_oxygen_range);
    std::uniform_int_distribution<int> fuel_dist(0, settings.m_fuel_range);
    std::uniform_int_distribution<int> metal_dist(0, settings.m_metal_range);

    const int total_spawn_weights = settings.m_meteoroid_weight + settings.m_asteroid_weight + settings.m_planet_weight;
    std::uniform_int_distribution<int> spawn_dist(0, total_spawn_weights);

    const int area = (settings.m_mapBorder * 2) * (settings.m_mapBorder * 2);
    const int numThings = static_cast<int>(area * settings.m_densityPerSquareThousand) / 1000 / 1000;
    
    for (int i = 0; i < numThings; ++i)
    {
        const int oxygen = settings.m_oxygen_floor + oxygen_dist(el);
        const int fuel = settings.m_fuel_floor + fuel_dist(el);
        const int metal = settings.m_metal_floor + metal_dist(el);

        int key = spawn_dist(el);
        if (key < settings.m_meteoroid_weight)
        {
            Meteoroid * ent = new Meteoroid(oxygen, fuel, metal);
            ent->SetPos(static_cast<float>(position_dist(el)), static_cast<float>(position_dist(el)));
            m_entities.push_back(ent);
        }
        else
        {
            key -= settings.m_meteoroid_weight;
            if (key < settings.m_asteroid_weight)
            {
                Asteroid * ent = new Asteroid(
                    oxygen * settings.m_asteroid_multiplier, 
                    fuel * settings.m_asteroid_multiplier, 
                    metal * settings.m_asteroid_multiplier
                );
                ent->SetPos(static_cast<float>(position_dist(el)), static_cast<float>(position_dist(el)));
                m_entities.push_back(ent);
            }
            else
            {
                Planet * ent = new Planet(
                    oxygen * settings.m_planet_multiplier, 
                    fuel * settings.m_planet_multiplier, 
                    metal * settings.m_planet_multiplier
                );
                ent->SetPos(static_cast<float>(position_dist(el)), static_cast<float>(position_dist(el)));
                m_entities.push_back(ent);
            }
        }
    }

    {   // Create the goal planet
        const int oxygen = settings.m_oxygen_floor + oxygen_dist(el);
        const int fuel = settings.m_fuel_floor + fuel_dist(el);
        const int metal = settings.m_metal_floor + metal_dist(el);
        Goal * ent = new Goal(
            oxygen * settings.m_goal_multiplier, 
            fuel * settings.m_goal_multiplier, 
            metal * settings.m_goal_multiplier
        );
        ent->SetPos(static_cast<float>(position_dist(el)), static_cast<float>(position_dist(el)));
        // Set the goal planet a minimum distance away from earth
        OASIS_TRAP(settings.m_min_goal_distance < settings.m_mapBorder);
        while(ent->GetX() * ent->GetX() + ent->GetY() * ent->GetY() < settings.m_min_goal_distance * settings.m_min_goal_distance)
        {
            ent->SetPos(static_cast<float>(position_dist(el)), static_cast<float>(position_dist(el)));
        }
        m_entities.push_back(ent);
    }
}

void GameLayer::UpdateClockAndTick()
{
    GameSettings settings = GameService::GetGameSettings();

    // Microseconds to seconds
    float delta = Oasis::WindowService::GetDelta() / 1000000.f;
    m_tickAccumulator += delta;
    m_dayAccumulator += delta;
    if (m_tickAccumulator >= settings.m_seconds_per_tick)
    {
        m_tickAccumulator = 0.f;
        for (Oasis::Reference<Entity> entity : m_entities)
        {
            entity->Tick();
        }
    }
    if (m_dayAccumulator >= settings.m_seconds_per_day)
    {
        m_dayAccumulator = 0.f;
        for (Oasis::Reference<Entity> entity : m_entities)
        {
            entity->DayCycle();
        }
    }

    {   // Check for game lost conditions
        int total_population = 0;
        for (auto player : m_players)
        {
            total_population += player->GetPopulation();
        }
        if (total_population <= 0)
        {
            AlertService::Lose();
        }
    }
}