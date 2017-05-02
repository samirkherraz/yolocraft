#include "Loop.h"

Loop::Loop(SDL* _sdl)
{
    Common::_Loop++;

    sdl = _sdl;
    loop = true;
    quit = false;
}

bool Loop::getQuit() const
{
    return quit;
}

void Loop::start()
{
    Common::playAudio(AUDIO_TRANSITION);
    loop = true;
    quit = false;
    fade = FADEIN;
}

Loop::~Loop()
{
    Common::_Loop--;

    sdl = NULL;
}
