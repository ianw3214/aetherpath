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
        x -= CameraService::GetX() + shape.m_offsetX;
        y -= CameraService::GetY() + shape.m_offsetY;
        Oasis::Renderer::DrawLine(x, y, x, y + shape.m_height, Oasis::Colours::RED);
        Oasis::Renderer::DrawLine(x, y, x + shape.m_width, y, Oasis::Colours::RED);
        Oasis::Renderer::DrawLine(x + shape.m_width, y, x + shape.m_width, y + shape.m_height, Oasis::Colours::RED);
        Oasis::Renderer::DrawLine(x, y + shape.m_height, x + shape.m_width, y + shape.m_height, Oasis::Colours::RED);
    }
    if (shape.m_type == Shape::Type::CIRCLE)
    {
        float last_x = x - CameraService::GetX() + shape.m_offsetX + shape.m_radius;
        float last_y = y - CameraService::GetY() + shape.m_offsetY;
        constexpr unsigned int granularity = 20;
        for (unsigned int i = 0; i <= granularity; ++i)
        {
            const float angle = 2.f * 3.14f * static_cast<float>(i) / static_cast<float>(granularity);
            float next_x = x - CameraService::GetX() + shape.m_offsetX + std::cos(angle) * shape.m_radius;
            float next_y = y - CameraService::GetY() + shape.m_offsetY + std::sin(angle) * shape.m_radius;
            Oasis::Renderer::DrawLine(last_x, last_y, next_x, next_y, Oasis::Colours::RED);
            last_x = next_x;
            last_y = next_y;
        }
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