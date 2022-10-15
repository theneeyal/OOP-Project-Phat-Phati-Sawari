#pragma once
#include "unit.hpp"

class Enemy : public Unit
{
    int lane;
    bool change;
    bool dir;
    int health;
    int type;
public:
    Enemy();
    Enemy(SDL_Texture *);
    void updatePos();
    void decHealth(int);
    int getHealth();
    void setHealth();
    void setType(int);
    int getType();
    ~Enemy();

};
