#include "serializer.hpp"

#include <fstream>

EntitySerializer * EntitySerializer::s_instance = nullptr;

EntitySerializer::EntitySerializer()
{
    // TODO: Initialize stuff
}

Ref<EntitySerializer> EntitySerializer::GetInstance()
{
    if (!s_instance) s_instance = new EntitySerializer();
    return s_instance;
}

Entity* EntitySerializer::GetEntity(const std::string& path)
{
    std::ifstream raw_data(path);
    json data;
    raw_data >> data;

    std::string name;
    if (data.find("name") != data.end() && data["name"].is_string())
    {
        name = data["name"];
        Oasis::Console::AddLog(name.c_str());
    }

    return nullptr;
}