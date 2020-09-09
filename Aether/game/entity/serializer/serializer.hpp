#pragma once
#include "oasis.h"

#include <string>
#include <unordered_map>
#include <functional>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "game/entity/entity.hpp"
#include "game/entity/component.hpp"

class EntitySerializer
{
private:
    EntitySerializer();
    static EntitySerializer * s_instance;
private:
    // Mapping of IDs to components
    std::unordered_map<std::string, std::function<Component*(const json&)>> s_componentMap;
    void RegisterComponents();
public:
    static Ref<EntitySerializer> GetInstance();

    // Actual class functions
    Entity* GetEntity(const std::string& path);
};