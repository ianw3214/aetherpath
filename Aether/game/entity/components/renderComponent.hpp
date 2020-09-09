#pragma once
#include "oasis.h"

#include "game/entity/component.hpp"

#include <string>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class RenderComponent : public Component
{
public:
    RenderComponent(Ref<Entity> entity, const std::string& path, float width = 0.f, float height = 0.f);
    virtual void Update(float delta) override;
private:
    float m_width;
    float m_height;
    Oasis::Sprite m_sprite;
public:
    // Serialization
    static std::string GetID() { return "render"; }
    static RenderComponent* LoadFromJson(const json& data, Ref<Entity> entity);
};