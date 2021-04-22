#ifndef MAINFUNC
#define MAINFUNC

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <time.h>
#include <string.h>

Case **LoadCase(int NumberLine);

void PrintScene(SDL_Renderer *renderer, Case **ListCase, Button *ListButton, location loc, int NumberLine, int timer, TTF_Font *police);

Couple CompareChunk(Case **ListCase, int NumberLine, location loc, int sourx, int soury);

void LifeThor(Case **LC, int NumberLine);

void LifeClosed(Case **LC, int NumberLine);

void SaveMap(Case **ListCase, int NumberLine, char name[]);

int LoadMap(Case **ListCase, int NumberLine, char name[]);

void LoadButton(Button *ListButton);

int ButtonFunc(SDL_Renderer *renderer, Button *ListButton, Case **ListCase, int NumberLine, int *MapState, location loc, int timer, TTF_Font *police);

#endif
