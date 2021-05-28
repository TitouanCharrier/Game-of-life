/*! \file game_of_life.h
 *  \author Les_Mecs_Paumees
 *  \brief Define all function essentials to make the game of life
 */

/*! \page game_of_life.h
 */

#ifndef GAMEOFLIFE
#define GAMEOFLIFE

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "game_of_life_gui.h"

/*! \fn void LoadSettings(Grid *NumberOf, St_Var *MainVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Change Game's first grid size and colors from settings.txt 
 *
 * \param argc : 2
 * \param argv : (Grid *NumberOf, St_Var *MainVar)
 * \return void
 */
void LoadSettings(Grid *NumberOf, St_Var *MainVar);

/*! \fn void LifeThor(St_List *List, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Define rules for cell's life and death (thorique matrix)
 *
 * \param argc : 2
 * \param argv : (St_List *List, Grid *NumberOf)
 * \return void
 */
void LifeThor(St_List *List, Grid *NumberOf);

/*! \fn LifeClosed(St_List *List, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Define rules for cell's life and death (closed matrix)
 *
 * \param argc : 2
 * \param argv : (St_List *List, Grid *NumberOf)
 * \return void
 */
void LifeClosed(St_List *List, Grid *NumberOf);

/*! \fn void LoadStdin(St_List *List, Grid *NumberOf, St_Var *MainVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Ask stdin for load a pattern using a pipe on launch
 *
 * \param argc : 2
 * \param argv : (St_List *List, Grid *NumberOf, St_Var *MainVar)
 * \return void
 */
int LoadStdin(St_List *List, Grid *NumberOf, St_Var *MainVar);

#endif