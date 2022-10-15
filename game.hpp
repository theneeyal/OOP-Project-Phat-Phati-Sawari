#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>
#include "Streetlight.hpp"
#include "vehicle.hpp"
#include "Patch.hpp"
#include "Bullet.hpp"
#include "booster.hpp"
#include "money.hpp"
#include "Fire.hpp"
#include "bike.hpp"
#include "Enemy.hpp"
#include "HealthEn.hpp"
#include "Tree.hpp"
using namespace std;

class Game
{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 700;

    //vectors of pointers (dynamic objects) pf all objects to be rendered on the screen.
    vector<vehicle *> vec; 
    vector<Streetlight *> strl; 
    vector<Patch *> pt;
    vector<Bullet *> bt;
    vector<booster *> boost;
    vector<money *> mon;
    vector<Fire *> fir;
    vector<booster *> dis_ro;
    vector<money *> dis_health;
    vector<Tree *> trees;
    bike b;
    bool isEnemy = false;
    int coins = 0;
    int diamonds = 0;
    bool gameover = false;
    int revived = 0;
    bool quit = false;
    int screen = 2;
    //Enemy en;
    SDL_Event e;

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The window renderer
    SDL_Renderer *gRenderer = NULL;

    //Current displayed texture
    SDL_Texture *gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture *assets = NULL;

    //initializing all sounds
    Mix_Music *music = NULL;
    Mix_Chunk *chcoin = NULL;
    Mix_Chunk *chdiamond = NULL;
    Mix_Chunk *chcoinB = NULL;
    Mix_Chunk *chhighScB = NULL;
    Mix_Chunk *chshieldOn = NULL;
    Mix_Chunk *chshieldOff = NULL;
    Mix_Chunk *chstart = NULL;
    Mix_Chunk *chheart = NULL;
    Mix_Chunk *chShoot = NULL;
    Mix_Chunk *chBombDrop = NULL;
    Mix_Chunk *chError = NULL;
    Mix_Chunk *chkhailTamam = NULL;
    Mix_Chunk *chDestroyed = NULL;
    Mix_Chunk *chShootCol = NULL;
    Mix_Chunk *chMissileB = NULL;

    //initializing font and setting text color
    TTF_Font *font = NULL;
    SDL_Color textColor = {14, 206, 69};

    //initialzing surface, texture and textrects to display varying numbers
    SDL_Surface *mhscore_v = NULL, *mscore_v = NULL, *mcoins = NULL, *mdiamonds = NULL;
    SDL_Texture *thscore_v = NULL, *tscore_v = NULL, *thcoins = NULL, *thdiamonds = NULL;
    SDL_Rect textrecth_v, textrects_v, coinsrect, diamondsrect;

    int ro = 0;
    int highscore = 0, score = 0;
    bool music_ = false;
    int xMouse = 0, yMouse = 0;
    int subscreen = 0;

public:
    bool init();
    bool loadMedia();
    void close();
    void populate_bg();
    void create_ro();
    void enemy_fire(int, int);
    template <typename V>
    void deleteObjects(vector<V *> &);
    template <typename X>
    void drawObjects(vector<X *> &);
    template <typename X>
    void screenClear(vector<X *> &);
    SDL_Texture *loadTexture(std::string path);
    void bike_collision();
    void vehicle_collision();
    void enemy_collision(Enemy *);
    void check_money(money *);
    void check_booster(booster *);
    void displayScore();
    void displayMoney();
    void run();
    void loadDisplay_ro();
    void draw_ro();
    void draw_healthE(Enemy *, HealthEn *);
    void loadNew(Enemy *);
    void treeLoad();
    void screen0(Enemy *, HealthEn *);
    void screen1();
    void screen2(Enemy *);
    void screen3();
    void subscreen1();
    void subscreen2();
};
