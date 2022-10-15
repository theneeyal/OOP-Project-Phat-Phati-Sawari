#include "Enemy.hpp"

Enemy::Enemy() {}

Enemy::Enemy(SDL_Texture *tex)
{
    health = 20;
    dir = true;
    change = false;
    assets = tex;
    src = {812, 9, 785, 262};
    mover = {400, -100, 300, 120};
    type = 0;
}

void Enemy::updatePos()
{
    if (mover.y < 20) //moves down untill reaches a fix y position
    {
        mover.y++;
    }
    if (change) 
    {
        if (dir)
        {
            if (mover.x >= 300)
            {
                mover.x -= 2;
                if (rand() % 100 < 5) //randomly chnges directions
                {
                    dir = false;
                }
            }
            else
            {
                dir = false; //changes direction when reaches either end of the road
            }
        }
        else
        {
            if (mover.x < 600)
            {
                mover.x += 2;
                if (rand() % 100 < 5)
                {
                    dir = true;
                }
            }
            else
            {
                dir = true;
            }
        }
        if (rand() % 100 <= 2)
        {
            change = false; //randomly gets stationary and starts moving again
        }
    }
    else
    {
        if (rand() % 100 <= 20) // gets back to moving from being stationary randomly
        {
            change = true;
        }
    }
}

void Enemy::decHealth(int val) //decreases health when a fire collides with enemy
{
    health -= val;
}

int Enemy::getHealth() //gets the current health
{
    return health;
}

void Enemy::setHealth() //sets the health back to full when a new enemy appears
{
    health = 20;
}

void Enemy::setType(int val) //setting new src coordinates after one enemy is defeated and new has to appear
{
    if (val < 5)
    {
        type = val;
    }
    else
    {
        type = 1;
    }

    switch (val)
    {
    case 1:
    {
        src = {812, 9, 785, 262};
        break;
    }
    case 2:
    {
        src = {67, 4141, 903, 285};
        break;
    }
    case 3:
    {
        src = {1017, 4161, 783, 293};
        break;
    }
    case 4:
    {
        src = {1839, 4153, 901, 303};
        break;
    }
    }
}

int Enemy::getType() //returns current type(indication of src coordinates) of enemy 
{
    return type;
}
Enemy::~Enemy() {}