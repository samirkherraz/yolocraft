#include "MenuShop.h"

MenuShop::MenuShop(SDL* sdl, Player* player)
    : MenuEntry(sdl, player)
{
    load();
}

MenuShop::~MenuShop()
{
}

void MenuShop::UpdateHeader()
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
    b.setOnClick(BUY);
    b.setName("Acheter");

    headerBTNList.push_back(b);

    b.setPosition(Point(WINDOW_W - 136, WINDOW_H - 50));
    b.setSize(Point(136, 50));
    b.setType(BUTTON);
    b.setOnClick(CRAFT_MENU);
    b.setName("Garage");
    headerBTNList.push_back(b);
}

void MenuShop::UpdateBody()
{

    bodyBTNList.clear();
    const int OFFSETX = WINDOW_W / 2 - 5 * (2 * BOX_SIZE) / 2;
    const int OFFSETY = WINDOW_H / 2 - 5 * (2 * BOX_SIZE) / 2;

    // int n = 0;
    for(unsigned int i = 0; i < Common::shapes.size(); i++) {

        Button b2;

        b2.setPosition(Point(i % 5 * (2 * BOX_SIZE) + OFFSETX, i / 5 * (2 * BOX_SIZE) + OFFSETY));
        b2.setSize(Point(BOX_SIZE, BOX_SIZE));
        b2.setOnClick(TOGGLE);
        b2.setType(Common::shapes[i]->getType());
        bodyBTNList.push_back(b2);
    }
}

void MenuShop::UpdateFooter()
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
