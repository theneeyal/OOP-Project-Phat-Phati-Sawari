#include "bullet.hpp"

Bullet::Bullet() {}

Bullet::Bullet(SDL_Texture *tex, int x, int y)
{
    flag = 0;
    assets = tex;
    src = {1691, 40, 99, 232};
    mover = {x, y, 15, 30};
}

void Bullet::updatePos()
{
    if (flag) // increases the size of the bullets and moves it downward on the frame.
    {
        mover.w++;
        mover.h++;
        flag = 0;
    }
    else
    {
        flag = 1;
    }
    mover.y += 20;
}

Bullet::~Bullet() {}