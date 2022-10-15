#pragma once
#include "Unit.hpp"

class Fire : public Unit
{
    bool isMissile;
public:
    Fire();
    Fire(SDL_Texture*,int, int, bool);
    void updatePos();
    bool check_collision(Unit *);
    bool isMissile_();
    ~Fire();
};