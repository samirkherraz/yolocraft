#include <iostream>
#include <SDL2/SDL.h>

#include "GamePlay.h"

using namespace std;

GamePlay::GamePlay(SDL* sdl, vector<IA*> _ias)
    : Loop(sdl)
{
    Common::_GamePlay++;
    world = NULL;
    ias = _ias;
    life_bar = NULL;
}

GamePlay::~GamePlay()
{
    Common::_GamePlay--;

    for(auto b : bodies) {
        SDL_FreeSurface(b);
    }
    for(auto b : mapGroundSurface) {
        SDL_FreeSurface(b);
    }
    for(auto b : mapBackgroundSurface) {
        SDL_FreeSurface(b);
    }

    bodies.clear();
    mapGroundSurface.clear();
    mapBackgroundSurface.clear();
    hashTags.clear();
    world = NULL;
}

void GamePlay::start()
{
    Loop::start();
    Common::playAudio(AUDIO_GAMEPLAY);

    initMapGround();
    bool fixFPS = false;
    initMapBackground();
    fade = FADEIN;
    while(loop) {

        for(auto ia : ias) {
            ia->step();
        }

        world->step(1.0 / FPS);

        int t1 = SDL_GetTicks();
        sdl->catchEvents();
        sdl->setOffsetX(updateOffset());
        sdl->clearBuffer();
        catchEvents();
        drawMapBackground();

        if(!validBodies())
            initBodies();
        drawBodies();
        drawMapGround();

        switch(fade) {
        case FADEINOUT:
            sdl->updateFadeOut();
            sdl->updateFadeIn();
            break;
        case FADEIN:
            sdl->updateFadeIn();
            break;

        case FADEOUT:
            sdl->updateFadeOut();
            break;
        case NOFADE:
            sdl->update();
            break;
        }

        int t2 = SDL_GetTicks();
        float32 diff = t2 - t1;
        float32 waitTime = 1000.0 / FPS - diff;

        if(waitTime <= 0) {
            FPS -= 2;
            fixFPS = true;
        } else {
            if(!fixFPS)
                FPS++;
            SDL_Delay(static_cast<Uint32>(waitTime));
        }

        fade = NOFADE;
    }

    Common::stopAudio();
}

void GamePlay::drawMapBackground()
{

    int surfaceNum = int(OffsetX / 2) / WINDOW_W;
    int lastMapBackgroundSurface = surfaceNum + 1;
    SDL_TextureDef mapPart;
    mapPart.surface = mapBackgroundSurface.at(surfaceNum % mapBackgroundSurface.size());
    mapPart.angle = 0;
    mapPart.pos = Point(OffsetX / 2 + WINDOW_W * surfaceNum, 0);
    sdl->registerTexture(mapPart);
    mapPart.surface = mapBackgroundSurface.at(lastMapBackgroundSurface % mapBackgroundSurface.size());
    mapPart.angle = 0;
    mapPart.pos = Point(OffsetX / 2 + WINDOW_W * lastMapBackgroundSurface, 0);
    sdl->registerTexture(mapPart);
}

void GamePlay::drawMapGround()
{

    unsigned int nbParts = 1 + (WINDOW_W / MAP_X_STEP);
    unsigned int surfaceNum = int(OffsetX) / (nbParts * MAP_X_STEP);
    unsigned int lastMapGroundSurface;

    int rest = int(OffsetX) % (nbParts * MAP_X_STEP);
    lastMapGroundSurface = surfaceNum + 1;

    bool drawCurrent = (surfaceNum < mapGroundSurface.size());
    bool drawNext = (rest != 0) && (lastMapGroundSurface < mapGroundSurface.size());
    SDL_TextureDef mapPart;

    if(drawCurrent) {
        mapPart.surface = mapGroundSurface.at(surfaceNum);
        mapPart.angle = 0;
        mapPart.pos = Point((nbParts * MAP_X_STEP) * surfaceNum, 0);
        sdl->registerTexture(mapPart);
    }
    if(drawNext) {
        mapPart.surface = mapGroundSurface.at(lastMapGroundSurface);
        mapPart.angle = 0;
        mapPart.pos = Point((nbParts * MAP_X_STEP) * lastMapGroundSurface, 0);
        sdl->registerTexture(mapPart);
    }
}

void GamePlay::initMapBackground()
{

    for(auto s : mapBackgroundSurface) {
        SDL_FreeSurface(s);
    }

    mapBackgroundSurface.clear();

    for(int PART = 0; PART < Common::surface_gameplay_background->w; PART += WINDOW_W) {
        SDL_Surface* surface = sdl->createSurface(Point(WINDOW_W, WINDOW_H));
        sdl->copySurface(
            Common::surface_gameplay_background, surface, Point(PART, 0), Point(WINDOW_W, WINDOW_H), Point(0, 0));
        mapBackgroundSurface.push_back(surface);
    }
}

void GamePlay::initMapGround()
{

    for(auto s : mapGroundSurface) {
        SDL_FreeSurface(s);
    }
    mapGroundSurface.clear();

    int nbParts = 1 + (WINDOW_W / MAP_X_STEP);
    Map* map = static_cast<Map*>(world->getMap()->GetUserData());
    vector<Point> mapGround = map->getGround();
    for(unsigned int PART = 0; PART < mapGround.size(); PART += nbParts) {
        SDL_Surface* surface = sdl->createSurface(Point(nbParts * MAP_X_STEP, WINDOW_H));
        for(unsigned int i = PART; i < min(PART + nbParts, (unsigned int)(mapGround.size() - 1)); i++) {
            Point p1 = mapGround.at(i);
            Point p2 = mapGround.at(i + 1);
            int y1 = p1.y;
            int y2 = p2.y;
            int x1 = (i - (PART)) * MAP_X_STEP;
            int x2 = (i + 1 - (PART)) * MAP_X_STEP;
            sdl->drawGround(surface, Point(x1, y1), Point(x2, y2));
        }

        mapGroundSurface.push_back(surface);
    }
}

void GamePlay::initBodies()
{

    for(auto* surface : bodies) {
        SDL_FreeSurface(surface);
    }

    bodies.clear();
    hashTags.clear();

    SDL_Surface* part;
    for(auto* box2Dmobile : world->getBodies()) {
        Grid* mobile = static_cast<Grid*>(box2Dmobile->GetUserData());
        Point mobileSize(mobile->getSize().x * BOX_SIZE, mobile->getSize().y * BOX_SIZE);
        SDL_Surface* mobileSurface = sdl->createSurface(mobileSize);

        for(int i = 0; i < mobile->getSize().x; i++) {
            for(int j = 0; j < mobile->getSize().y; j++) {

                if(mobile->getPart(Point(i, j)) == NULL)
                    continue;

                part = Common::getSurfaceOfType(mobile->getPart(Point(i, j))->getType());
                sdl->copySurface(part, mobileSurface, Point(i * BOX_SIZE, j * BOX_SIZE));
            }
        }

        bodies.push_back(mobileSurface);
        hashTags.push_back(mobile->getHash());
    }
}

bool GamePlay::validBodies()
{

    bool valid = true;

    if(world->getBodies().size() != hashTags.size())
        return false;

    for(auto* box2Dmobile : world->getBodies()) {
        Grid* mobile = static_cast<Grid*>(box2Dmobile->GetUserData());
        bool found = false;
        for(auto hash : hashTags) {
            if(hash == mobile->getHash()) {
                found = true;
                break;
            }
        }
        if(!found) {
            valid = false;
            break;
        }
    }

    return valid;
}

void GamePlay::drawBodies()
{

    b2Body* box2Dmobile = NULL;
    vector<b2Body*> Vecbox2Dmobile = world->getBodies();

    for(unsigned int k = 0; k < Vecbox2Dmobile.size(); k++) {
        box2Dmobile = Vecbox2Dmobile.at(k);
        Grid* mobile = static_cast<Grid*>(box2Dmobile->GetUserData());
        Point mobileSize(mobile->getSize().x * BOX_SIZE, mobile->getSize().y * BOX_SIZE);
        SDL_Surface* mobileSurface = bodies.at(k); //(mobileSize);

        Point start;
        float angle = box2Dmobile->GetAngle();

        start.x = BOX2D_SCALE * box2Dmobile->GetPosition().x - (mobileSize.x / 2);
        start.y = BOX2D_SCALE * box2Dmobile->GetPosition().y - (mobileSize.y / 2);

        SDL_TextureDef texture;
        texture.surface = mobileSurface;
        texture.angle = -angle * 180 / M_PI;
        texture.angle -= 360 * (int)(texture.angle / 360);
        texture.pos = start;
        sdl->registerTexture(texture);
    }
}

void GamePlay::setWorld(World* new_world)
{

    if(new_world != NULL) {
        this->world = new_world;
    }
}

void GamePlay::catchEvents()
{
    world->getPlayer()->doAction(STOP_MOTOR);
    for(auto keycode : sdl->getKeyboardEvents()) {
        switch(keycode) {
        case SDLK_DOWN:
            world->getPlayer()->doAction(GO_DOWNWARD);

            break;

        case SDLK_UP:
           // pose beaucoups de problèmes
           // world->getPlayer()->doAction(GO_UPWARD);
            break;

        case SDLK_LEFT:
            world->getPlayer()->doAction(GO_BACKWARD);
            break;

        case SDLK_RIGHT:
            world->getPlayer()->doAction(GO_FORWARD);
            break;

        case SDLK_ESCAPE:
            loop = false;
            fade = FADEOUT;
            quit = false;
            break;
        }
    }

    if(sdl->getMouseDown()) {
        world->getPlayer()->setFireTarget(sdl->getMousePosition());
        world->getPlayer()->doAction(FIRE);
    }

    if(world->getPlayer()->isDead()) {
        loop = false;
        fade = FADEOUT;
        quit = false;
    }
}



double GamePlay::updateOffset()
{

    b2Body* box2Dmobile = world->getPlayer()->getMobile()->getB2Mobile();

    if(box2Dmobile->GetPosition().x * BOX2D_SCALE > WINDOW_W / 4) {
        OffsetX = box2Dmobile->GetPosition().x * BOX2D_SCALE - WINDOW_W / 4;
        OffsetMove = OffsetX - LastOffsetX >= 0;
        LastOffsetX = OffsetX;
    }

    return OffsetX;
}
