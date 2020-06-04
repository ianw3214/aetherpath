#include "collisionComponent.hpp"
#include "game/entity/entity.hpp"

Shape Shape::GenerateRect(float width, float height, float offsetX, float offsetY)
{
    Shape shape = {Shape::Type::RECT, offsetX, offsetY};
    shape.m_width = width;
    shape.m_height = height;
    return shape;
}

Shape Shape::GenerateCircle(float radius, float offsetX, float offsetY)
{
    Shape shape = {Shape::Type::CIRCLE, offsetX, offsetY};
    shape.m_radius = radius;
    return shape;
}


CollisionComponent::CollisionComponent(Ref<Entity> entity, Shape shape)
    : Component(entity)
    , m_shape(shape)
{

}