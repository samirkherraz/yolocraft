#ifndef MENUCRAFT_H
#define MENUCRAFT_H

#include "Common.h"
#include "Grid.h"
#include "MenuEntry.h"
/**@brief S'occupe de gérer le menu de la grille. */
class MenuCraft : public MenuEntry
{
private:
 
	
public:
	MenuCraft(SDL * sdl,Player * player);
	virtual ~MenuCraft();
    virtual void UpdateHeader();
    virtual void UpdateBody();
    virtual void UpdateFooter();
	};

#endif // MENUCRAFT_H
