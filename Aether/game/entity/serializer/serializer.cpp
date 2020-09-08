#include "serializer.hpp"

EntitySerializer * EntitySerializer::s_instance = nullptr;

Ref<EntitySerializer> EntitySerializer::GetInstance()
{
    if (!s_instance) s_instance = new EntitySerializer();
    return s_instance;
}

EntitySerializer::EntitySerializer()
{
    // TODO: Initialize stuff
}