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

Shape Shape::LoadFromJson(const json& data)
{
    if (data.find("type") != data.end() && data["type"].is_string())
    {
        // TODO: Function to get type string from enum to avoid small errors
        // TODO: More error checking for missing keys
        if (data["type"] == "rect")
        {
            Shape result = { Type::RECT, 0.f, 0.f };
            result.m_width = data["width"];
            result.m_height = data["height"];
            return result;
        }
        if (data["type"] == "circle")
        {
            Shape result = { Type::CIRCLE, 0.f, 0.f };
            result.m_radius = data["radius"];
            return result;
        }
    }
    return {Type::INVALID};
}

CollisionComponent::CollisionComponent(Ref<Entity> entity, Shape shape)
    : Component(entity)
    , m_shape(shape)
{

}

// The x and y position used is the raw x/y positions
bool CollisionComponent::Colliding(float x, float y) const
{
    const float shape_x = m_entityRef->GetX() + m_shape.m_offsetX;
    const float shape_y = m_entityRef->GetY() + m_shape.m_offsetY;
    if (m_shape.m_type == Shape::Type::RECT)
    {
        const bool h_overlap = x >= shape_x && x <= shape_x + m_shape.m_width;
        const bool v_overlap = y >= shape_y && y <= shape_y + m_shape.m_height;
        return h_overlap && v_overlap;
    }
    if (m_shape.m_type == Shape::Type::CIRCLE)
    {
        const float x_diff = x - shape_x;
        const float y_diff = y - shape_y;
        return x_diff * x_diff + y_diff * y_diff <= m_shape.m_radius * m_shape.m_radius;
    }
    return false;
}

bool CollisionComponent::Colliding(float x, float y, const Shape& shape) const
{
    const float shape_x = m_entityRef->GetX() + m_shape.m_offsetX;
    const float shape_y = m_entityRef->GetY() + m_shape.m_offsetY;
    const float other_x = x + shape.m_offsetX;
    const float other_y = y + shape.m_offsetY;
    if (m_shape.m_type == Shape::Type::RECT)
    {
        if (shape.m_type == Shape::Type::RECT)
        {
            const bool h_overlap = shape_x <= other_x + shape.m_width && shape_x + m_shape.m_width >= other_x;
            const bool v_overlap = shape_y <= other_y + shape.m_height && shape_y + m_shape.m_height >= other_y;
            return h_overlap && v_overlap;
        }
        if (shape.m_type == Shape::Type::CIRCLE)
        {
            const float x_diff = other_x - std::max(shape_x, std::min(other_x, shape_x + m_shape.m_width));
            const float y_diff = other_y - std::max(shape_y, std::min(other_y, shape_y + m_shape.m_height));
            return x_diff * x_diff + y_diff * y_diff <= shape.m_radius * shape.m_radius;
        }
    }
    if (m_shape.m_type == Shape::Type::CIRCLE)
    {
        if (shape.m_type == Shape::Type::RECT)
        {
            const float x_diff = shape_x - std::max(other_x, std::min(shape_x, other_x + shape.m_width));
            const float y_diff = shape_y - std::max(other_y, std::min(shape_y, other_y + shape.m_height));
            return x_diff * x_diff + y_diff * y_diff <= m_shape.m_radius * m_shape.m_radius;
        }
        if (shape.m_type == Shape::Type::CIRCLE)
        {
            const float dist = m_shape.m_radius + shape.m_radius;
            const float x_diff = other_x - shape_x;
            const float y_diff = other_y - shape_y;
            return x_diff * x_diff + y_diff * y_diff <= dist * dist;
        }
    }
    return false;
}

CollisionComponent* CollisionComponent::LoadFromJson(const json& data, Ref<Entity> entity)
{
    // TODO: More error checking
    Shape shape = Shape::LoadFromJson(data["shape"]);
    
    float offsetX = 0.f, offsetY = 0.f;
    if (data.find("offsetX") != data.end() && data["offsetX"].is_number_float())
    {
        offsetX = data["offsetX"];
    }
    if (data.find("offsetY") != data.end() && data["offsetY"].is_number_float())
    {
        offsetY = data["offsetY"];
    }
    shape.m_offsetX = offsetX;
    shape.m_offsetY = offsetY;

    return new CollisionComponent(entity, shape);
}