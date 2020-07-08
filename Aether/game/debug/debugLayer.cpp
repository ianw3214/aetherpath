#include "debugLayer.hpp"

#include "game/entity/entity.hpp"
#include "game/gamelayer.hpp"
#include "game/camera/camera.hpp"

#include "game/entity/components/collisionComponent.hpp"
#include "game/entity/components/moveComponent.hpp"
#include "game/entity/components/resourceComponent.hpp"

// TODO: Need to have a better solution for this
#include "../../Oasis/vendor/imgui/imgui.h"

void DebugLayer::Init()
{
    Oasis::ImGuiWrapper::AddWindowFunction([&](){
        ImGui::Begin("Debug");

        if (Ref<Entity> selected = GameService::GetSelected())
        {
            if (auto resource = selected->GetComponent<ResourceComponent>())
            {
                ImGui::Text("Population: %i", resource->GetPopulation());
                ImGui::Text("Oxygen: %i", resource->GetOxygen());
                ImGui::Text("Fuel: %i", resource->GetFuel());
                ImGui::Text("Metal: %i", resource->GetMetal());
            }
        }

        ImGui::End();
    });
}

void DebugLayer::Close()
{

}

bool DebugLayer::HandleEvent(const Oasis::Event& event)
{
    return false;
}

void DrawCollision(float x, float y, const Shape& shape)
{
    if (shape.m_type == Shape::Type::RECT)
    {
        const float new_x = CameraService::RawToScreenX(x + shape.m_offsetX);
        const float new_y = CameraService::RawToScreenY(y + shape.m_offsetY);
        const float width = shape.m_width * CameraService::GetScale();
        const float height = shape.m_height * CameraService::GetScale();
        GameService::DrawRect(new_x, new_y, width, height, 1, Oasis::Colours::BLUE);
    }
    if (shape.m_type == Shape::Type::CIRCLE)
    {
        float center_x = CameraService::RawToScreenX(x + shape.m_offsetX);
        float center_y = CameraService::RawToScreenY(y + shape.m_offsetY);
        float radius = shape.m_radius * CameraService::GetScale();
        GameService::DrawCircle(center_x, center_y, radius, 1, Oasis::Colours::BLUE);
    }
}

void DrawMove(float x, float y, float target_x, float target_y)
{
    x = CameraService::RawToScreenX(x);
    y = CameraService::RawToScreenY(y);
    target_x = CameraService::RawToScreenX(target_x);
    target_y = CameraService::RawToScreenY(target_y);
    GameService::DrawLine(x, y, target_x, target_y, 1, Oasis::Colours::GREEN);
}

void DebugLayer::Update() 
{
    for (Ref<Entity> entity : GameService::GetEntities())
    {
        const float x = entity->GetX();
        const float y = entity->GetY();
        // Render entity collision if it exists
        if (auto collision = entity->GetComponent<CollisionComponent>())
        {
            DrawCollision(x, y, collision->GetShape());
        }
        // Render move if it exists and moving
        if (auto move = entity->GetComponent<MoveComponent>())
        {
            if (move->Moving())
            {
                DrawMove(x, y, move->GetTargetX(), move->GetTargetY());
            }
        }
    }
}