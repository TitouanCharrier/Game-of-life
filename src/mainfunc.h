#ifndef MAINFUNC
#define MAINFUNC

#define pi 3.1415926535897932384626433

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int concat(int x, int y);

void Clean(St_List *List, Grid *NumberOf);

void FreeCase(St_List *List,Grid *NumberOf);

void LoadCase(St_List *List,Grid *NumberOf);

void LifeThor(St_List *List, Grid *NumberOf);

void LoadStdin(St_List *List, Grid *NumberOf);

void LifeClosed(St_List *List, Grid *NumberOf);

void SaveMap(St_List *List, Grid *NumberOf, char name[]);

void LoadMap(St_List *List, Grid *NumberOf, char name[]);

void LoadButton(St_List *List, St_Var *MainVar, Grid *NumberOf);

void LoadDirection(St_List *List, St_Var *MainVar, Grid *NumberOf);

void FindCase(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

void FinDirection(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

void PrintScene(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

void PlaceCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

void RemoveCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

void ButtonFunc(SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar, Disp *DispVar);

void HandleKeyUp(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

void HandleKeyDown(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

Couple CompareChunk(St_List *List, Grid *NumberOf,St_Var *MainVar, int sourx, int soury);

#endif
