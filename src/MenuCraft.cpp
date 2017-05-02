#include "MenuCraft.h"

MenuCraft::MenuCraft(SDL* sdl, Player* player)
    : MenuEntry(sdl, player)
{
    load();
}

MenuCraft::~MenuCraft()
{
}

void MenuCraft::UpdateHeader()
{

    headerBTNList.clear();

    Button b;

    b.setPosition(Point(0, WINDOW_H - 50));
    b.setSize(Point(136, 50));
    b.setType(BUTTON);
    b.setOnClick(QUIT);
    b.setName("Quitter");

    headerBTNList.push_back(b);

    b.setPosition(Point(WINDOW_W / 2 - 136 / 2, WINDOW_H - 50));
    b.setSize(Point(136, 50));
    b.setType(BUTTON);
    b.setOnClick(PLAY);
    b.setName("Jouer");

    headerBTNList.push_back(b);

    b.setPosition(Point(WINDOW_W - 136, WINDOW_H - 50));
    b.setSize(Point(136, 50));
    b.setType(BUTTON);
    b.setOnClick(SHOP_MENU);
    b.setName("Magasin");
    headerBTNList.push_back(b);
}

void MenuCraft::UpdateBody()
{
    bodyBTNList.clear();

    const int OFFSETX = WINDOW_W / 2 - BOX_SIZE * 5;
    const int OFFSETY = WINDOW_H / 2 - BOX_SIZE * 5;
    // int n = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            Button b;
            b.setPosition(Point(i * BOX_SIZE + OFFSETX, j * BOX_SIZE + OFFSETY));
            b.setSize(Point(BOX_SIZE, BOX_SIZE));
            b.setOnClick(CONSTRUCT);
            b.setType(CELL);
            bodyBTNList.push_back(b);
        }
    }
}

void MenuCraft::UpdateFooter()
{

    footerBTNList.clear();

    const int MARGINBETWEEN = 50;
    const int OFFSETX = WINDOW_W / 2 - ((BOX_SIZE + MARGINBETWEEN) * main_player->getShapes().size() / 2);
    const int OFFSETY = 20;

    for(unsigned int i = 0; i < main_player->getShapes().size(); i++) {

        Button b;
        b.setPosition(Point(i * (BOX_SIZE + MARGINBETWEEN) + OFFSETX, OFFSETY));
        b.setSize(Point(BOX_SIZE, BOX_SIZE));
        b.setType(main_player->getShapes()[i]->getType());
        b.setOnClick(TOGGLE);

        footerBTNList.push_back(b);
    }
}
