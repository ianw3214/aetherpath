#pragma once
#include "oasis.h"

#include <string>

class Background
{
public:
    Background();

    void Render() const;
private:
    // TODO: These are both temporary
    const std::string path = "res/sprites/background_backup.png";
    const int num_stars = 100;

    void DrawStars() const;

    struct StarInfo
    {
        float x;
        float y;
        float scale;
    };
    std::vector<StarInfo> m_stars;
};