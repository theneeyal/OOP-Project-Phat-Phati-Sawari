#pragma once
#include "SDL.h"
#include "unit.hpp"
#include "RoadObj.hpp"
#include <iostream>

class booster : public RoadObj
{
    bool collidedY;

public:
    booster();
    booster(SDL_Texture *);
    booster(int, SDL_Texture *);
    void setBooster();
    ~booster();
};
