#ifndef SPLASH_H
#define SPLASH_H

#include "Loop.h"
#include "SDL.h"

/** @brief Affichage du logo de démarrage
*/
class Splash : public Loop
{
public:
    Splash(SDL* sdl);
    virtual ~Splash();
    virtual void start();
};

#endif // SPLASH_H
