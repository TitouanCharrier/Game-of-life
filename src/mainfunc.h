#ifndef MAINFUNC
#define MAINFUNC

#include "struct.h"
#include <SDL2/SDL.h>
#include <assert.h>

Case **LoadCase(int width, int height);
void PrintScene(SDL_Renderer *renderer, Case **ListCase);

#endif