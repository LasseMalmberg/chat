#include "Input.h"

map<SDL_Keycode, bool> Input::keyStates;
bool Input::isShiftDown;

void Input::Update(SDL_Event* event) 
{
    // Shift is updated separately to allow it to be used simultaneously with 
    // other keys. This enables the use of uppercase and special characters.
    UpdateShiftKey();

    // Update the state of the listed keys.
    // Note: limited to one key per frame.
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
            case SDLK_a:
            case SDLK_b:
            case SDLK_c:
            case SDLK_d:
            case SDLK_e:
            case SDLK_f:
            case SDLK_g:
            case SDLK_h:
            case SDLK_i:
            case SDLK_j:
            case SDLK_k:
            case SDLK_l:
            case SDLK_m:
            case SDLK_n:
            case SDLK_o:
            case SDLK_p:
            case SDLK_q:
            case SDLK_r:
            case SDLK_s:
            case SDLK_t:
            case SDLK_u:
            case SDLK_v:
            case SDLK_w:
            case SDLK_x:
            case SDLK_y:
            case SDLK_z:
            case SDLK_1:
            case SDLK_2:
            case SDLK_3:
            case SDLK_4:
            case SDLK_5:
            case SDLK_6:
            case SDLK_7:
            case SDLK_8:
            case SDLK_9:
            case SDLK_0:
            case SDLK_SPACE:
            case SDLK_PERIOD:
            case SDLK_COMMA:
            case SDLK_QUOTE:
            case SDLK_PLUS:
            case SDLK_RETURN:
            case SDLK_RETURN2:
            case SDLK_BACKSPACE:
                keyStates[event->key.keysym.sym] = true;
                break;
    }
}

// Resets the state of all keys to not pressed.
void Input::Reset()
{
    for (auto it = keyStates.begin(); it != keyStates.end(); it++)
    {
        it->second = false;
    }
}

bool Input::IsKeyDown(const char* key) 
{
    char c = tolower(*key);

    SDL_Keycode keycode = SDL_GetKeyFromName(&c);

    return keyStates[keycode];
}

bool Input::IsKeyDown(SDL_Keycode keycode)
{
    return keyStates[keycode];
}

void Input::UpdateShiftKey()
{
    isShiftDown = false;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LSHIFT])
        isShiftDown = true;
}
