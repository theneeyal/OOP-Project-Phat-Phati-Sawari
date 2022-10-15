#include "money.hpp"

money::money(){};

money::money(SDL_Texture *tex)
{
    s = 10;
    int temp = rand() % 100;
    if (temp < 5) //five percent probabilty for it to be heart
    {
        type = 2;
    }
    else if (temp < 10)//five percent probabilty for it to be diamond
    {
        type = 1;
    }
    else
    {
        type = 0; //90 probability for a coin.
    }
    setMoney(); //set source coordinates according to the file chosen
    lane = rand() % 4; //picking lane randomly
    setPosition(); //setting position according to the lane, this is called from parent class RoadObj
    assets = tex;
}

money::~money()
{
}
money:: money(SDL_Texture * tex, bool val, int x){ //overload contrcutor for creating stationary object of heart, to dislay health on the screen,
    src = {118, 1033, 114, 103};
    mover = {x, 190, 40, 40};
    assets = tex;
    stationary = true;
}
void money::setMoney() //setting the src coordinates according to type chosen.
{
    switch (type)
    {
    case 0:
        //coin
        src = {450, 45, 300, 250};
        break;
    case 1:
        //diamond
        src = {237, 74, 178, 142};
        break;
    case 2:
        //heart
        src = {118, 1033, 114, 103};
        break;
    }
}
