#include "SDL.h"

SDL::SDL()
{
Common::_SDL++;

    toDraw = new vector<SDL_TextureDef>();
}

void SDL::setOffsetX(double offset)
{

    OffsetX = offset;
}

double SDL::getOffsetX()
{

    return OffsetX;
}

SDL_Surface* SDL::createText(string text, SDL_Color rgb)
{

    SDL_Surface* source = NULL;

    if(!Common::police) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    } else {
        source = TTF_RenderText_Blended(Common::police, text.c_str(), rgb);
    }

    return source;
}
void SDL::drawText(SDL_Surface* t_text, string text, Point pos, SDL_Color rgb)
{
    SDL_Surface* t = createText(text.c_str(), rgb);
    copySurface(t, t_text, pos);
}

SDL_Texture* SDL::createTexture(SDL_Surface* surface)
{
    SDL_Texture* ret = SDL_CreateTextureFromSurface(this->renderer, surface);

    return ret;
}

void SDL::registerTexture(SDL_TextureDef texture)
{
    toDraw->push_back(texture);
}

void SDL::clearBuffer()
{
    toDraw->clear();
}

void SDL::catchEvents()
{
    SDL_Event e;
    keyboadEvents.clear();
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_MOUSEBUTTONDOWN: {
            mouseClick = true;
            mouseDown = true;
        } break;
        case SDL_MOUSEBUTTONUP: {
            mouseDown = false;
        } break;
        case SDL_KEYDOWN: {
            keyboadEvents.push_back(e.key.keysym.sym);
        } break;
        case SDL_MOUSEMOTION: {
            mousePosition.x = e.motion.x;
            mousePosition.y = WINDOW_H - e.motion.y;
        } break;
        }
    }
}

vector<int> SDL::getKeyboardEvents() const
{

    return keyboadEvents;
}

Point SDL::getMousePosition() const
{

    return mousePosition;
}

bool SDL::getMouseDown() const
{

    return mouseDown;
}

bool SDL::getMouseClick()
{
    if(mouseClick) {
        mouseClick = false;
        return true;
    } else {
        return false;
    }
}

void SDL::render(SDL_TextureDef texture, int alpha)
{
    SDL_Rect targetRect;

    targetRect.x = texture.pos.x - OffsetX;
    targetRect.y = WINDOW_H - (texture.surface->h + texture.pos.y);
    targetRect.w = texture.surface->w;
    targetRect.h = texture.surface->h;

    SDL_Texture* t = createTexture(texture.surface);
    SDL_SetTextureAlphaMod(t, alpha);
    SDL_RenderCopyEx(this->renderer, t, NULL, &targetRect, texture.angle, NULL, SDL_FLIP_NONE);

    SDL_DestroyTexture(t);
}

SDL_Surface* SDL::createSurface(string image)
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

SDL_Surface* SDL::resizeSurface(SDL_Surface* source, Point size)
{
    return NULL;
}

SDL_Surface* SDL::createSurface(Point size)
{
    SDL_Surface* ret = SDL_CreateRGBSurface(0, size.x, size.y, 32, 0, 0, 0, 0);
    SDL_SetColorKey(ret, SDL_TRUE, SDL_MapRGB(ret->format, 0, 0, 0));
    return ret;
}

void SDL::copySurface(SDL_Surface* source, SDL_Surface* target, Point pos)
{

    SDL_Rect targetRect;

    targetRect.x = pos.x;
    targetRect.y = pos.y;
    targetRect.w = source->w;
    targetRect.h = source->h;

    SDL_BlitSurface(source, NULL, target, &targetRect);
}

void SDL::copySurface(SDL_Surface* source, SDL_Surface* target, Point sourcePos, Point sourceSize, Point targetPos)
{

    SDL_Rect targetRect, sourceRect;

    sourceRect.x = sourcePos.x;
    sourceRect.y = sourcePos.y;
    sourceRect.w = sourceSize.x;
    sourceRect.h = sourceSize.y;

    targetRect.x = targetPos.x;
    targetRect.y = targetPos.y;
    targetRect.w = sourceSize.x;
    targetRect.h = sourceSize.y;

    SDL_BlitSurface(source, &sourceRect, target, &targetRect);
}

void SDL::init()
{

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Échec de l'initialisation de la SDL " << SDL_GetError();
        exit(-1);
    } else {
        SDL_GL_SwapWindow(window);
        this->window = SDL_CreateWindow(
            "YoloCraft", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL);

        if(window) {
             if(FULLSCREEN) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)) {
                cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
                exit(-1);
            }
            if(TTF_Init() == -1) {
                fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            }

            if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
                cerr << "AUdio could not initialize! "<< endl;
            }

            // Set the window caption

            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

        } else {
            cerr << "Erreur de création de la fenêtre: " << SDL_GetError();
            exit(-1);
        }
    }
}

void SDL::drawGround(SDL_Surface* surface, Point p1, Point p2)
{
    
    SDL_Color g{0,200,0};
    SDL_Color s{8,13,28};
    

    p1.y = surface->h - 1 - p1.y;
    p2.y = surface->h - 1 - p2.y;

    int xsize = max(p1.x, p2.x) - min(p1.x, p2.x);

    double a = double(p1.y - p2.y) / double(p1.x - p2.x);
    double b = p1.y - a * p1.x;

    int addx = p1.x > p2.x ? -1 : 1;

    int x = p1.x;
    int y = p1.y;

    for(int i = 0; i < xsize; i++) {
        
        int r = min(-y+surface->h,int(rand() / (RAND_MAX + 1.0) * (10+1)));
        
        for(int j = y-r; j < y; j++) {
            setPixel(surface, x, j, g);
        }
        for(int j = y; j < surface->h; j++) {
            setPixel(surface, x, j, s);
        }
        

        x += addx;
        y = a * x + b;
    }
}
void SDL::update(int alpha)
{
    clear();
    for(unsigned int i = 0; i < toDraw->size(); ++i) {
        render(toDraw->at(i), alpha);
    }
    print();
}

void SDL::updateFadeIn()
{

    for(int i = 0; i < 255; i += 10) {
        clear();
        update(i);
        print();
        SDL_Delay(2);
    }
}

void SDL::updateFadeOut()
{

    for(int i = 255; i >= 0; i -= 10) {
        clear();
        update(i);
        print();
        SDL_Delay(2);
    }
}
void SDL::print()
{
    SDL_RenderPresent(this->renderer);
}
void SDL::clear()
{
    SDL_RenderClear(this->renderer);
}

void SDL::setPixel(SDL_Surface* surface, int x, int y, SDL_Color pixel)
{
    *((SDL_Color*)(surface->pixels) + x + y * surface->w) = pixel;
}

SDL::~SDL()
{
Common::_SDL--;

    SDL_SetWindowFullscreen(window, 0);
    SDL_Quit();

    keyboadEvents.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    toDraw->clear();
    delete toDraw;
}
