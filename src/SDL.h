#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include "Point.h"
#include "Common.h"
#include <vector>

#include <assert.h>

using namespace std;
/** @brief Cette classe est une surchage de la librairie SDL. les fonctions définies ici sont réutilisées telles quelles dans notre code pour tout affichage à l'ecran.
*/

struct SDL_TextureDef
{
    double angle;
    SDL_Surface* surface;
    Point pos;
};

class SDL
{

private:
    double OffsetX;

    SDL_Texture* createTexture(SDL_Surface* surface);
    void render(SDL_TextureDef texture, int alpha);
    SDL_Surface* resizeSurface(SDL_Surface* source, Point size);
    bool mouseDown;
    bool mouseClick;
    vector<int> keyboadEvents;
    Point mousePosition;
    void setPixel(SDL_Surface* surface, int x, int y, SDL_Color color = {255,255,255});
    SDL_Renderer* renderer;
    SDL_Window* window;
    vector<SDL_TextureDef>* toDraw;

public:
    SDL();
    ~SDL();
    void init();
    void drawGround(SDL_Surface* source, Point p1, Point p2);
    void print(); 
    void clear();
    void update(int alpha = 255);
    void catchEvents();
    bool getMouseDown() const;
    Point getMousePosition() const;
    vector<int> getKeyboardEvents() const;
    void registerTexture(SDL_TextureDef texture);
    void clearBuffer();
    void copySurface(SDL_Surface* source, SDL_Surface* target, Point pos);
    void copySurface(SDL_Surface* source, SDL_Surface* target, Point sourcePos, Point sourceSize, Point targetPos);
    SDL_Surface* createSurface(string image);
    SDL_Surface* createSurface(Point size);
    void setOffsetX(double offset);
    double getOffsetX();
    void regressionTest();
    SDL_Surface* createText(string text, SDL_Color rgb= {0,0,0});
    bool getMouseClick();
    void updateFadeIn();
    void updateFadeOut();
    void drawText(SDL_Surface* t_text, string text, Point pos, SDL_Color rgb = {0,0,0});
};

#endif // SDL_H
