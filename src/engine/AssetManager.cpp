#include "AssetManager.h"

Graphics* AssetManager::graphics = NULL;
TTF_Font* AssetManager::font = NULL;

void AssetManager::Initialize(Graphics* gfx) 
{
    if (!graphics)
        graphics = gfx;

    // Load the only font in the program.
    font = TTF_OpenFont("fonts/Inconsolata-Regular.ttf", 40);
}

void AssetManager::Deinitialize() 
{
    TTF_CloseFont(font);
}

// Converts text to a texture. Returns the texture's dimensions
// through the width and height parameters.  
SDL_Texture* AssetManager::ConvertStringToTexture(string text, int& width, int& height)
{
    // Convert the font and the text to a surface.
    SDL_Color textColor = { 247, 247, 247 };
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (textSurface == NULL)
        ERROR("Unable to render text surface");

    // Take the surface's dimensions.
    width = textSurface->w;
    height = textSurface->h;

    // Convert the surface to a texture.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics->GetRenderer(), textSurface);
    if (texture == NULL)
        ERROR("Unable to create texture from text surface");


    SDL_FreeSurface(textSurface);

    return texture;
}
