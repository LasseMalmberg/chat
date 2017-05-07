#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdio>
#include <string>

#include "SDL.h"

typedef unsigned int uint;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


#define SAFE_DELETE(p) if (p != NULL) { delete p; p = NULL; }

// Prints an error message with file name and line number.
#define ERROR(msg) fprintf(stderr, "[Error][%s][%d] %s\n", \
        __FILE__, __LINE__, msg)

// Prints an error message if p is null.
#define MEM_CHECK(p) if (p == NULL) \
        fprintf(stderr, "[Error][%s][%d] Null pointer\n", \
            __FILE__, __LINE__)

// If return value (rv) is less than zero, the SDL function failed.
#define SDL_CHECK(rv, msg) if (rv < 0) \
        fprintf(stderr, "[Error][%s][%d] %s failure: %s\n", \
            __FILE__, __LINE__, msg, SDL_GetError())

#endif
