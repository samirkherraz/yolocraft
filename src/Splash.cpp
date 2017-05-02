#include "Splash.h"

Splash::Splash(SDL* sdl)
    : Loop(sdl)
{
Common::_Splash++;

    SDL_Delay(1000);
    SDL_TextureDef mapPart;
    mapPart.surface = Common::surface_splash_screen;
    mapPart.angle = 0;
    mapPart.pos = Point(0, 0);
    sdl->registerTexture(mapPart);
}

void Splash::start()
{
    
     Common::playAudio(AUDIO_INTRO);
    
    int t1 = SDL_GetTicks();
    fade = FADEIN;
    while(loop) {

        switch(fade) {
        case FADEINOUT:
            sdl->updateFadeOut();
            sdl->updateFadeIn();
            break;
        case FADEIN:
            sdl->updateFadeIn();
            break;

        case FADEOUT:
            sdl->updateFadeOut();
            break;
        case NOFADE:
            sdl->update();
            break;
        }

        int t2 = SDL_GetTicks();

        if(t2 - t1 > SPLASH_TIME) {
            if(FADEOUT) {
                loop = false;
            } else {
                fade = FADEOUT;
            }
        } else {
            fade = NOFADE;
        }
        int waitTime = 1000.0 / FPS;
        SDL_Delay(static_cast<Uint32>(waitTime));
    }
}

Splash::~Splash()
{
Common::_Splash--;

    
}
