#ifndef MAINFUNC
#define MAINFUNC

#define pi 3.1415926535897932384626433

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void test();

//Loading / Saving : 
void LoadCase(St_List *List,Grid *NumberOf);

void SaveMap(St_List *List, Grid *NumberOf, char name[]);

void LoadMap(St_List *List, Grid *NumberOf, char name[]);

void LoadButton(St_List *List, St_Var *MainVar, Grid *NumberOf);

void LoadRle(St_List *List, Grid *NumberOf, char name[]);

void LoadBackground(SDL_Renderer *renderer, St_Var *MainVar);

//Interact :
int FindButton(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

void PlaceCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

void RemoveCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

void ButtonFunc(SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar, Disp *DispVar);

void HandleKeyUp(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

int HandleKeyDown(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

int concat(int x, int y);

int ChangeMapSize(St_List *List, Grid *NumberOf, int NewLines, int NewCols);

//Printing : 
void PrintScene(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

void PrintCases(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

void RefreshButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf, SDL_Color White);

void PrintButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf, SDL_Color White);

void PrintCount(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf, SDL_Color White);

void PrintError(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf, SDL_Color White);

//Cleaning : 
void Clean(St_List *List, Grid *NumberOf);

//WIP :
Couple CompareChunk(St_List *List, Grid *NumberOf,St_Var *MainVar, int sourx, int soury);

void FreeCase(St_List *List,Grid *NumberOf);

#endif
