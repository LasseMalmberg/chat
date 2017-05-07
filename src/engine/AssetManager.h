#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Global.h"
#include "Graphics.h"

using std::string;

class AssetManager
{
public:
    static void Initialize(Graphics* gfx);
    static void Deinitialize();

    static SDL_Texture* ConvertStringToTexture(string text, int& width, int& height);

private:
    static TTF_Font* font;
    static Graphics* graphics;
};

#endif
