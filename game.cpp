#include "game.hpp"
#include "bike.hpp"
#include "Streetlight.hpp"
#include "Enemy.hpp"
#include "HealthEn.hpp"
#include "Tree.hpp"
bool Game::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("پھٹ پھٹی سواری", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                if (TTF_Init() == -1)
                {
                    return false;
                }

                //Initialize SDL_mixer
                if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
                {
                    return false;
                }
            }
        }
    }

    return success;
}

bool Game::loadMedia()

{
    //Loading success flag
    bool success = true;

    assets = loadTexture("assets.png");
    gTexture = loadTexture("screen2_mainmenu.png");

    //Opening the font and musics
    font = TTF_OpenFont("cooper.ttf", 30);
    music = Mix_LoadMUS("bike_.wav");
    chcoin = Mix_LoadWAV("coin.wav");
    chcoinB = Mix_LoadWAV("coin-booster.wav");
    chdiamond = Mix_LoadWAV("diamond.wav");
    chheart = Mix_LoadWAV("health.wav");
    chhighScB = Mix_LoadWAV("highscore.wav");
    chshieldOn = Mix_LoadWAV("shield-on2.wav");
    chshieldOff = Mix_LoadWAV("shield-off.wav");
    chShoot = Mix_LoadWAV("shoot.wav");
    chstart = Mix_LoadWAV("start.wav");
    chBombDrop = Mix_LoadWAV("bomb-drop.wav");
    chkhailTamam = Mix_LoadWAV("khailTamam.wav");
    chError = Mix_LoadWAV("error.wav");
    chMissileB = Mix_LoadWAV("missileB.wav");
    chShootCol = Mix_LoadWAV("shootCol.wav");
    chDestroyed = Mix_LoadWAV("destroyed.wav");

    //setting display rects of text at position required
    textrecth_v = {185, 44, 50, 20};
    textrects_v = {170, 96, 50, 20};
    coinsrect = {252, 150, 20, 20};
    diamondsrect = {105, 150, 20, 20};

    if (assets == NULL || gTexture == NULL)
    {
        printf("Unable to run due to error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void Game::close()
{
    //Free loaded images
    SDL_DestroyTexture(assets);
    assets = NULL;
    SDL_DestroyTexture(gTexture);

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //clearing all vectors of dynamic pointers
    screenClear(vec);
    screenClear(bt);
    screenClear(fir);
    screenClear(pt);
    screenClear(strl);
    screenClear(boost);
    screenClear(mon);
    screenClear(dis_ro);
    screenClear(dis_health);
    screenClear(trees);

    //closing font
    TTF_CloseFont(font);

    //freeing memory of all sounds loaded
    Mix_FreeMusic(music);
    Mix_FreeChunk(chstart);
    Mix_FreeChunk(chShoot);
    Mix_FreeChunk(chshieldOn);
    Mix_FreeChunk(chshieldOff);
    Mix_FreeChunk(chhighScB);
    Mix_FreeChunk(chheart);
    Mix_FreeChunk(chBombDrop);
    Mix_FreeChunk(chcoin);
    Mix_FreeChunk(chcoinB);
    Mix_FreeChunk(chdiamond);
    Mix_FreeChunk(chError);
    Mix_FreeChunk(chkhailTamam);
    Mix_FreeChunk(chDestroyed);
    Mix_FreeChunk(chMissileB);
    Mix_FreeChunk(chShootCol);

    //setting all sound pointers to null
    music = NULL;
    chshieldOff = NULL;
    chshieldOn = NULL;
    chShoot = NULL;
    chstart = NULL;
    chcoinB = NULL;
    chcoin = NULL;
    chdiamond = NULL;
    chheart = NULL;
    chhighScB = NULL;
    chBombDrop = NULL;
    chkhailTamam = NULL;
    chError = NULL;
    chShootCol = NULL;
    chDestroyed = NULL;
    chMissileB = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *Game::loadTexture(std::string path)
{
    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}
void Game::populate_bg()
{ //initializes pointers of patches and streetlights on road
    for (int j = 0; j < 6; j++)
    {
        Patch *p = new Patch(assets, j);
        pt.push_back(p);
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Streetlight *sl = new Streetlight(assets, i, j);
            strl.push_back(sl);
        }
    }
}

void Game::create_ro()
{ //randomly creates vehicle, booster or money and adds it to its vector
    int r = rand() % 100;
    if (r <= 10)
    {
        switch (r)
        {
        case (0):
        case (1):
        case (2):
        case (3):
        {
            vehicle *v = new vehicle(assets);
            vec.push_back(v);
            ro = 6;
            break;
        }
        case (4):
        case (5):
        case (6):
        {
            booster *bs = new booster(assets);
            boost.push_back(bs);
            ro = 4;
            break;
        }
        case (7):
        case (8):
        case (9):
        {
            money *m = new money(assets);
            mon.push_back(m);
            ro = 2;
            break;
        }
        }
    }
}

void Game::enemy_fire(int x, int y)
{ //creates bomb thrown by enemy at the place where the enemy is with 1% probability
    if (rand() % 100 <= 1)
    {
        Bullet *b = new Bullet(assets, x, y);
        bt.push_back(b);
    }
}

void Game::treeLoad()
{ // creates a tree with 20% probability
    if (rand() % 100 <= 20)
    {
        Tree *t = new Tree(assets);
        trees.push_back(t);
    }
}
template <typename X>
void Game::drawObjects(vector<X *> &vec)
{ // template function, to draw all road objects
    for (auto i = vec.begin(); i != vec.end(); i++)
    {
        (*i)->draw(gRenderer);
    }
}

template <typename V>
void Game::deleteObjects(vector<V *> &vec)
{ // template function, to delete all road objects
    auto i = vec.begin();
    while (i != vec.end())
    {
        if (((*i)->getY() >= 650) || ((*i)->getY() <= 5))
        {
            delete (*i);
            vec.erase(i);
        }
        else
        {
            ++i;
        }
    }
}
void Game::check_money(money *m)
{ // checks the type of money the biker has collided with from getType()
    int money_type = m->getType();
    switch (money_type)
    {
    case (0):
        //coin
        {
            Mix_PlayChannel(-1, chcoin, 0); // sound of coin generated
            score += 50;                    // increases score by 50
            if (b.getCoinD())
            { // increases number of coins by double if double coin booster is on
                coins += 2;
                //b.durCoin();
            }
            else
            {
                coins++;
            }
            break;
        }
    case (1):
        //diamond
        Mix_PlayChannel(-1, chdiamond, 0); // sound of diamond collecting generated
        diamonds++;
        break;
    case (2):
        //heart
        Mix_PlayChannel(-1, chheart, 0); // sound of heart generated
        b.incHealth();                   // increases health
        break;
    }
}
void Game::check_booster(booster *bo)
{ // checks type of booster the biker has collided with from getType()
    int booster_type = bo->getType();
    switch (booster_type)
    {
    case (0):
        //missile
        Mix_PlayChannel(-1, chMissileB, 0); // missile booster sound generated
        b.setMissile();                     // sets missile booster true
        break;
    case (1):
        //score
        Mix_PlayChannel(-1, chhighScB, 0); // double highscore booster sound generated
        b.setHighD();                      // sets double highscore true

        break;
    case (2):
        //shield
        Mix_PlayChannel(-1, chshieldOn, 0); // shield-on sound generated
        b.setShielded();                    // sets shielded true
        break;
    case (3):
        //coin
        Mix_PlayChannel(-1, chcoinB, 0); // coin booster sound generated
        b.setCoinD();                    // sets double coin true
        break;
    }
}
void Game::bike_collision()
{ // checks bikes collision with different objects with the help of operator over-loaded collision function
    for (auto i = vec.begin(); i != vec.end(); i++)
    { // checks collision of bike with vehicle
        if (b == (*(*i)))
        {
            b.setHealth(-1); // sets bike health to -1, whiche means game over
        }
    }
    for (auto i = boost.begin(); i != boost.end(); i++)
    { // checks collision of bike with booster
        if (b == (*(*i)))
        {
            (*i)->setY(700);
            check_booster((*i));
        }
    }
    for (auto i = bt.begin(); i != bt.end(); i++)
    { // checks collision of bike with bullet thrown by enemy
        if (b == (*(*i)))
        {
            (*i)->setY(700);
            if (!b.getShielded())
            {
                Mix_PlayChannel(-1, chBombDrop, 0); // bullet colliding with bike sound generated
                b.decHealth();                      // decreases health of biker
            }
            else
            {
                Mix_PlayChannel(-1, chshieldOff, 0); // shield-off sound generated
                b.shieldOff();                       // sets shieloff true
            }
        }
    }
    for (auto i = mon.begin(); i != mon.end(); i++)
    { // checks collision of bike with money
        if (b == (*(*i)))
        {
            (*i)->setY(700);
            check_money((*i)); // sends to check_mony to check type of money collided with
        }
    }
}

void Game::vehicle_collision()
{ // checks collision of bullet thrown by enemy with vehicle
    // not done in bike_collision since it was more precise when own logic applied
    auto i = bt.begin();
    while (i != bt.end())
    {
        auto j = vec.begin();
        while (j != vec.end())
        {
            if ((*(*j)) == (*(*i)) && !((*j)->getCollided())) // checks if vehicle and bullet have collided
            {
                (*j)->changeSrc();                  // changes vehicle src to an explosion
                Mix_PlayChannel(-1, chBombDrop, 0); // generates bomb drop sound
                (*j)->setCollided();
                (*i)->setY(5); // sets mover.y of bullet to 700 so that it gets removed from screen
                break;
            }
            ++j;
        }
        ++i;
    }
}

void Game::enemy_collision(Enemy *en)
{ // checks collision of enemy with the fire
    auto i = fir.begin();
    while (i != fir.end())
    {
        if ((*i)->check_collision(en))
        {
            Mix_PlayChannel(-1, chShootCol, 0); // sound of fire colliding with enemy generated
            (*i)->setY(-50);
            if ((*i)->isMissile_())
            { // checksif  missile and decreases health of enemy by 2
                en->decHealth(2);
            }
            else
            { // if normal fire then decreases health of enemy by 1
                en->decHealth(1);
            }
        }
        ++i;
    }
    if (en->getHealth() <= 0)
    {                                        // checks if enemy health has become 0
        Mix_PlayChannel(-1, chDestroyed, 0); // generates sound of enemy destroyed
        isEnemy = false;
    }
}

void Game::loadDisplay_ro()
{ // generates a vector of stationary road objects that are to be displayed on screen
    booster *ro_b;
    for (int i = 0; i < 4; i++)
    {
        ro_b = new booster(i + 1, assets);
        dis_ro.push_back(ro_b);
    }
    money *heart;
    for (int i = 0; i < 5; i++)
    {
        heart = new money(assets, true, 20 + 50 * i);
        dis_health.push_back(heart);
    }
}

void Game::draw_ro()
{ // draws the roadobjects onto the screen. Boosters are drawn by first checking which booster is active.
    for (auto i = dis_ro.begin(); i != dis_ro.end(); i++)
    {
        int ty = (*i)->getType(); // gets type of booster active
        bool draw_obj = false;
        switch (ty)
        {
        case 0:
        {
            //missile
            draw_obj = b.getMissile();
            break;
        }
        case 1:
        {
            //highscore
            draw_obj = b.getHighD();
            break;
        }
        case 2:
        {
            //shield
            draw_obj = b.getShielded();
            break;
        }
        case 3:
        {
            //coin
            draw_obj = b.getCoinD();
            break;
        }
        }
        if (draw_obj) // draws the booster which is active
        {
            (*i)->draw(gRenderer);
        }
    }
    int healthCheck = b.getHealth();
    for (auto i = dis_health.begin(); i != dis_health.end(); i++)
    {
        if (healthCheck != 0)
        {
            (*i)->draw(gRenderer); // draws heart on screen
            healthCheck--;
        }
    }
}

void Game::displayScore()
{ // displays score and highScore on screen
    if (screen == 0)
    { // Score and highScore are increased only on screen 0
        if (b.getHighD())
        { // if double coin booster is activated then score is increased by double
            score += 2;
        }
        else
        {
            score += 1;
        }

        if (score >= highscore)
        { // if score exceeds highscore then highscore also starts increasing
            highscore = score;
        }
    }
    // converting highscore and score to strings to display
    stringstream hs, sc;
    hs << highscore;
    sc << score;

    // creating a surface of highscore and score
    mhscore_v = TTF_RenderText_Solid(font, hs.str().c_str(), textColor);
    mscore_v = TTF_RenderText_Solid(font, sc.str().c_str(), textColor);

    // creating texture of the surface to make it display
    thscore_v = SDL_CreateTextureFromSurface(gRenderer, mhscore_v);
    tscore_v = SDL_CreateTextureFromSurface(gRenderer, mscore_v);

    // displaying score and highScore
    SDL_RenderCopy(gRenderer, thscore_v, NULL, &textrecth_v);
    SDL_RenderCopy(gRenderer, tscore_v, NULL, &textrects_v);
}

void Game::displayMoney()
{ // displaying number of coins and diamonds when collected

    // converting coins and diamonds to strings to display
    stringstream c, d;
    c << coins;
    d << diamonds;

    // creating a surface of coins and diamonds
    mcoins = TTF_RenderText_Solid(font, c.str().c_str(), textColor);
    mdiamonds = TTF_RenderText_Solid(font, d.str().c_str(), textColor);

    // creating texture of the surface to make it display
    thcoins = SDL_CreateTextureFromSurface(gRenderer, mcoins);
    thdiamonds = SDL_CreateTextureFromSurface(gRenderer, mdiamonds);

    // displaying coins and diamonds
    SDL_RenderCopy(gRenderer, thcoins, NULL, &coinsrect);
    SDL_RenderCopy(gRenderer, thdiamonds, NULL, &diamondsrect);
}

void Game::draw_healthE(Enemy *enemy, HealthEn *h_en)
{ // draws the enemy health by checking it using getHealth and then updating its src accordingly by using the val set by this function
    int temp = enemy->getHealth();
    int val = 0;
    if (temp >= 18)
    {
        val = 7;
    }
    else if (temp >= 15)
    {
        val = 6;
    }
    else if (temp >= 12)
    {
        val = 5;
    }
    else if (temp >= 9)
    {
        val = 4;
    }
    else if (temp >= 6)
    {
        val = 3;
    }
    else if (temp >= 3)
    {
        val = 2;
    }
    else
    {
        val = 1;
    }
    h_en->setSrc(val);
    h_en->draw(gRenderer);
}

template <typename X>
void Game::screenClear(vector<X *> &v1)
{ // used to traverse objects which are needed to be cleared from memory/screen when game ends/ new game is started. It makes use of the function delete objects.
    for (auto i = v1.begin(); i != v1.end(); i++)
    {
        (*i)->setY(750); //setting Y to 750 so that it can be deleted in the deleteobjects function
    }
    deleteObjects(v1);
}

void Game::loadNew(Enemy *en)
{ // function to set everything to 0 except highscore so that when game is restarted new game begins, with highscore of old game saved
    gameover = false;
    score = 0;
    coins = 0;
    diamonds = 0;
    screenClear(vec);
    screenClear(bt);
    screenClear(fir);
    screenClear(boost);
    screenClear(mon);
    screenClear(trees);
    b.setHealth(3);
    isEnemy = false;
    en->setHealth();
    b.nullBoosters();
    b.unDead();
}

void Game::screen0(Enemy *en, HealthEn *h_e)
{ // in-game screen

    //Mix_HaltMusic(); //Uncomment this to PAUSE background music
    if (!music_)
    { //plays background music
        Mix_PlayMusic(music, -1);
        Mix_Volume(1, (MIX_MAX_VOLUME) / 8);
        Mix_PlayChannel(-1, chstart, 0); //start countdown sound
        music_ = true;
    }

    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            std::cout << "quit" << std::endl;
            quit = true;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
        { // checks if left arrow key pressed
            b.moveLeft();
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
        { // checks if right arrow key pressed
            b.moveRight();
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
        { // checks if space bar pressed

            Fire *f = new Fire(assets, b.getX() + b.getW() / 2, b.getY(), b.getMissile()); // generates fire. If getmissile is true then missile is generated.
            fir.push_back(f);
            Mix_PlayChannel(-1, chShoot, 0); // shooting sound generated
            if (b.getMissile())
            {
                b.missileOff(); // sets missile booster off since its been generated now.
            }
        }

        if (score >= 150 && !isEnemy && rand() % 100 >= 80)
        { // creates a new enemy if old is destroyed
            isEnemy = true;
            en->setType(en->getType() + 1);
            en->setHealth();
            en->setY(-100);
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) //Checks if Escape key was pressed.
        {
            Mix_HaltMusic(); // halts background music
            music_ = false;
            gTexture = loadTexture("screen1_pausescreen.png"); //Loads the pause background screen
            screen = 1;
            cout << "Paused" << endl;
        }
    }
    SDL_RenderClear(gRenderer);                      //removes everything from renderer
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer

    drawObjects(strl); // draws streetlights
    drawObjects(pt);   // draws patches
    b.draw(gRenderer); // draws bike
    treeLoad();        // loads trees

    if (isEnemy)
    { // calls all functions of enemy if it is alive
        en->draw(gRenderer);
        enemy_fire(en->getX() + en->getW() / 2, en->getY() + en->getH());
        enemy_collision(en);
        draw_healthE(en, h_e);
    }
    if (revived > 0)
    {
        revived--;
    }
    if (ro == 0)
    { // creates road objects
        create_ro();
    }
    else
    {
        ro--;
    }

    drawObjects(trees); // draws trees
    drawObjects(vec);   // draws vehicles
    drawObjects(boost); // draws boosters
    drawObjects(mon);   // draws money and heart
    drawObjects(bt);    // draws bullet
    drawObjects(fir);   // draws fire

    draw_ro();       // draws road objects
    b.durCoin();     // updates time duration of coin booster
    b.durHigh();     // updates time duration of high score booster
    b.durShielded(); // updates time duration of shield booster

    if (revived == 0)
    {
        bike_collision();
    }

    vehicle_collision(); // checks if bullet and vehicle have collided

    // deletes all vector pointers
    deleteObjects(trees);
    deleteObjects(vec);
    deleteObjects(boost);
    deleteObjects(mon);
    deleteObjects(bt);
    deleteObjects(fir);

    // calls function to display score, highscore, diamonds and coins
    displayScore();
    displayMoney();

    SDL_RenderPresent(gRenderer); //displays the updated renderer
    if (gameover)
    {
        gTexture = loadTexture("screen3_gameover.png"); //Loads the pause background screen
        screen = 3;
    }
    if (b.getHealth() == -1)
    {
        Mix_PlayChannel(-1, chkhailTamam, 0); // generates gameover sound
        b.dead();                             // sets bike as dead
        gameover = true;
    }

    SDL_Delay(100); //causes sdl engine to delay for specified miliseconds
}
void Game::screen1()
{ // pause-screen
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        if (e.button.button == SDL_BUTTON_LEFT) //CHECK  MOUSE LEFT CLICK
        {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            if (xMouse > 380 && yMouse > 230 && xMouse < 666 && yMouse < 274)
            {
                gTexture = loadTexture("screen0_gameinscreen.png"); // loads in-game screen
                screen = 0;
                cout << "Unpaused" << endl;
            }
            if (xMouse > 380 && yMouse > 290 && xMouse < 666 && yMouse < 326)
            {
                gTexture = loadTexture("screen2_mainmenu.png"); // loads main-menu screen
                screen = 2;
            }
        }
        SDL_RenderPresent(gRenderer);
        SDL_Delay(100);
    }
}

void Game::screen2(Enemy *en)
{ // main-menu
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        SDL_RenderClear(gRenderer);                      //removes everything from renderer
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer

        if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) //CHECK LEFT CLICK
        {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            if (xMouse > 335 && yMouse > 288 && xMouse < 700 && yMouse < 335 && subscreen == 0) //Start Sawari
            {
                loadNew(en); // new game is being started, so all vectors/objects/variables are set to emptied/0/NULL
                gTexture = loadTexture("screen0_gameinscreen.png");
                screen = 0;
            }
            else if (xMouse > 335 && yMouse > 365 && xMouse < 700 && yMouse < 405 && subscreen == 0) //Instructions
            {
                subscreen = 1;
                gTexture = loadTexture("subscreen1_instructions.png"); // loads instructions screen
            }
            else if (xMouse > 335 && yMouse > 433 && xMouse < 700 && yMouse < 474 && subscreen == 0) //Credits
            {
                subscreen = 2;
                gTexture = loadTexture("subscreen2_credits.png"); // loads credits screen
            }
            else if (xMouse > 335 && yMouse > 506 && xMouse < 700 && yMouse < 550 && subscreen == 0) //Exit
            {
                cout << "exit" << endl;
                quit = true;
            }
            if (subscreen != 0)
            {
                if (subscreen == 1)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_GetMouseState(&xMouse, &yMouse);
                        if (xMouse > 370 && yMouse > 600 && xMouse < 690 && yMouse < 650)
                        {
                            subscreen = 0;
                            cout << "pressed" << endl;
                            gTexture = loadTexture("screen2_mainmenu.png"); //mainmenu
                            screen2(en);
                        }
                    }
                }
                if (subscreen == 2)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_GetMouseState(&xMouse, &yMouse);
                        if (xMouse > 288 && yMouse > 342 && xMouse < 758 && yMouse < 392)
                        {
                            subscreen = 0;
                            cout << "pressed" << endl;
                            gTexture = loadTexture("screen2_mainmenu.png"); //mainmenu
                            screen2(en);
                        }
                    }
                }
            }
        }

        SDL_RenderPresent(gRenderer);
        SDL_Delay(100); //100 miliseconds
    }
    SDL_RenderPresent(gRenderer);
}
void Game::screen3()
{ // game-over
    Mix_HaltMusic();
    music_ = false;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        SDL_RenderClear(gRenderer);                      //removes everything from renderer
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer
        if (e.button.button == SDL_BUTTON_LEFT)          //CHECK LEFT CLICK
        {

            SDL_GetMouseState(&xMouse, &yMouse);
            if (xMouse > 385 && yMouse > 278 && xMouse < 660 && yMouse < 307) // revive
            {
                if (diamonds >= 1)
                { // checks if atleast 1 diamond is present to revive
                    b.unDead();
                    gameover = false;
                    diamonds -= 1;
                    b.setHealth(1);
                    revived = 25;
                    gTexture = loadTexture("screen0_gameinscreen.png");
                    screen = 0;
                }
                else
                { // if diamond not present an error sound is generated
                    Mix_PlayChannel(-1, chError, 0);
                }
            }
            if (xMouse > 391 && yMouse > 325 && xMouse < 660 && yMouse < 355)
            {
                gTexture = loadTexture("screen2_mainmenu.png"); // loads main-menu screen
                screen = 2;
            }
        }

        if (screen == 3)
        { // displays highscore and score on screen
            displayMoney();
            displayScore();
        }

        SDL_RenderPresent(gRenderer);
        SDL_Delay(100);
    }
}

void Game::subscreen1()
{ // instructions

}
void Game::subscreen2()
{ // credits

}
void Game::run()
{
    SDL_RenderClear(gRenderer);

    b.setAssets(assets);  // sets bike assets
    Enemy en(assets);     // sets enemy asstes
    HealthEn h_e(assets); // sets enemy healths assets
    loadDisplay_ro();     // loads stationary road objects
    populate_bg();        // loads all background moving objects

    xMouse = 0, yMouse = 0;
    //While application is running
    while (!quit)
    {
        //Handle events on queue
        //screen 0 ingame
        //screen 1 pausescreen
        //screen 2 screen2_mainmenu
        //screen 3 gameover

        // calling respective function for screens
        if (screen == 0)
        {
            screen0(&en, &h_e);
        }

        else if (screen == 1)
        {
            screen1();
        }
        else if (screen == 2)
        {
            screen2(&en);
        }
        else if (screen == 3)
        {
            screen3();
        }
    }
}