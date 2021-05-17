#ifndef GAMEOFLIFE
#define GAMEOFLIFE

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "game_of_life_gui.h"

void LoadSettings(Grid *NumberOf);

void LifeThor(St_List *List, Grid *NumberOf);

int LoadStdin(St_List *List, Grid *NumberOf, St_Var *MainVar);

void LifeClosed(St_List *List, Grid *NumberOf);

#endif