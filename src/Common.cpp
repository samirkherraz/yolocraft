#include "Common.h"
SDL_Surface* Common::surface_button;
SDL_Surface* Common::surface_cell;
SDL_Surface* Common::surface_selected;
SDL_Surface* Common::surface_empty;

SDL_Surface* Common::surface_wheel;
SDL_Surface* Common::surface_bodywork;
SDL_Surface* Common::surface_angle_left_up;
SDL_Surface* Common::surface_angle_left_down;
SDL_Surface* Common::surface_angle_right_up;
SDL_Surface* Common::surface_angle_right_down;
SDL_Surface* Common::surface_weapon;
SDL_Surface* Common::surface_rocket;
SDL_Surface* Common::surface_explosion_1;
SDL_Surface* Common::surface_explosion_2;
SDL_Surface* Common::surface_explosion_3;
SDL_Surface* Common::surface_explosion_4;
SDL_Surface* Common::surface_menu_background;
SDL_Surface* Common::surface_gameplay_background;
SDL_Surface* Common::surface_splash_screen;

Mix_Music* Common::music_background_menu;
Mix_Music* Common::music_background_gameplay;
Mix_Chunk* Common::audio_fire;
Mix_Chunk* Common::audio_motor;
Mix_Chunk* Common::audio_rocket_explode;
Mix_Chunk* Common::audio_button_click;
Mix_Chunk* Common::audio_transition;
Mix_Chunk* Common::audio_intro;
Mix_Chunk* Common::audio_construct;

TTF_Font* Common::police;

AbstractObject* Common::angle_right_up;
AbstractObject* Common::angle_right_down;
AbstractObject* Common::angle_left_up;
AbstractObject* Common::angle_left_down;
AbstractObject* Common::bodywork;
AbstractObject* Common::wheel;
AbstractObject* Common::weapon;
AbstractObject* Common::rocket;
int Common::gridID = 0;
vector<AbstractObject*> Common::bought_shapes;
vector<AbstractObject*> Common::shapes;

int Common::_AbstractObject = 0;
int Common::_ContactListner = 0;
int Common::_Game = 0;
int Common::_GamePlay = 0;
int Common::_Grid = 0;
int Common::_Loop = 0;
int Common::_Map = 0;
int Common::_Menu = 0;
int Common::_MenuCraft = 0;
int Common::_MenuEntry = 0;
int Common::_MenuShop = 0;
int Common::_Mobile = 0;
int Common::_Player = 0;
int Common::_SDL = 0;
int Common::_Splash = 0;
int Common::_World = 0;

SDL_Surface* Common::getSurfaceOfType(unsigned int type)
{
    SDL_Surface* part;

    switch(type) {
    case WHEEL:
        part = Common::surface_wheel;
        break;
    case BODYWORK:
        part = Common::surface_bodywork;
        break;
    case ANGLE_LEFT_UP:
        part = Common::surface_angle_left_up;
        break;
    case ANGLE_RIGHT_UP:
        part = Common::surface_angle_right_up;
        break;
    case ANGLE_LEFT_DOWN:
        part = Common::surface_angle_left_down;
        break;
    case ANGLE_RIGHT_DOWN:
        part = Common::surface_angle_right_down;
        break;
    case WEAPON:
        part = Common::surface_weapon;
        break;

    case ROCKET:
        part = Common::surface_rocket;
        break;
    case CELL:
        part = Common::surface_cell;
        break;
    case BUTTON:
        part = Common::surface_button;
        break;
    case SELECTED:
        part = Common::surface_selected;
        break;
    case EXPLOSION_1:
        part = Common::surface_explosion_1;
        break;
    case EXPLOSION_2:
        part = Common::surface_explosion_2;
        break;
    case EXPLOSION_3:
        part = Common::surface_explosion_3;
        break;
    case EXPLOSION_4:
        part = Common::surface_explosion_4;
        break;
    default:
        part = Common::surface_empty;
        break;
    }
    return part;
}

AbstractObject* Common::getObjectOfType(unsigned int type)
{
    AbstractObject* part;

    switch(type) {
    case WHEEL:
        part = Common::wheel;
        break;
    case BODYWORK:
        part = Common::bodywork;
        break;
    case ANGLE_LEFT_UP:
        part = Common::angle_left_up;
        break;
    case ANGLE_LEFT_DOWN:
        part = Common::angle_left_down;
        break;
    case ANGLE_RIGHT_UP:
        part = Common::angle_right_up;
        break;

    case ANGLE_RIGHT_DOWN:
        part = Common::angle_right_down;
        break;
    case WEAPON:
        part = Common::weapon;
        break;
    case ROCKET:
        part = Common::rocket;
        break;

    default:
        part = NULL;
        break;
    }
    return part;
}

void Common::stopAudio()
{
    if(Mix_PlayingMusic() != 0) {
        Mix_HaltMusic();
    }
}

void Common::playAudio(unsigned int audio)
{

    switch(audio) {
    case AUDIO_GAMEPLAY:
        stopAudio();
        Mix_PlayMusic(Common::music_background_gameplay, -1);

        break;
    case AUDIO_MENU:
        stopAudio();

        Mix_PlayMusic(Common::music_background_menu, -1);

        break;
    case AUDIO_FIRE:
        Mix_PlayChannel(3, Common::audio_fire, 0);
        break;
    case AUDIO_CONSTRUCT:
        Mix_PlayChannel(0, Common::audio_construct, 0);

        break;
    case AUDIO_TRANSITION:
        Mix_PlayChannel(2, Common::audio_transition, 0);

        break;
    case AUDIO_CLICK:
        Mix_PlayChannel(0, Common::audio_button_click, 0);

        break;
    case AUDIO_EXPLODE:
        Mix_PlayChannel(4, Common::audio_rocket_explode, 0);

        break;
    case AUDIO_INTRO:
        Mix_PlayChannel(-1, Common::audio_intro, 0);

        break;
    case AUDIO_MOTOR:
        Mix_PlayChannel(1, Common::audio_motor, 0);

        break;
    }
}

void Common::init()
{

    string PartsDir = "./data/items/";
    string MenuDir = "./data/menu/";
    string AudioDir = "./data/audio/";

    Common::surface_empty = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0);

    Common::surface_button = Common::createSurface(MenuDir + "button.png");
    Common::surface_cell = Common::createSurface(MenuDir + "cell.png");
    Common::surface_selected = Common::createSurface(MenuDir + "selected.png");

    Common::surface_wheel = Common::createSurface(PartsDir + "wheel.png");
    Common::surface_bodywork = Common::createSurface(PartsDir + "bodywork.png");
    Common::surface_angle_left_up = Common::createSurface(PartsDir + "angle_left_up.png");
    Common::surface_angle_left_down = Common::createSurface(PartsDir + "angle_left_down.png");
    Common::surface_angle_right_up = Common::createSurface(PartsDir + "angle_right_up.png");
    Common::surface_angle_right_down = Common::createSurface(PartsDir + "angle_right_down.png");
    Common::surface_weapon = Common::createSurface(PartsDir + "weapon.png");
    Common::surface_rocket = Common::createSurface(PartsDir + "rocket.png");
    Common::surface_explosion_1 = Common::createSurface(PartsDir + "explosion_1.png");
    Common::surface_explosion_2 = Common::createSurface(PartsDir + "explosion_2.png");
    Common::surface_explosion_3 = Common::createSurface(PartsDir + "explosion_3.png");
    Common::surface_explosion_4 = Common::createSurface(PartsDir + "explosion_4.png");
    Common::surface_gameplay_background = Common::createSurface(PartsDir + "background.png");
    Common::surface_menu_background = Common::createSurface(MenuDir + "background.png");
    Common::surface_splash_screen = Common::createSurface(MenuDir + "splash.png");

    Common::music_background_menu = Mix_LoadMUS((AudioDir + "music_menu.WAV").c_str());
    Common::music_background_gameplay = Mix_LoadMUS((AudioDir + "music_gameplay.WAV").c_str());
    Common::audio_fire = Mix_LoadWAV((AudioDir + "fire.WAV").c_str());
    Common::audio_motor = Mix_LoadWAV((AudioDir + "motor.WAV").c_str());
    Common::audio_rocket_explode = Mix_LoadWAV((AudioDir + "rocket_explode.WAV").c_str());
    Common::audio_button_click = Mix_LoadWAV((AudioDir + "button_click.WAV").c_str());
    Common::audio_transition = Mix_LoadWAV((AudioDir + "transition.WAV").c_str());
    Common::audio_intro = Mix_LoadWAV((AudioDir + "intro.WAV").c_str());
    Common::audio_construct = Mix_LoadWAV((AudioDir + "construct.WAV").c_str());

    Mix_Volume(0, MIX_MAX_VOLUME);
    Mix_Volume(1, MIX_MAX_VOLUME);
    Mix_Volume(2, MIX_MAX_VOLUME);
    Mix_Volume(3, MIX_MAX_VOLUME);
    Mix_Volume(4, MIX_MAX_VOLUME);
    Mix_Volume(-1, MIX_MAX_VOLUME);

    Common::police = TTF_OpenFont((PartsDir + "arialbd.ttf").c_str(), 16);

    Common::angle_right_up = new AbstractObject();
    Common::angle_right_down = new AbstractObject();
    Common::angle_left_up = new AbstractObject();
    Common::angle_left_down = new AbstractObject();
    Common::bodywork = new AbstractObject();
    Common::wheel = new AbstractObject();
    Common::weapon = new AbstractObject();
    Common::rocket = new AbstractObject();

    Common::shapes.push_back(Common::angle_right_up);
    Common::shapes.push_back(Common::angle_right_down);
    Common::shapes.push_back(Common::angle_left_up);
    Common::shapes.push_back(Common::angle_left_down);
    Common::shapes.push_back(Common::bodywork);
    Common::shapes.push_back(Common::wheel);
    Common::shapes.push_back(Common::weapon);

    Common::angle_right_up->setType(ANGLE_RIGHT_UP);
    Common::angle_right_down->setType(ANGLE_RIGHT_DOWN);
    Common::angle_left_up->setType(ANGLE_LEFT_UP);
    Common::angle_left_down->setType(ANGLE_LEFT_DOWN);
    Common::bodywork->setType(BODYWORK);
    Common::wheel->setType(WHEEL);
    Common::weapon->setType(WEAPON);
    Common::rocket->setType(ROCKET);

    Common::angle_right_up->setDammage(5);
    Common::angle_right_down->setDammage(5);
    Common::angle_left_up->setDammage(5);
    Common::angle_left_down->setDammage(5);
    Common::bodywork->setDammage(10);
    Common::wheel->setDammage(0);
    Common::weapon->setDammage(5);
    Common::rocket->setDammage(25);

    Common::angle_right_up->setLife(10);
    Common::angle_right_down->setLife(10);
    Common::angle_left_up->setLife(10);
    Common::angle_left_down->setLife(10);
    Common::bodywork->setLife(10);
    Common::wheel->setLife(0);
    Common::weapon->setLife(0);
    Common::rocket->setLife(0);
}

void Common::destroy()
{

    SDL_FreeSurface(Common::surface_angle_left_down);
    SDL_FreeSurface(Common::surface_angle_left_up);
    SDL_FreeSurface(Common::surface_angle_right_down);
    SDL_FreeSurface(Common::surface_angle_right_up);
    SDL_FreeSurface(Common::surface_bodywork);
    SDL_FreeSurface(Common::surface_button);
    SDL_FreeSurface(Common::surface_cell);
    SDL_FreeSurface(Common::surface_empty);
    SDL_FreeSurface(Common::surface_explosion_1);
    SDL_FreeSurface(Common::surface_explosion_2);
    SDL_FreeSurface(Common::surface_explosion_3);
    SDL_FreeSurface(Common::surface_explosion_4);
    SDL_FreeSurface(Common::surface_gameplay_background);
    SDL_FreeSurface(Common::surface_menu_background);
    SDL_FreeSurface(Common::surface_rocket);
    SDL_FreeSurface(Common::surface_selected);
    SDL_FreeSurface(Common::surface_splash_screen);
    SDL_FreeSurface(Common::surface_weapon);
    SDL_FreeSurface(Common::surface_wheel);

    Mix_FreeChunk(audio_construct);
    Mix_FreeChunk(audio_intro);
    Mix_FreeChunk(audio_transition);
    Mix_FreeChunk(audio_button_click);
    Mix_FreeChunk(audio_rocket_explode);
    Mix_FreeChunk(audio_motor);
    Mix_FreeChunk(audio_fire);
    Mix_FreeMusic(music_background_gameplay);
    Mix_FreeMusic(music_background_menu);
}

SDL_Surface* Common::createSurface(string image)
{

    SDL_Surface* returnSurface;
    SDL_Surface* imageSurface = IMG_Load(image.c_str());

    if(imageSurface == NULL) {
        cerr << "Unable to load image ! SDL Error: " << SDL_GetError() << endl;
        exit(-1);
    } else {

        returnSurface = SDL_ConvertSurfaceFormat(imageSurface, SDL_PIXELFORMAT_RGBA8888, 0);
        if(returnSurface == NULL) {
            cerr << "Unable to optimize image " << image.c_str() << "! SDL Error: " << SDL_GetError();
            exit(-1);
        }
    }

    return returnSurface;
}