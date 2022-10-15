#pragma once
#include "SDL.h"
#include "Unit.hpp"

class bike : public Unit
{
    bool moveL;
    bool moveR;
    int moveFrame;
    int health;
    bool missileNext;
    bool doubleCoin;
    int doubleCoinDur;
    bool doubleHigh;
    int doubleHighDur;
    bool shielded;
    int shieldedDur;
    SDL_Rect srcS;
    SDL_Rect moverS;
    bool isDead;

public:
    bike();
    void setAssets(SDL_Texture *);
    //void draw(SDL_Renderer *);
    void updatePos();
    void moveLeft();
    void moveRight();
    void decHealth();
    void incHealth();
    int getHealth();
    void setHealth(int);
    void setMissile();
    bool getMissile();
    void missileOff();
    void setCoinD();
    bool getCoinD();
    void durCoin();
    void setHighD();
    bool getHighD();
    void durHigh();
    void setShielded();
    bool getShielded();
    void durShielded();
    void shieldOff();
    void draw(SDL_Renderer *);
    void nullBoosters();
    void dead();
    void unDead();
};