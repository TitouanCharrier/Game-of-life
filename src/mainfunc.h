#ifndef MAINFUNC
#define MAINFUNC

#include "struct.h"
#include <SDL2/SDL.h>
#include <assert.h>

Case **LoadCase(int NumberLine);

void PrintScene(SDL_Renderer *renderer, Case **ListCase, location loc, int NumberLine);

void Life(Case **LC, int NumberLine);

#endif