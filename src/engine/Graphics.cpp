#include "Graphics.h"

Graphics::Graphics()
{
    std::string title = "Chat";

    window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_RESIZABLE);

    MEM_CHECK(window);

    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    MEM_CHECK(renderer);

    SDL_RenderSetLogicalSize(renderer,WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

Graphics::~Graphics() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Graphics::Clear() 
{
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 0);
    SDL_RenderClear(renderer);
}

void Graphics::Present() 
{
    SDL_RenderPresent(renderer);
}
