#pragma once
#include "SDL.h"
#include "unit.hpp"
#include "Roadobj.hpp"
#include <iostream>

class money: public RoadObj
{

public:
    money();
    money(SDL_Texture *);
    money(SDL_Texture *, bool, int);
    void setMoney();
    ~money();
};