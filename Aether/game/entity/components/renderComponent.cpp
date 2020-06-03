#include "renderComponent.hpp"
#include "game/entity/entity.hpp"

#include "game/camera/camera.hpp"

RenderComponent::RenderComponent(Ref<Entity> entity, const std::string& path, float width, float height)
    : Component(entity)
    , m_sprite(path)
    , m_width(width)
    , m_height(height)
{
    // If no set width/height, use the width/height of the sprite
    if (width == 0.f && height == 0.f)
    {
        m_width = m_sprite.GetWidth();
        m_height = m_sprite.GetHeight();
    }
}

void RenderComponent::Update(float delta)
{
    m_sprite.SetDimensions(m_width, m_height);
    m_sprite.SetPos(m_entityRef->GetX() - CameraService::GetX(), m_entityRef->GetY() - CameraService::GetY());
    Oasis::Renderer::DrawSprite(&m_sprite);
}