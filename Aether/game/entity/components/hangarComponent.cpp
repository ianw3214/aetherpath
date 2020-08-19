#include "hangarComponent.hpp"

#include "game/gamelayer.hpp"
#include "game/entity/components/renderComponent.hpp"
#include "game/entity/components/collisionComponent.hpp"
#include "game/entity/components/moveComponent.hpp"
#include "game/entity/components/resourceComponent.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

HangarComponent::HangarComponent(Ref<Entity> entity, int capacity, int deployRange)
    : Component(entity)
    , m_capacity(capacity)
    , m_deployRange(deployRange)
    , m_ships(0)
{

}

void HangarComponent::Update(float delta)
{

}

bool HangarComponent::CreateShip()
{
    // If we are full, do nothing
    if (m_ships >= m_capacity)
    {
        return false;
    }

    // Temporarily just have a set amount of resources to require
    auto resource = GetEntity()->GetComponent<ResourceComponent>();
    OASIS_TRAP(resource);
    if (!resource->ConsumeMetal(10))
    {
        return false;
    }

    m_ships++;
    return true;
}

bool HangarComponent::DeployShip(float x, float y)
{
    // If no ships in the hangar, do nothing
    if (m_ships <= 0)
    {
        Oasis::Console::AddLog("Can't deploy ship: no ships to deploy");
        return false;
    }

    // If the point is outside the deploy range, do nothing
    int x_diff = GetEntity()->GetX() - x;
    int y_diff = GetEntity()->GetY() - y;
    if (x_diff * x_diff + y_diff * y_diff > m_deployRange * m_deployRange)
    {
        Oasis::Console::AddLog("Can't deploy ship: not in range");
        return false;
    }

    // TODO: Not sure if ship creation should stay in hangar component
    Entity * ship = new Entity();
    ship->SetX(x);
    ship->SetY(y);
    ship->AddComponent(new RenderComponent(ship, "res/sprites/scout.png", 130.f, 80.f));
    ship->AddComponent(new CollisionComponent(ship, Shape::GenerateRect(130.f, 80.f, -60.f, -40.f)));
    ship->AddComponent(new ResourceComponent(ship, 100, 100, 100, 100));
    ship->AddComponent(new MoveComponent(ship));
    GameService::AddEntity(ship);

    m_ships--;
    return true;
}