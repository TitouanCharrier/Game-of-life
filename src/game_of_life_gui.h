/*! \file game_of_life_gui.h
 *  \author Les_Mecs_Paumees
 *  \brief Define all function to setup the graphical user interface
 */

/*! \page game_of_life_gui.h
 */

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

/*! \fn void LoadCase(St_List *List,Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Allocate a 2D array containing the main grid
 *
 * \param argc : 2
 * \param argv : (St_List *List,Grid *NumberOf)
 * \return void
 */
void LoadCase(St_List *List,Grid *NumberOf);

/*! \fn void SaveMap(St_List *List, Grid *NumberOf, char name[])
 *  \author Les_Mecs_Paumees
 *
 *  \brief Copie the actual states of cases on a file (format .ins)
 *
 * \param argc : 3
 * \param argv : (St_List *List, Grid *NumberOf, char name[])
 * \return void
 */
void SaveMap(St_List *List, Grid *NumberOf, char name[]);

/*! \fn void LoadMap(St_List *List, Grid *NumberOf, char name[])
 *  \author Les_Mecs_Paumees
 *
 *  \brief Change the actual state of cases to match a file.ins 
 *
 * \param argc : 3
 * \param argv : (St_List *List, Grid *NumberOf, char name[])
 * \return void
 */
void LoadMap(St_List *List, Grid *NumberOf, char name[]);

/*! \fn void LoadButton(St_List *List, St_Var *MainVar, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Allocate and define all buttons used for the interface
 *
 * \param argc : 3
 * \param argv : (St_List *List, St_Var *MainVar, Grid *NumberOf)
 * \return void
 */
void LoadButton(St_List *List, St_Var *MainVar, Grid *NumberOf);

/*! \fn void LoadRle(St_List *List, Grid *NumberOf, char name[])
 *  \author Les_Mecs_Paumees
 *
 *  \brief Change the actual state of cases to match a file.rle
 *
 * \param argc : 3
 * \param argv : (St_List *List, Grid *NumberOf, char name[])
 * \return void
 */
void LoadRle(St_List *List, Grid *NumberOf, char name[]);

/*! \fn void LoadBackground(SDL_Renderer *renderer, St_Var *MainVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Define the Background
 *
 * \param argc : 2
 * \param argv : (SDL_Renderer *renderer, St_Var *MainVar)
 * \return void
 */
void LoadBackground(SDL_Renderer *renderer, St_Var *MainVar);

/*
Interact : ---------------------------------------------------------------------
*/

/*! \fn void FindButton(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Search the button matching the mouse coords
 *
 * \param argc : 4
 * \param argv : (SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar)
 * \return void
 */
int FindButton(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

/*! \fn void PlaceCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Search the Case matching the mouse coords once done, set its state on
 *
 * \param argc : 5
 * \param argv : (SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar)
 * \return void
 */
void PlaceCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

/*! \fn void RemoveCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Search the Case matching the mouse coords once done, set its state off
 *
 * \param argc : 5
 * \param argv : (SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar)
 * \return void
 */
void RemoveCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar);

/*! \fn void ButtonFunc(SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Define all actions which buttons must perform
 *
 * \param argc : 5
 * \param argv : (SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar)
 * \return void
 */
void ButtonFunc(SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar);

/*! \fn void HandleKeyUp(St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Define all actions which keys (released) must perform
 *
 * \param argc : 5
 * \param argv : (St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar)
 * \return void
 */
void HandleKeyUp(St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

/*! \fn int HandleKeyDown(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Define all actions which keys (pressed) must perform
 *
 * \param argc : 6
 * \param argv : (SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar)
 * \return 
 * 1 if a key is detected
 * 0 if not
 */
int HandleKeyDown(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar);

/*! \fn void ChangeMapSize(St_List *List, Grid *NumberOf, int NewLines, int NewCols)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Reallocate Case array to match desired size
 *
 * \param argc : 4
 * \param argv : (St_List *List, Grid *NumberOf, int NewLines, int NewCols)
 * \return void
 */
void ChangeMapSize(St_List *List, Grid *NumberOf, int NewLines, int NewCols);

/*! \fn int concat(int x, int y)
 *  \author Internet
 *
 *  \brief NOT my function, I take it on internet. It just concatenate 2 int
 *
 * \param argc : 2
 * \param argv : (int x, int y)
 * \return concatenation of the 2 integers
 */
int concat(int x, int y);

/*
Printing : ---------------------------------------------------------------------
*/

/*! \fn void PrintScene(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Call all function begining by "Print" 
 *
 * \param argc : 4
 * \param argv : (SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 * \return void
 */
void PrintScene(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

/*! \fn void PrintCases(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Place and write on the renderer the cases
 *
 * \param argc : 4
 * \param argv : (SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 * \return void
 */
void PrintCases(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

/*! \fn void RefreshButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Called when an action change a button to avoid charging texture each time. Change buttons attributes
 *
 * \param argc : 4
 * \param argv : (SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 * \return void
 */
void RefreshButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

/*! \fn void PrintButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Place and write on the renderer the Buttons
 *
 * \param argc : 4
 * \param argv : (SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 * \return void
 */
void PrintButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

/*! \fn void PrintCount(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Place and write on the renderer the Counter
 *
 * \param argc : 4
 * \param argv : (SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 * \return void
 */
void PrintCount(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

/*! \fn void PrintError(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Place and write on the renderer the Errors
 *
 * \param argc : 4
 * \param argv : (SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf)
 * \return void
 */
void PrintError(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf);

/*
Cleaning : -------------------------------------------------------------------
*/

/*! \fn void Clean(St_List *List, Grid *NumberOf)
 *  \author Les_Mecs_Paumees
 *
 *  \brief Reset all cases's state to 0
 *
 * \param argc : 2
 * \param argv : (St_List *List, Grid *NumberOf)
 * \return void
 */
void Clean(St_List *List, Grid *NumberOf);

/*
Work In Progress : -----------------------------------------------------------
*/

/*! \fn void CompareChunk(St_List *List, Grid *NumberOf,St_Var *MainVar, int sourx, int soury)
 *  \author Les_Mecs_Paumees
 *
 *  \brief This is an other methode to find a clicked case
 *
 * \param argc : 5
 * \param argv : (St_List *List, Grid *NumberOf,St_Var *MainVar, int sourx, int soury)
 * \return Couple of coordinates
 * 
 * \remarks
 * We divide the grid in 4 chunk, check if the click is inside one
 * Then repeat the operation until we find the case
 * in theorie that work, in fact I havent succed.
 */
Couple CompareChunk(St_List *List, Grid *NumberOf,St_Var *MainVar, int sourx, int soury);

#endif
