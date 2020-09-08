#pragma once
#include "oasis.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class EntitySerializer
{
public:
    Ref<EntitySerializer> GetInstance();
private:
    EntitySerializer();
    static EntitySerializer * s_instance;
};