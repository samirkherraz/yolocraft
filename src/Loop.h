#ifndef LOOP_H
#define LOOP_H

#include "SDL.h"

using namespace std;

class Loop
{
public:
    Loop(SDL * _sdl);
    ~Loop();
    bool getQuit()const;
    void start();

protected:
    bool loop;
    bool quit;
    int fade;
    int FPS = 60;
    bool fixFPS;
    SDL * sdl;
};

#endif // LOOP_H
