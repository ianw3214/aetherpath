#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

////////////////////////////////////////////////////////////////
struct Shape
{
    enum class Type
    {
        INVALID = -1,
        RECT,
        CIRCLE
    };
    Type m_type;
    float m_offsetX;
    float m_offsetY;

    union {
        struct {
            float m_radius;
        };
        struct {
            float m_width;
            float m_height;
        };
    };

    static Shape GenerateRect(float width, float height, float offsetX = 0.f, float offsetY = 0.f);
    static Shape GenerateCircle(float radius, float offsetX = 0.f, float offsetY = 0.f);
};

////////////////////////////////////////////////////////////////
class CollisionComponent : public Component
{
public:
    CollisionComponent(Ref<Entity> entity, Shape shape = {Shape::Type::INVALID});
    // Collision components don't need to actually update anything because
    //   collisions are handled by an external systems
    // virtual void Update(float delta) override;

    inline bool IsValid() const { return m_shape.m_type != Shape::Type::INVALID; }
    const Shape& GetShape() const { return m_shape; }
private:
    Shape m_shape;
};