#include "entity.hpp"

void RenderEntity::SetSprite(const std::string& path, float width, float height)
{
    m_sprite = Oasis::Sprite(path);
    m_width = width == -1 ? m_sprite.GetWidth() : width;
    m_height = height == -1 ? m_sprite.GetHeight() : height;
}

void RenderEntity::Render() 
{
    const float scale = Camera::GetCamera()->GetScale();
    float window_width = static_cast<float>(Oasis::WindowService::WindowWidth());
    float window_height = static_cast<float>(Oasis::WindowService::WindowHeight());
    float width = m_width * scale;
    float height = m_height * scale;
    float screen_x = (GetX() - Camera::GetCamera()->GetX()) * scale + window_width / 2;
    float screen_y = (GetY() - Camera::GetCamera()->GetY()) * scale + window_height / 2;
    if (screen_x > -width && screen_x < window_width && screen_y > -height && screen_y < window_height)
    {
        // Render
        m_sprite.SetPos(screen_x, screen_y);
        m_sprite.SetDimensions(width, height);
        m_sprite.SetTint(Oasis::Colours::WHITE, static_cast<float>(Selected()) * 0.2f);
        Oasis::Renderer::DrawSprite(m_sprite);
    }
}

bool RenderEntity::Colliding(float x, float y) const
{
    // Assume the input points are raw coords and not screen adjusted
    return x > GetX() && x < GetX() + GetWidth() && y > GetY() && y < GetY() + GetHeight();
}
