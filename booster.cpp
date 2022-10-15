#include "booster.hpp"

booster::booster(){};

booster::booster(int val, SDL_Texture *tex)
{// this constructor is used when a stationary booster is created to be displayed on screen when a booster is active
    type = val - 1;
    stationary = true;
    assets = tex;
    switch (val)
    {
    case 1:
    {
        src = {968, 2831, 309, 309};
        mover = {20, 240, 50, 50};
        //missile
        break;
    }
    case 2:
    {
        src = {553, 2798, 297, 396};
        mover = {80, 240, 50, 50};
        //highscore
        break;
    }
    case 3:
    {
        src = {108, 2820, 332, 313};
        mover = {140, 240, 50, 50};
        //shield
        break;
    }
    case 4:
    {
        src = {1380, 2792, 297, 396};
        mover = {200, 240, 50, 50};
        //coin
        break;
    }
    }
}

booster::booster(SDL_Texture *tex)
{// normal booster is constructed
    s = 20;
    if (rand() % 100 < 20)
    {
        //20% chance of missile-booster to appear
        type = 0;
    }
    else
    {
        type = rand() % 3 + 1;
    }
    setBooster();
    lane = rand() % 4;
    setPosition();
    assets = tex;
}

booster::~booster()
{
}

void booster::setBooster()
{
    switch (type)
    {
    case 0:
        //missile-booster
        src = {968, 2831, 309, 309};
        break;
    case 1:
        //blue-booster
        src = {553, 2798, 297, 396};
        break;
    case 2:
        //shield
        src = {108, 2820, 332, 313};
        break;
    case 3:
        //coin-booster
        src = {1380, 2792, 297, 396};
        break;
    }
}
