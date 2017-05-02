#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Splash.h"
#include "Player.h"
#include "Map.h"
#include "World.h"
#include "GamePlay.h"
#include "Menu.h"
#include "IA.h"

/** @breif Cette classe permet de lancer une partie de jeu complète. Elle initialise tous les éléménts du jeu. 
 */
class Game : public Loop
{

private:
    SDL* sdl;
    Map* map;
    GamePlay* game_play;
    Menu* menu;
    Player* main_player;
    Splash* splash;
    vector<IA*> ia_players;
    World* world;
    void initSdl();
    void initMap();
    void initGamePlay();
    void initMenu();
    void initSplash();
    void initPlayer();
    void initWorld();
    bool startMenu();
    bool startGamePlay();
    void initIa();
    void startSplash();
    void resetPlayer();

public:
    Game();
    virtual ~Game();
    virtual void start();

};

#endif // GAME_H
