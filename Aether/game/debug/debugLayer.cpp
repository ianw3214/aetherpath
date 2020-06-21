#include "debugLayer.hpp"

#include "game/entity/entity.hpp"
#include "game/gamelayer.hpp"
#include "game/camera/camera.hpp"

#include "game/entity/components/collisionComponent.hpp"

void DebugLayer::Init()
{
    Oasis::ImGuiWrapper::AddWindowFunction([&](){

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
        const float x = CameraService::RawToScreenX(x + shape.m_offsetX);
        const float y = CameraService::RawToScreenY(y + shape.m_offsetY);
        const float width = shape.m_width * CameraService::GetScale();
        const float height = shape.m_height * CameraService::GetScale();
        GameService::DrawRect(x, y, width, height, 1);
        // Oasis::Renderer::DrawLine(x, y, x, y + height, Oasis::Colours::RED);
        // Oasis::Renderer::DrawLine(x, y, x + width, y, Oasis::Colours::RED);
        // Oasis::Renderer::DrawLine(x + width, y, x + width, y + height, Oasis::Colours::RED);
        // Oasis::Renderer::DrawLine(x, y + height, x + width, y + height, Oasis::Colours::RED);
    }
    if (shape.m_type == Shape::Type::CIRCLE)
    {
        float center_x = CameraService::RawToScreenX(x + shape.m_offsetX);
        float center_y = CameraService::RawToScreenY(y + shape.m_offsetY);
        float radius = shape.m_radius * CameraService::GetScale();
        GameService::DrawCircle(center_x, center_y, radius, 1);
        /*
        constexpr unsigned int granularity = 20;
        for (unsigned int i = 0; i <= granularity; ++i)
        {
            const float angle = 2.f * 3.14f * static_cast<float>(i) / static_cast<float>(granularity);
            float next_x = CameraService::RawToScreenX(x + shape.m_offsetX + std::cos(angle) * shape.m_radius);
            float next_y = CameraService::RawToScreenY(y + shape.m_offsetY + std::sin(angle) * shape.m_radius);
            Oasis::Renderer::DrawLine(last_x, last_y, next_x, next_y, Oasis::Colours::RED);
            last_x = next_x;
            last_y = next_y;
        }
        */
    }
}

void DebugLayer::Update() 
{
    for (Ref<Entity> entity : GameService::GetEntities())
    {
        // Render entity collision if it exists
        if (auto collision = entity->GetComponent<CollisionComponent>())
        {
            DrawCollision(entity->GetX(), entity->GetY(), collision->GetShape());
        }
    }
}