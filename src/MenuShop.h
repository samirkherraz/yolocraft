#ifndef MENUSHOP_H
#define MENUSHOP_H

#include "Common.h"
#include "MenuEntry.h"
/**@brief Gére le menu magasin. 
*/
class MenuShop : public MenuEntry
{
private:
 

public:
    MenuShop(SDL* sdl,Player * player);
    virtual ~MenuShop();
    virtual void UpdateHeader();
    virtual void UpdateBody();
    virtual void UpdateFooter();
};

#endif // MENUSHOP_H
