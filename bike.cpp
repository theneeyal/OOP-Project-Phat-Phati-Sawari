#include "bike.hpp"

bike::bike()
{
    srcS = {976, 362, 445, 431}; //source and mover of shield
    moverS = {mover.x, mover.y, 100, 100};
    src = {72, 1185, 174, 301}; //source and mover of bike
    mover = {530, 570, 80, 100};
    moveL = false;
    moveR = false;
    missileNext = false; //all boosters false when creating new object of player.
    moveFrame = 0;
    health = 3; //default health is 3
    doubleCoin = false;
    doubleCoinDur = 0;
    isDead = false;
}

void bike::setAssets(SDL_Texture *tex)
{
    assets = tex;
}

void bike::moveLeft()
{
    if (mover.x > 250) //guard to prevent bike corssing the left side of the road
    {
        moveL = true;
    }
}
void bike::moveRight() //guard to prevent bike corssing the right side of the road
{
    if (mover.x < 670)
    {
        moveR = true;
    }
}

void ::bike::updatePos()
{
    if (!moveL && !moveR)
    {
        moveFrame = 0;
        src = {72, 1185, 174, 301}; // if no cursor is pressed, the straight bike reappears
        if (isDead)
        {
            src = {1336, 1276, 299, 136};
        }
    }
    else
    {
        if (moveL)
        {
            switch (moveFrame) //checking if cursor keys are pressed for consecutive timee then tilt and distance covered is increased proportional to the time the key is pressed for
            {
            case (-4):
            case (-3):
            case (-2):
            case (-1):
            case (0):
                mover.x -= 20;
                src = {350, 1540, 164, 299};
                break;
            case (1):
                mover.x -= 30;
                src = {582, 1537, 167, 299};
                break;
            case (2):
                mover.x -= 40;
                src = {815, 1538, 159, 299};
                break;
            case (3):
                mover.x -= 50;
                src = {1027, 1531, 155, 298};
                break;
            }
            if (moveFrame < 3)
            {
                moveFrame++;
            }
            moveL = false;
        }
        if (moveR)
        {
            switch (moveFrame)
            {
            case (4):
            case (3):
            case (2):
            case (1):
            case (0):
                mover.x += 20;
                src = {347, 1172, 175, 301};
                break;
            case (-1):
                mover.x += 30;
                src = {589, 1160, 178, 301};
                break;
            case (-2):
                mover.x += 40;
                src = {819, 1164, 183, 301};
                break;
            case (-3):
                mover.x += 50;
                src = {1034, 1173, 185, 301};
                break;
            }
            if (moveFrame > -3)
            {
                moveFrame--;
            }
            moveR = false;
        }
    }
    moverS.x = mover.x; //the shield follows the bike if bike is shielded
    moverS.y = mover.y;
}

void bike::decHealth() //getters and setters of booster states (true/ fase) and time durations follow
{
    health--;
}

void bike::incHealth()
{
    if (health <= 5)
    {
        health++;
    }
}

int bike::getHealth()
{
    return health;
}

void bike::setHealth(int val)
{
    health = val;
}
void bike::setMissile()
{
    missileNext = true;
}

bool bike::getMissile()
{
    return missileNext;
}

void bike::missileOff()
{
    missileNext = false;
}

void bike::setCoinD()
{
    doubleCoin = true;
    doubleCoinDur = 100;
}
bool bike::getCoinD()
{
    return doubleCoin;
}
void bike::durCoin()
{
    if (doubleCoinDur == 0)
    {
        doubleCoin = false;
    }
    else
    {
        doubleCoinDur--;
    }
}

void bike::setHighD()
{
    doubleHigh = true;
    doubleHighDur = 50;
}
bool bike::getHighD()
{
    return doubleHigh;
}
void bike::durHigh()
{
    if (doubleHighDur == 0)
    {
        doubleHigh = false;
    }
    else
    {
        doubleHighDur--;
    }
}
void bike::setShielded()
{
    shielded = true;
    shieldedDur = 50;
}
bool bike::getShielded()
{
    return shielded;
}
void bike::durShielded()
{
    if (shieldedDur == 0)
    {
        shielded = false;
    }
    else
    {
        shieldedDur--;
    }
}

void bike::shieldOff()
{
    shielded = false;
    shieldedDur = 0;
}

void bike::draw(SDL_Renderer *tex) //overriden draw function from unit class, Shield is to be drawn over the bike if bike is shielded
{
    updatePos();
    SDL_RenderCopy(tex, assets, &src, &mover);
    if (shielded)
    {
        SDL_RenderCopy(tex, assets, &srcS, &moverS);
    }
}

void bike::nullBoosters() //nullifying all boosters when the game is over, new game starts or the game is closed.
{
    missileNext = false;
    doubleCoin = false;
    doubleCoinDur = 0;
    doubleHigh = false;
    doubleHighDur = 0;
    shielded = false;
    shieldedDur = 0;
}

void bike::dead() 
{
    shielded = false;
    isDead = true;
    mover.w = 100;
    mover.h = 50;
}

void bike::unDead() //gives back coordinates to straight biker from the dead horizontal biker, used at revive and new game
{
    isDead = false;
    src = {72, 1185, 174, 301};
    mover.h = 100;
    mover.w = 80;
}