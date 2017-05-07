#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"

#include "Global.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void Clear();
    void Present();

    SDL_Renderer* GetRenderer() const { return renderer; }
    SDL_Window* GetWindow() const { return window; }

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
};

#endif
