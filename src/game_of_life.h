#ifndef GAMEOFLIFE
#define GAMEOFLIFE

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "game_of_life_gui.h"

//Change Game's first grid size and colors from settings.txt 
void LoadSettings(Grid *NumberOf, St_Var *MainVar);

//Define rules for cell's life and death (thorique matrix)
void LifeThor(St_List *List, Grid *NumberOf);

//Define rules for cell's life and death (closed matrix)
void LifeClosed(St_List *List, Grid *NumberOf);

//Ask stdin for load a pattern using a pipe on launch
int LoadStdin(St_List *List, Grid *NumberOf, St_Var *MainVar);

#endif