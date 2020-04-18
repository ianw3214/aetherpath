#pragma once
#include "oasis.h"

////////////////////////////////////////////////////////////////////////////////////////
class UILayer : public Oasis::GameStateLayer
{
public:
    // UI enums
    enum class ResourceIcon
    {
        OXYGEN,
        FUEL,
        POPULATION,
        METAL
    };
public:
    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    Oasis::Sprite m_cursor;
    
    // Icons
    // TODO: Make these sprites more consistent (use fuel as reference)
    Oasis::Sprite m_oxygenIcon;
    Oasis::Sprite m_fuelIcon;
    Oasis::Sprite m_populationIcon;
    Oasis::Sprite m_metalIcon;
private:
    // Drawing helper functions
    void AddPadding(float padding, float& curr_y);
    void DrawResource(ResourceIcon resource, int numResource, float& curr_y);
};