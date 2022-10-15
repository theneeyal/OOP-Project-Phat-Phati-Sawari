#include "Fire.hpp"

Fire::Fire() {}

Fire::Fire(SDL_Texture *tex, int x, int y, bool iM)
{
    assets = tex; //sets the src coordinates and size of object on screen according to the current state of what will the biker fire next, missile if he has the booster, and regular fire otherwise.
    if (iM)
    {
        src = {2083, 22, 90, 332};
        mover = {x, y, 25, 60};
    }
    else
    {
        src = {1934, 52, 26, 207};
        mover = {x, y, 10, 30};
    }

    
    isMissile = iM;
}

void Fire::updatePos() //mover upwards in every frame
{
    mover.y -= 20;
}

bool Fire::check_collision(Unit *un) //special collision of fire with enemy planes to avoid the wings of enemies.
{
    bool A, C, D;
    A = (mover.x >= ((un)->getX() + 100)) && (mover.x <= ((un)->getX() + (un)->getW() - 100));
    C = (((un)->getY() + (un)->getH()) >= mover.y);
    return (A && C);
}

bool Fire::isMissile_(){ //getter function for isMissile
    return isMissile;
}
Fire::~Fire(){};