#include "MenuEntry.h"
#include "Game.h"
MenuEntry::MenuEntry(SDL* sdl, Player* player)
{
    this->main_player = player;
    this->sdl = sdl;
}

MenuEntry::~MenuEntry()
{

    headerBTNList.clear();
    bodyBTNList.clear(); // grille du player
    footerBTNList.clear(); // grille du player
    finalSurfacesList.clear();
    sdl = NULL;
    main_player = NULL;
}

void MenuEntry::load()
{

    headerBTNList.clear();
    bodyBTNList.clear(); // grille du player
    footerBTNList.clear(); // grille du player
    finalSurfacesList.clear();
    UpdateHeader();
    UpdateBody();
    UpdateFooter();
}

void MenuEntry::build(vector<Button> section)
{
        SDL_TextureDef toSDL;

    for(auto btn : section) { // Pour les boutons de la buttonList
        if(btn.getStatus() == SELECTED) {
            toSDL.surface = Common::surface_selected;
            toSDL.pos = Point(btn.getPosition().x - 10, btn.getPosition().y - 10);
            finalSurfacesList.push_back(toSDL);
        }

        toSDL.pos = btn.getPosition();
        toSDL.surface = Common::getSurfaceOfType(btn.getType());
        toSDL.angle = 0;
        finalSurfacesList.push_back(toSDL);
        if(btn.getName() != "") {
            SDL_Surface* text = sdl->createText(btn.getName());
            tobeCleared.push_back(text);
            toSDL.pos.x = toSDL.pos.x + (toSDL.surface->w - text->w) / 2;
            toSDL.pos.y = toSDL.pos.y + (toSDL.surface->h - text->h) / 2;
            toSDL.surface = text;
            finalSurfacesList.push_back(toSDL);
        }
    }
}

void MenuEntry::make()
{
    SDL_TextureDef toSDL;
    finalSurfacesList.clear();

    toSDL.surface = Common::surface_menu_background;
    toSDL.pos = Point(0, 0);
    toSDL.angle = 0;
    finalSurfacesList.push_back(toSDL);
    
    build(headerBTNList);
    build(bodyBTNList);
    build(footerBTNList);
    
}
