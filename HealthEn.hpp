#pragma once
#include "Unit.hpp"

class HealthEn: public Unit //health bar to display the remaining health of the enemy
{
    public:
    HealthEn();
    HealthEn(SDL_Texture*);
    void setSrc(int);
    ~HealthEn();
};