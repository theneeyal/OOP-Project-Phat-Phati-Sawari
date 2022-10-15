#include "HealthEn.hpp"

HealthEn::HealthEn()
{
}

HealthEn::HealthEn(SDL_Texture *tex)
{
    assets = tex;
    src = {111, 3833, 325, 22};// sets src initially to the full health bar in the assets.
    mover = {800, 40, 150, 20}; 
}

void HealthEn::setSrc(int val)
{
    switch (val) //choosing correct src coordinates from based on current health of enemy.
    { 
    case 1:
    {
        src = {111, 3833, 325, 22};
        break;
    }
    case 2:
    {
        src = {111, 3856, 325, 22};
        break;
    }
    case 3:
    {
        src = {111, 3885, 325, 22};
        break;
    }
    case 4:
    {
        src = {111, 3911, 325, 22};
        break;
    }
    case 5:
    {
        src = {111, 3939, 325, 22};
        break;
    }
    case 6:
    {
        src = {111, 3968, 325, 22};
        break;
    }
    case 7:
    {
        src = {111, 3999, 325, 22};
        break;
    }
    }
}

HealthEn::~HealthEn()
{
}
