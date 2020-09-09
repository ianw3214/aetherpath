#include "serializer.hpp"

#include <fstream>

#include "game/entity/components/renderComponent.hpp"

EntitySerializer * EntitySerializer::s_instance = nullptr;

EntitySerializer::EntitySerializer()
{
    RegisterComponents();
}

void EntitySerializer::RegisterComponents()
{
    s_componentMap[RenderComponent::GetID()] = RenderComponent::LoadFromJson;
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

    Entity * result = new Entity();

    std::string name;
    if (data.find("name") != data.end() && data["name"].is_string())
    {
        name = data["name"];
        // TODO: Make name relevant to entities
        // Might want to put this in a data component or something of the sort
        // Or we could just put it in the actual base entity class
    }

    if (data.find("components") != data.end() && data["components"].is_array())
    {
        const json& components = data["components"];
        for (const json& component : components)
        {
            std::string id;
            if (component.find("id") != component.end() && component["id"].is_string())
            {
                id = component["id"];
            }
            else
            {
                continue;
            }
            if (s_componentMap.find(id) != s_componentMap.end())
            {
                if (component.find("data") != component.end() && component["data"].is_object())
                {
                    Component * comp = s_componentMap[id](component["data"]);   
                }
                else
                {
                    json empty;
                    Component * comp = s_componentMap[id](empty);
                }
            }
        }
    }

    return nullptr;
}