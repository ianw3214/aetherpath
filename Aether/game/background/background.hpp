#pragma once
#include "oasis.h"

#include <string>

class Background
{
public:
    Background();

    void Render() const;
private:
    // TODO: Dynamically set based on map size?
    const int num_stars = 100;

    void DrawStars() const;

    struct StarInfo
    {
        float x;
        float y;
        float scale;
    };
    std::vector<StarInfo> m_stars;

    // Cached sprites
    Oasis::Sprite m_backgroundSprite;
};