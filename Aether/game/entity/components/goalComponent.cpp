#include "goalComponent.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/resourceComponent.hpp"

GoalComponent::GoalComponent(Ref<Entity> entity)
    : Component(entity)
{

}

void GoalComponent::Update(float delta)
{
    Ref<ResourceComponent> resource = m_entityRef->GetComponent<ResourceComponent>();
    OASIS_TRAP(resource);

    if (resource->GetPopulation() > TARGET_POPULATION)
    {
        // TODO: Need to handle actual game win
        Oasis::Console::AddLog("GAME WON!");
    }
}