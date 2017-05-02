#include "Game.h"
using namespace std;

int main()
{

    Game* c = new Game();
    c->start();
    delete c;


cout << "AbstractObject : " << Common::_AbstractObject << endl;
cout << "ContactListner : " <<  Common::_ContactListner<< endl;
cout << "Game : " <<  Common::_Game<< endl;
cout << "GamePlay : " <<  Common::_GamePlay<< endl;
cout << "Grid : " <<  Common::_Grid<< endl;
cout << "Loop : " <<  Common::_Loop<< endl;
cout << "Map : " <<  Common::_Map<< endl;
cout << "Menu : " <<  Common::_Menu<< endl;
cout << "MenuCraft : " <<  Common::_MenuCraft<< endl;
cout << "MenuEntry : " <<  Common::_MenuEntry << endl;
cout << "MenuShop : " <<  Common::_MenuShop << endl;
cout << "Mobile : " <<  Common::_Mobile<< endl;
cout << "Player : " <<  Common::_Player << endl;
cout << "SDL : " <<  Common::_SDL<< endl;
cout << "Splash : " <<  Common::_Splash<< endl;
cout << "World : " <<  Common::_World << endl;
}