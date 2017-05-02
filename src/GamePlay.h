#ifndef CAMERA_H
#define CAMERA_H

#include "Mobile.h"
#include "World.h"
#include "Common.h"
#include "SDL.h"
#include "Loop.h"
#include "IA.h"
using namespace std;
/** @brief Gère l'ensemble des éléments de jeu.
*/
class GamePlay : public Loop
{
private:
    int fade;
    void drawMapGround();
    void drawMapBackground();
    void drawBodies();
    void initMapGround();
    void initMapBackground();
    void initBodies();
    void catchEvents();
    double updateOffset();
    World* world;

    vector<IA*> ias;
    SDL_Surface* life_bar;
    vector<SDL_Surface*> bodies;
    vector<SDL_Surface*> mapGroundSurface;
    vector<SDL_Surface*> mapBackgroundSurface;
    vector<string> hashTags;

    double OffsetX;
    bool OffsetMove;
    double LastOffsetX;
    bool validBodies();

public:

    GamePlay(SDL* sdl, vector<IA*> _ias);
    virtual ~GamePlay();
    virtual void start();
    void setWorld(World* new_world);
};

#endif
