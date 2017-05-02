#include "Menu.h"
#include "Menu.h"

Menu::Menu(SDL* sdl, Player* player)
    : Loop(sdl)
{
    Common::_Menu++;
    this->main_player = player;
    menushop = new MenuShop(sdl, main_player);
    menucraft = new MenuCraft(sdl, main_player);
    currentMenu = menucraft;
}

bool Menu::constructPlayer()
{
    Mobile* player_mobile = new Mobile();
    int start = 0;
    bool playerNotValid = true;
    player_mobile->setPosition(Point(800, 400));
    for(unsigned int k = 0; k < menucraft->bodyBTNList.size(); k++) {

        if(menucraft->bodyBTNList[k].getType() == CELL)
            continue;
        playerNotValid = false;
        int i = +(k - start) / 10;
        int j = 9 - (k - start) % 10;
        AbstractObject* part = Common::getObjectOfType(menucraft->bodyBTNList[k].getType());
        player_mobile->addPart(Point(i, j), part);
    }
    delete main_player->getMobile();
    main_player->setMobile(player_mobile);
    return playerNotValid;
}
Menu::~Menu()
{
    Common::_Menu--;

    delete menucraft;
    delete menushop;
    currentMenu = NULL;
}

void Menu::clearScreen()
{

    for(unsigned int i = 0; i < currentMenu->tobeCleared.size(); i++) {
        SDL_FreeSurface(currentMenu->tobeCleared[i]);
    }
    currentMenu->tobeCleared.clear();
}

void Menu::initScreen()
{
    clearScreen();

    sdl->clearBuffer();

    currentMenu->make();

    for(unsigned int i = 0; i < currentMenu->finalSurfacesList.size(); i++) {
        sdl->registerTexture(currentMenu->finalSurfacesList[i]);
    }
}

void Menu::start()
{
    Loop::start();
    Common::playAudio(AUDIO_MENU);

    sdl->setOffsetX(0);
    while(loop) {

        int t1 = SDL_GetTicks();
        sdl->catchEvents();
        eventManager();

        switch(fade) {
        case FADEINOUT:

            sdl->updateFadeOut();
            initScreen();

            sdl->updateFadeIn();
            break;
        case FADEIN:
            initScreen();
            sdl->updateFadeIn();
            break;

        case FADEOUT:
            initScreen();
            sdl->updateFadeOut();
            break;
        case NOFADE:
            initScreen();
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

void Menu::doAction(Button& btn)
{

    switch(btn.getOnClick()) {

    case SHOP_MENU:
        fade = FADEINOUT;
        currentMenu = menushop;
        break;

    case QUIT:
        loop = false;
        quit = true;
        break;
    case CRAFT_MENU:
        fade = FADEINOUT;
        currentMenu = menucraft;
        currentMenu->UpdateFooter();

        break;
    case PLAY:
        loop = constructPlayer();
        fade = FADEOUT;
        break;

    case CONSTRUCT:

        for(unsigned int i = 0; i < currentMenu->bodyBTNList.size(); i++) {
            if(&currentMenu->bodyBTNList[i] == &btn) {
                doGrid(i);
            }
        }

        break;
    case BUY:
        for(auto& b : currentMenu->bodyBTNList) {
            if(b.getStatus() == SELECTED) {
                b.setStatus(UNSELECTED);
                main_player->buyShape(Common::getObjectOfType(b.getType()));
                break;
            }
        }

        currentMenu->UpdateFooter();

        break;
    case TOGGLE: {
        unsigned int status = btn.getStatus();

        for(auto& b : currentMenu->footerBTNList) {
            b.setStatus(UNSELECTED);
        }
        for(auto& b : currentMenu->headerBTNList) {
            b.setStatus(UNSELECTED);
        }
        for(auto& b : currentMenu->bodyBTNList) {
            b.setStatus(UNSELECTED);
        }

        if(status == UNSELECTED) { ///////// On catche l'état du bouton
            btn.setStatus(SELECTED);
        }
    }

    break;
    default:

        break;
    }
}

vector<unsigned int> Menu::somethingIsNear(unsigned int idButton)
{ // Renvoie un vector d'ids des voisins
    vector<unsigned int> ret;

    switch(idButton) {
    case 0: // coin bas gauche
        ret.push_back(1);
        ret.push_back(10);
        break;
    case 9: // coin haut gauche
        ret.push_back(8);
        ret.push_back(19);
        break;
    case 90: // coin bas droit
        ret.push_back(91);
        ret.push_back(80);
        break;
    case 99: // coin haut droit
        ret.push_back(89);
        ret.push_back(98);
        break;
    default:
        if(idButton > 0 && idButton < 9) { // bord gauche
            ret.push_back(idButton - 1);
            ret.push_back(idButton + 1);
            ret.push_back(idButton + 10);
        } else if(idButton % 10 == 9) { // bord haut
            ret.push_back(idButton - 10);
            ret.push_back(idButton - 1);
            ret.push_back(idButton + 10);
        } else if(idButton % 10 == 0) { // bord bas
            ret.push_back(idButton - 10);
            ret.push_back(idButton + 1);
            ret.push_back(idButton + 10);
        } else if(idButton > 90 && idButton < 99) { // bord droit
            ret.push_back(idButton - 1);
            ret.push_back(idButton + 1);
            ret.push_back(idButton - 10);
        } else { // Le milieu
            ret.push_back(idButton - 1);
            ret.push_back(idButton + 1);
            ret.push_back(idButton - 10);
            ret.push_back(idButton + 10);
        }
    }

    for(unsigned int i = 0; i < ret.size(); i++) {
        if(currentMenu->bodyBTNList[ret[i]].getType() == CELL) {
            ret.erase(ret.begin() + i);
            i--;
        }
    }

    return ret;
}

bool Menu::canBePlacedOnIt(Button buttonToPlaced, unsigned int idButton, int ignore)
{

    bool ignoreIsBodyWork = (ignore != -1) && currentMenu->bodyBTNList[ignore].getType() == BODYWORK;
    bool empty = (ignore != -1) || currentMenu->bodyBTNList[idButton].getType() == CELL;
    bool bodywork = buttonToPlaced.getType() == BODYWORK;
    bool wheel = buttonToPlaced.getType() == WHEEL;
    bool weapon = buttonToPlaced.getType() == WEAPON;
    bool firstBodyWork = ((atLeastOneBodyWork == (ignoreIsBodyWork ? 1 : 0)) && bodywork);
    bool bodyWorkNear = false;
    bool weaponNear = false;
    bool wheelNear = false;
    for(auto id : somethingIsNear(idButton)) {

        if(int(id) == ignore)
            continue;


        switch(currentMenu->bodyBTNList[id].getType()) {
        case BODYWORK:
            bodyWorkNear = true;
            break;
        case WHEEL:
            wheelNear = true;
            break;
        case WEAPON:
            weaponNear = true;
            break;
        default:
            continue;
        }
    }

    if(firstBodyWork) {
        return true;
    } else if(empty && bodyWorkNear) {

        if(wheel && weaponNear) {
            return false;
        } else if(weapon && wheelNear) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void Menu::doGrid(unsigned int idButton)
{
    bool atLeastOneSelected = false;
    if(currentMenu == menucraft) {

        vector<unsigned int> nears = somethingIsNear(idButton);
        for(auto& buttonSelected : currentMenu->footerBTNList) {
            if(buttonSelected.getStatus() == SELECTED) {

                atLeastOneSelected = true;
                if(canBePlacedOnIt(buttonSelected, idButton)) { // On regarde si notre case a un
                    currentMenu->bodyBTNList[idButton].setType(buttonSelected.getType());
                    atLeastOneBodyWork += (buttonSelected.getType() == BODYWORK) ? 1 : 0;
                }
                break;
            }
        }
        if(!atLeastOneSelected) {
            unsigned int shouldKeep = 0;

            bool topEmpty = false;
            bool bottomEmpty = false;
            bool leftEmpty = false;
            bool rightEmpty = false;
            switch(idButton) {
            case 0: // coin bas gauche
                topEmpty = currentMenu->bodyBTNList[idButton + 1].getType() == CELL;
                rightEmpty = currentMenu->bodyBTNList[idButton + 10].getType() == CELL;
                break;
            case 9: // coin haut gauche
                bottomEmpty = idButton - 1 > 0 && currentMenu->bodyBTNList[idButton - 1].getType() == CELL;
                rightEmpty = currentMenu->bodyBTNList[idButton + 10].getType() == CELL;
                break;
            case 90: // coin bas droit
                topEmpty = currentMenu->bodyBTNList[idButton + 1].getType() == CELL;
                leftEmpty = currentMenu->bodyBTNList[idButton - 10].getType() == CELL;
                break;
            case 99: // coin haut droit
                leftEmpty = currentMenu->bodyBTNList[idButton - 10].getType() == CELL;
                bottomEmpty = currentMenu->bodyBTNList[idButton - 1].getType() == CELL;
                break;
            default:
                if(idButton > 0 && idButton < 9) { // bord gauche
                    leftEmpty = currentMenu->bodyBTNList[idButton - 10].getType() == CELL;
                    bottomEmpty = currentMenu->bodyBTNList[idButton - 1].getType() == CELL;
                    topEmpty = currentMenu->bodyBTNList[idButton + 1].getType() == CELL;
                } else if(idButton % 10 == 9) { // bord haut
                    rightEmpty = currentMenu->bodyBTNList[idButton + 10].getType() == CELL;
                    leftEmpty = currentMenu->bodyBTNList[idButton - 10].getType() == CELL;
                    bottomEmpty = currentMenu->bodyBTNList[idButton - 1].getType() == CELL;
                } else if(idButton % 10 == 0) { // bord bas
                    rightEmpty = currentMenu->bodyBTNList[idButton + 10].getType() == CELL;
                    leftEmpty = currentMenu->bodyBTNList[idButton - 10].getType() == CELL;
                    topEmpty = currentMenu->bodyBTNList[idButton + 1].getType() == CELL;
                } else if(idButton > 90 && idButton < 99) { // bord droit
                    leftEmpty = currentMenu->bodyBTNList[idButton - 10].getType() == CELL;
                    bottomEmpty = currentMenu->bodyBTNList[idButton - 1].getType() == CELL;
                    topEmpty = currentMenu->bodyBTNList[idButton + 1].getType() == CELL;
                } else { // Le milieu
                    rightEmpty = currentMenu->bodyBTNList[idButton + 10].getType() == CELL;
                    leftEmpty = currentMenu->bodyBTNList[idButton - 10].getType() == CELL;
                    bottomEmpty = currentMenu->bodyBTNList[idButton - 1].getType() == CELL;
                    topEmpty = currentMenu->bodyBTNList[idButton + 1].getType() == CELL;
                }
            }
            bool canbeRemoved = false;
            vector<unsigned int> btnNears = somethingIsNear(idButton);
            for(unsigned int btn : btnNears) {
                bool thisCanKeep = false;

                thisCanKeep = canBePlacedOnIt(currentMenu->bodyBTNList[btn], btn, idButton);

                if(thisCanKeep) {
                    shouldKeep++;
                }
            }

            if(!rightEmpty && !leftEmpty && bottomEmpty && topEmpty) {
                canbeRemoved = false;
            } else if(rightEmpty && leftEmpty && !bottomEmpty && !topEmpty) {
                canbeRemoved = false;
            } else if(shouldKeep >= somethingIsNear(idButton).size()) {

                canbeRemoved = true;
            } else {
                canbeRemoved = (atLeastOneBodyWork <= 2 && currentMenu->bodyBTNList[idButton].getType() == BODYWORK);
            }

            if(canbeRemoved) {
                atLeastOneBodyWork -= (currentMenu->bodyBTNList[idButton].getType() == BODYWORK) ? 1 : 0;
                currentMenu->bodyBTNList[idButton].setType(CELL);
            }
        }
    }
}

void Menu::eventManager()
{

    if(sdl->getMouseClick()) {

        for(auto& btn : currentMenu->headerBTNList) {
            if(mouseOverButton(sdl->getMousePosition(), btn)) {
                doAction(btn);
                Common::playAudio(AUDIO_CLICK);
            }
        }

        for(auto& btn : currentMenu->footerBTNList) {
            if(mouseOverButton(sdl->getMousePosition(), btn)) {
                doAction(btn);
                Common::playAudio(AUDIO_CLICK);
            }
        }

        for(unsigned int i = 0; i < currentMenu->bodyBTNList.size(); i++) {
            if(mouseOverButton(sdl->getMousePosition(), currentMenu->bodyBTNList[i])) {
                doAction(currentMenu->bodyBTNList[i]);
                Common::playAudio(AUDIO_CONSTRUCT);
            }
        }
    }
}

bool Menu::mouseOverButton(Point mousePosition, Button btn)
{

    bool insideX =
        ((mousePosition.x <= (btn.getSize().x + btn.getPosition().x)) && (mousePosition.x >= btn.getPosition().x));
    bool insideY =
        ((mousePosition.y <= (btn.getSize().y + btn.getPosition().y)) && (mousePosition.y >= btn.getPosition().y));

    return insideX && insideY;
}

void Menu::setPlayer(Player* player)
{
    main_player = player;
}
Player* Menu::getPlayer() const
{
    return main_player;
}
