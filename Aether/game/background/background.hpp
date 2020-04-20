#pragma once
#include "oasis.h"

#include <vector>

////////////////////////////////////////////////////////////////////////////////////////
constexpr float star_sprite_width = 10.f;
constexpr float star_sprite_height = 10.f;
constexpr float star_scale_ratio = 0.5f;
struct Star
{
    float x;
    float y;
    float parallax;

    static constexpr float StarDensityPerSquareThousand = 1.5f;
};

////////////////////////////////////////////////////////////////////////////////////////
class Background : public Oasis::GameStateLayer
{
public:
    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    Oasis::Sprite m_starSprite;

    std::vector<Star> m_stars;
};