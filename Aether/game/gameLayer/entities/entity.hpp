#pragma once
#include "oasis.h"

#include <string>

#include "game/camera/camera.hpp"

// -------------------------------------------------------------
class Entity
{
public:
    Entity() : m_x(0.f), m_y(0.f) {}
    virtual ~Entity() {}

    inline float GetX() const { return m_x; }
    inline float GetY() const { return m_y; }
    inline void SetX(float x) { m_x = x; }
    inline void SetY(float y) { m_y = y; }
    inline void SetPos(float x, float y) { m_x = x; m_y = y; }

    virtual void Update() {}

private:
    float m_x;
    float m_y;
};

// -------------------------------------------------------------
class RenderEntity : public Entity
{
public:
    inline float GetWidth() const { return m_width; }
    inline float GetHeight() const { return m_height; }
    inline void SetWidth(float w) { m_width = w; }
    inline void SetHeight(float h) { m_height = h; }
    inline void SetDimensions(float w, float h) { m_width = w; m_height = h; }

    void SetSprite(const std::string& path, float width = -1.f, float height = -1.f);
    void Render();

    // Don't override update, let derived entities render themselves for more control

protected:
    Oasis::Sprite m_sprite;

    float m_width;
    float m_height;
};