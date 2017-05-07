#ifndef INPUT_H
#define INPUT_H

#include <cstdio>
#include <ctype.h>
#include <map>

#include "SDL.h"

using std::map;

class Input
{
public:
    static void Update(SDL_Event* event);
    static void Reset();

    static bool IsKeyDown(const char* key);
    static bool IsKeyDown(SDL_Keycode keycode);
    static bool IsShiftDown() { return isShiftDown; }

private:
    static void UpdateShiftKey();

    static map<SDL_Keycode, bool> keyStates;
    static bool isShiftDown;
};

#endif
