#ifndef MAINFUNC
#define MAINFUNC

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include "../lib/include/SDL2/SDL.h"
#include "../lib/include/SDL2/SDL_ttf.h"
#include "../lib/include/assert.h"
#include "../lib/include/time.h"
#include "../lib/include/string.h"
#include "../lib/include/unistd.h"

Case **LoadCase(Grid *NumberOf);

void PrintScene(SDL_Renderer *renderer, Case **ListCase, Button *ListButton, location loc, Grid *NumberOf, int *timer, TTF_Font *police);

Couple CompareChunk(Case **ListCase, Grid *NumberOf, location loc, int sourx, int soury);

void LifeThor(Case **LC, Grid *NumberOf);

void LifeClosed(Case **LC, Grid *NumberOf);

void SaveMap(Case **ListCase, Grid *NumberOf, char name[]);

void LoadMap(Case **ListCase, Grid *NumberOf, char name[]);

void LoadButton(Button *ListButton, int RESX, int RESY, Grid *NumberOf);

void ButtonFunc(SDL_Renderer *renderer, Button *ListButton, Case **ListCase, Grid *NumberOf, int *MapState, location loc, int *timer, TTF_Font *police);

void Clean(Case **ListCase, Grid *NumberOf);

void FreeCase(Case **ListCase,Grid *NumberOf);

#endif
