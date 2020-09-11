#include "hangarComponent.hpp"

#include "game/gamelayer.hpp"
#include "game/entity/components/renderComponent.hpp"
#include "game/entity/components/collisionComponent.hpp"
#include "game/entity/components/moveComponent.hpp"
#include "game/entity/components/resourceComponent.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

#include "game/camera/camera.hpp"

#include "game/entity/serializer/serializer.hpp"

HangarComponent::HangarComponent(Ref<Entity> entity, int capacity, int deployRange)
    : Component(entity)
    , m_capacity(capacity)
    , m_deployRange(deployRange)
    , m_ships(0)
{

}

void HangarComponent::Update(float delta)
{
    // Show the deploy range if the user is about to deploy
    if (GameService::IsUserDeployAction())
    {
        // Only show the range from if the user is selecting this hangar
        if (GetEntity() == GameService::GetSelected())
        {
            const float x = CameraService::RawToScreenX(GetEntity()->GetX());
            const float y = CameraService::RawToScreenY(GetEntity()->GetY());
            const float radius = static_cast<float>(m_deployRange) * CameraService::GetScale();
            GameService::DrawCircle(x, y, radius, 1, Oasis::Colours::RED);
        }
    }
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
    int x_diff = static_cast<int>(GetEntity()->GetX() - x);
    int y_diff = static_cast<int>(GetEntity()->GetY() - y);
    if (x_diff * x_diff + y_diff * y_diff > m_deployRange * m_deployRange)
    {
        Oasis::Console::AddLog("Can't deploy ship: not in range");
        return false;
    }

    // TODO: Not sure if ship creation should stay in hangar component
    Entity * ship = EntitySerializer::GetInstance()->GetEntity("test_entity.json");
    ship->SetX(x);
    ship->SetY(y);
    GameService::AddEntity(ship);

    m_ships--;
    return true;
}

HangarComponent* HangarComponent::LoadFromJson(const json& data, Ref<Entity> entity)
{
    int capacity = 10;
    int deployRange = 500;
    if (data.find("capacity") != data.end() && data["capacity"].is_number_integer())
    {
        capacity = data["capacity"];
    }
    if (data.find("deployRange") != data.end() && data["deployRange"].is_number_integer())
    {
        deployRange = data["deployRange"];
    }
    return new HangarComponent(entity, capacity, deployRange);
}