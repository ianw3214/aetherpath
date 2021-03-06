#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

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

    static Shape LoadFromJson(const json& data);
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

    // Collision calculations
    bool Colliding(float x, float y) const;
    bool Colliding(float x, float y, const Shape& shape) const;
private:
    Shape m_shape;
public:
    // Serialization
    static std::string GetID() { return "collision"; }
    static CollisionComponent* LoadFromJson(const json& data, Ref<Entity> entity);
};