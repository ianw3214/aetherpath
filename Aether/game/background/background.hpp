#pragma once
#include "oasis.h"

#include <string>

class Background
{
public:
    Background();

    void Render() const;
private:
    const std::string path = "res/sprites/background_backup.png";

    void DrawStars() const;
};