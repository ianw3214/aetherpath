#include "map.hpp"

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/renderComponent.hpp"
#include "game/entity/components/collisionComponent.hpp"
#include "game/entity/components/moveComponent.hpp"
#include "game/entity/components/resourceComponent.hpp"

void Map::GenerateMap()
{
    GenerateEarth();
    GenerateMoon();

    /////////////////////////////////////////////////////////
    // DEBUG SHIP
    Entity * ship = new Entity();
    ship->SetX(400.f);
    ship->SetY(400.f);
    ship->AddComponent(new RenderComponent(ship, "res/sprites/scout.png", 130.f, 80.f));
    ship->AddComponent(new CollisionComponent(ship, Shape::GenerateRect(130.f, 80.f, -60.f, -40.f)));
    ship->AddComponent(new ResourceComponent(ship, 100, 100, 100, 100));
    ship->AddComponent(new MoveComponent(ship));
    GameService::AddEntity(ship);
    /////////////////////////////////////////////////////////
}

void Map::GenerateEarth()
{
    Entity * earth = new Entity();
    earth->SetX(0.f);
    earth->SetY(0.f);
    earth->AddComponent(new RenderComponent(earth, "res/sprites/earth.png", 400.f, 400.f));
    earth->AddComponent(new CollisionComponent(earth, Shape::GenerateCircle(200.f)));
    earth->AddComponent(new ResourceComponent(earth, 100, 100, 100, 100));
    // earth->AddComponent(new MoveComponent(earth));
    GameService::AddEntity(earth);
}

void Map::GenerateMoon()
{
    Entity * moon = new Entity();
    moon->SetX(400.f);
    moon->SetY(-400.f);
    // TODO: Need actual moon sprite
    moon->AddComponent(new RenderComponent(moon, "res/sprites/earth.png", 400.f, 400.f));
    moon->AddComponent(new CollisionComponent(moon, Shape::GenerateCircle(200.f)));
    moon->AddComponent(new ResourceComponent(moon, 100, 100, 100, 100));
    // moon->AddComponent(new MoveComponent(moon));
    GameService::AddEntity(moon);
}