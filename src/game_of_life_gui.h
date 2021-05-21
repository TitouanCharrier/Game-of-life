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

/*
Loading / Saving : -------------------------------------------------------------
*/

//Allocate a 2D array containing the main grid
void LoadCase(St_List *List,Grid *NumberOf);

//Copie the actual states of cases on a file (format .ins)
void SaveMap(St_List *List, Grid *NumberOf, char name[]);

//Change the actual state of cases to match a file.ins 
void LoadMap(St_List *List, Grid *NumberOf, char name[]);

//Allocate and define all buttons used for the interface
void LoadButton(St_List *List, St_Var *MainVar, Grid *NumberOf);

//Change the actual state of cases to match a file.rle
void LoadRle(St_List *List, Grid *NumberOf, char name[]);

//Define the Background
void LoadBackground(SDL_Renderer *renderer, St_Var *MainVar);

/*
Interact : ---------------------------------------------------------------------
*/

//Search the button matching the mouse coords
int FindButton(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

//Search the Case matching the mouse coords once done, set its state on
void PlaceCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

//Search the Case matching the mouse coords once done, set its state off
void RemoveCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

//Define all actions which buttons must perform
void ButtonFunc(SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar);

//Define all actions which keys (released) must perform
void HandleKeyUp(St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

//Define all actions which keys (pressed) must perform
int HandleKeyDown(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

//Reallocate Case array to match desired size
int ChangeMapSize(St_List *List, Grid *NumberOf, int NewLines, int NewCols);

//NOT my function, I take it on internet but I understand pretty well how its work
//It just concatenate 2 int
int concat(int x, int y);

/*
Printing : ---------------------------------------------------------------------
*/

//Call all function begining by "Print" 
void PrintScene(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

//Place and write on the renderer the cases
void PrintCases(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

//Called when an action change a button to avoid charging texture all the time
//Change buttons attributes
void RefreshButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

//Place and write on the renderer the Buttons
void PrintButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

//Place and write on the renderer the Counter
void PrintCount(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

//Place and write on the renderer the Errors
void PrintError(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

/*
//Cleaning : -------------------------------------------------------------------
*/

//Reset all cases's state to 0
void Clean(St_List *List, Grid *NumberOf);

/*
//Work In Progress : -----------------------------------------------------------
*/

//This is an other methode to find a matching 
//We divide the grid in 4 chunk, check if the click is inside one
//Then repeat the operation until we find the case
//in theorie that work, in fact I havent succed.
Couple CompareChunk(St_List *List, Grid *NumberOf,St_Var *MainVar, int sourx, int soury);

#endif
