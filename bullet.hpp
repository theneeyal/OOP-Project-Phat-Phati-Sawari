#pragma once
#include "Unit.hpp"

class Bullet : public Unit
{
    bool flag;

public:
    Bullet();
    Bullet(SDL_Texture *, int, int);
    void updatePos();
    ~Bullet();
};