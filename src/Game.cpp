#include "Game.h"

Game::Game() : Loop(NULL)
{
    Common::_Game++;
}
void Game::initSdl()
{
    sdl = new SDL();
    sdl->init();
}

void Game::initMap()
{

    vector<Point> ground_map;
    int* y = new int[23];
    y[0] = 100;
    y[1] = 98;
    y[2] = 95;
    y[3] = 90;
    y[4] = 95;
    y[5] = 80;
    y[6] = 85;
    y[7] = 94;
    y[8] = 100;
    y[9] = 92;
    y[10] = 90;
    y[11] = 88;
    y[12] = 78;
    y[13] = 70;
    y[14] = 77;
    y[15] = 68;
    y[16] = 50;
    y[17] = 55;
    y[18] = 70;
    y[19] = 90;
    y[20] = 100;
    y[21] = 98;
    y[22] = 104;

    ground_map.push_back(Point(0, 0));
    int max = 40000;
    for(int x = MAP_X_STEP; x <= max; x += MAP_X_STEP) {
        ground_map.push_back(Point(x, y[x / MAP_X_STEP % 23]));
    }
    ground_map.push_back(Point(max + MAP_X_STEP, 0));

    delete y;
    map = new Map();

    map->setBackGround("./data/background.png");
    map->setGround(ground_map);
}
void Game::initPlayer()
{
    main_player = new Player();
    main_player->buyShape(Common::getObjectOfType(BODYWORK));
    main_player->buyShape(Common::getObjectOfType(WHEEL));
    main_player->buyShape(Common::getObjectOfType(WEAPON));
}

void Game::initWorld()
{
    world = new World();
    world->createPlayer(main_player, true);
		
    for(auto* ia : ia_players){
        world->createPlayer(ia->getIA(), false);
    }

    world->createMap(map);
    world->setGravity(Point(0, -9.8));
}

bool Game::startMenu()
{
    menu->start();
    return !menu->getQuit();
}

bool Game::startGamePlay()
{
    game_play->setWorld(world);
    game_play->start();
    return !game_play->getQuit();
}

void Game::initGamePlay()
{
    game_play = new GamePlay(sdl, ia_players);
}
void Game::initMenu()
{
    menu = new Menu(sdl, main_player);
}
void Game::initSplash()
{
    splash = new Splash(sdl);
}

void Game::startSplash()
{
    splash->start();
}

void Game::initIa()
{	
	for(int i = 0; i < NB_IA; i++){
		IA *ia = new IA("IA-"+to_string(i), main_player);
		
		ia->defineMobile(
			Point(main_player->getMobile()->getPosition().x + MAP_X_STEP * ((i+1)*10), 200),
			((i == NB_IA-1)? -1 : rand()%2)
		);
		
		//ia->afficheDonnees();
		ia_players.push_back(ia);
	}

}
void Game::resetPlayer(){
	main_player->live();
}

void Game::start()
{
    Loop::start();

    initSdl();
    Common::init();
    initSplash();
    startSplash();

    initPlayer();
    initMenu();
    initMap();

    while(loop) {
        loop = startMenu();
        if(!loop) {
            break;
        }
        initIa();
        initWorld();
        resetPlayer();
        initGamePlay();
        loop = startGamePlay();
        delete world;
        delete game_play;
        
        for(auto * ia : ia_players)
        		delete ia;
        ia_players.clear();

        if(!loop) {
            break;
        }
    }
}

Game::~Game()
{
    Common::_Game--;

    delete sdl;
    Common::destroy();
    // delete game_play;
    delete menu;
    delete map;
    delete main_player;
    delete splash;
}
