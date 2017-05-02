#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <string>
#include <vector>
#include "Point.h"
#include "AbstractObject.h"
#include "SDL.h"
#include "Button.h"
#include "Player.h"

using namespace std;
/**@brief définit les éléments communs entre les menus. Classe mère des classes menus.
*/
class MenuEntry
{
public:
    MenuEntry(SDL* sdl, Player* player);
    ~MenuEntry();

    vector<Button> headerBTNList;
    vector<Button> bodyBTNList; // grille du player
    vector<Button> footerBTNList; // grille du player
    vector<SDL_TextureDef> finalSurfacesList;
    vector<SDL_Surface*> tobeCleared;

    virtual void load();
    virtual void make();
    virtual void build(vector<Button> section);

    virtual void UpdateHeader(){};
    virtual void UpdateBody(){};
    virtual void UpdateFooter(){};
protected:
    
    Player* main_player;
    SDL* sdl;
};

#endif // MENUENTRY_H
