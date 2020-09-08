#pragma once
#include "oasis.h"

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "game/entity/entity.hpp"

class EntitySerializer
{
private:
    EntitySerializer();
    static EntitySerializer * s_instance;
public:
    static Ref<EntitySerializer> GetInstance();

    // Actual class functions
    Entity* GetEntity(const std::string& path);
};